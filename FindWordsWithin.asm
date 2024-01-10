.CODE

FindWordsWithinUntilTheContentIsTooSmallOrEndOfRecordAsm PROC
        mov     QWORD PTR [rsp+32], r9
        mov     QWORD PTR [rsp+24], r8
        mov     QWORD PTR [rsp+16], rdx
        mov     DWORD PTR [rsp+8], ecx
        sub     rsp, 104

        mov [rsp+r12Local$],r12
        mov [rsp+r13Local$],r13
        mov [rsp+r14Local$],r14
        mov [rsp+r15Local$],r15
        mov [rsp+rsiLocal$],rsi
        mov [rsp+rbxLocal$],rbx
        mov [rsp+rdiLocal$],rdi


         jmp LoadWyrazenieItemToRs
RsLoaded:
    xor ESI,esi; ESI = IndexToCharInContentArray
    mov dword PTR [rsp+currentRecordIndex$], esi

poczatek_glownej_petli:

    mov eax, dword PTR [rsp+currentRecordIndex$];    while (currentRecordIndex < iloscWszystkichRekordow)
    cmp eax, dword PTR [rsp+iloscWszystkichRekordow$]
    jge koniec_glownej_petli; Skocz, jeśli currentRecordIndex$ >= iloscWszystkichRekordow$

SkipToFirstRecordThatIsOkToLookForAsm :
    mov eax, DWORD PTR [rsp+iloscWszystkichRekordow$]
    cmp DWORD PTR [rsp+currentRecordIndex$], eax
    jge SkipToFirstRecordThatIsOkToLookForAsmEND; while (currentRecordIndex < iloscWszystkichRekordow
    mov eax, DWORD PTR [rsp+currentRecordIndex$] 
    mov rcx, QWORD PTR [rsp+results$]
    shl rax, 2
    cmp DWORD PTR[rcx + rax], 0
    jne SkipToFirstRecordThatIsOkToLookForAsmEND; results[currentRecordIndex] == 0
    mov eax, DWORD PTR [rsp+currentRecordIndex$]
    inc eax
    mov DWORD PTR [rsp+currentRecordIndex$], eax; currentRecordIndex++
    mov eax, DWORD PTR [rsp+iloscWszystkichRekordow$]
    cmp DWORD PTR [rsp+currentRecordIndex$], eax
    jge SkipToFirstRecordThatIsOkToLookForAsm;	if (currentRecordIndex < iloscWszystkichRekordow)
    mov eax, DWORD PTR [rsp+currentRecordIndex$]   
    mov rcx, QWORD PTR [rsp+recordOffsets$]
    shl rax, 2
    mov eax, DWORD PTR[rcx + rax]
    mov esi, eax; ESI = IndexToCharInContentArray
    jmp SkipToFirstRecordThatIsOkToLookForAsm

SkipToFirstRecordThatIsOkToLookForAsmEND:
    mov eax, DWORD PTR [rsp+currentRecordIndex$];  if (currentRecordIndex == iloscWszystkichRekordow) {
    mov ebx, DWORD PTR [rsp+iloscWszystkichRekordow$]
    cmp eax, ebx
    je koniec_glownej_petli;  break;  
    dec ebx
    cmp eax,ebx          
    jne currentRecordIndex_not_equal_iloscWszystkichRekordow_minus_1
    mov eax, dword ptr [rsp+contentArraySize$]
    mov dword ptr [rsp+wskaznikNaKoniecBiezacegoRekordu$], eax; wskaznikNaKoniecBiezacegoRekordu = contentArray.size();
    jmp currentRecordIndex_equal_iloscWszystkichRekordow_minus_1

currentRecordIndex_not_equal_iloscWszystkichRekordow_minus_1:
        mov eax, dword ptr [rsp+currentRecordIndex$]
        inc eax 
        shl eax, 2
        mov rdx, QWORD PTR [rsp+recordOffsets$]
        add rdx, rax
        mov eax, [rdx]
        mov DWORD PTR[rsp + wskaznikNaKoniecBiezacegoRekordu$], eax

currentRecordIndex_equal_iloscWszystkichRekordow_minus_1:
    mov byte ptr [rsp+znaleziony$], 0;  znaleziony = false;

while_IndexToCharInContentArray_l_wskaznikNaKoniecBiezacegoRekordu_and_not_znaleziony: 
        cmp esi, DWORD PTR [rsp+wskaznikNaKoniecBiezacegoRekordu$]; ESI = IndexToCharInContentArray
        jge przed_przed_koniec_petli
        movzx eax, byte ptr [rsp+znaleziony$]
        test eax, eax;   while (IndexToCharInContentArray < wskaznikNaKoniecBiezacegoRekordu && !znaleziony)
        jnz przed_przed_koniec_petli

CompareWordsUntilTheContentIsTooSmallOrEndOfRecord:
        cmp esi, DWORD PTR[rsp+wskaznikNaKoniecBiezacegoRekordu$]; ESI = IndexToCharInContentArray
        jge przed_przed_koniec_petli; IndexToCharInContentArray < pointerToEndOfTheRecord
        mov eax, esi; ESI = IndexToCharInContentArray
        mov rdx, QWORD PTR[rsp + descriptionArray$]
        shl eax, 2      
        add rdx, rax
        mov eax, DWORD PTR[rdx];eax= descriptionArray$[IndexToCharInContentArray]
        mov ecx, eax; Skopiuj wartość do ecx  ecx= descriptionArray$[IndexToCharInContentArray]
        shr ecx, 24; Przesuń ecx o 24 bity w prawo, aby MSB stał się LSB
        and ecx, 255; Maskuj, aby zachować tylko LSB(OdlegloscOdKoncaSlowa);
        mov edi,ecx; EDI= OdlegloscOdKoncaSlowa
        shr eax, 16; Przesuń eax o 16 bitów w prawo, aby trzeci bajt stał się LSB
        and eax, 255; Maskuj, aby zachować tylko LSB(DlugoscSlowa); eax= DlugoscSlowa
        movzx ebx, BYTE PTR [rsp+dlugoscWyrazeniaItem$]
        cmp eax, ebx; eax = descriptionArray[IndexToCharInContentArray].DlugoscSlowa
        jge InnerLoop; descriptionArray[IndexToCharInContentArray].DlugoscSlowa >= dlugoscWyrazeniaItem
        mov esi, dword ptr[rsp+wskaznikNaKoniecBiezacegoRekordu$]
        jmp przed_przed_koniec_petli ;jesli pierwsze slowo z rekordu jest mniejsze niz wyszukiwane, to powinno 

InnerLoop: ; ecx = descriptionArray[IndexToCharInContentArray].OdlegloscOdKoncaSlowa
        mov eax, esi; ESI = IndexToCharInContentArray
        add eax, ecx; ecx = descriptionArray[IndexToCharInContentArray].OdlegloscOdKoncaSlowa
        mov DWORD PTR [rsp+koniec_slowa$], eax; int koniec_slowa = IndexToCharInContentArray + descriptionArray[IndexToCharInContentArray].OdlegloscOdKoncaSlowa;

VeryInnerLoop:;  while (IndexToCharInContentArray + dlugoscWyszukiwanegoWyrazenia <= koniec_slowa)  
        mov rbx, QWORD PTR contentArray$[rsp];rbx = adres do contentArray$
        mov byte ptr [rsp+jest$],1 ;bool jest = true;     
        ; znaczenie rejestrow :
        ; rbx - rbx = adres do contentArray$
        ; rdx - pozycja aktualnie porownywanego znaku, wzgledna, od zera
        ; esi - bezwgledna pozycja porownywanego znaku
        ; edi - odleglosc od konca slowa, wzgledna, tj slugosc calego slowa minus dlugosc jego czesci po analizie

      ;Rs start

        mov eax,esi
        shl rax,2
        add rax,rbx
        mov bl,0
        mov bh, BYTE PTR [rsp+dlugoscWyrazeniaItem$]

        ;pierwszy znak
        mov ecx,[rax] ; w ecx jest pierwszy znak z contentArray$[IndexToCharInContentArray]
        inc esi  
        dec edi
        cmp r8d,ecx  ; 
        jne nierowne; jezeli contentArray$[IndexToCharInContentArray]!=wyrazenieItem[0]
        inc bl
        cmp bh,bl 
        je rowne

        ;drugi znak
        mov rdx,r8       
        add rax,4                             
        rol rdx,32
        mov ecx,[rax]
        inc esi  
        dec edi
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;trzeci znak
        add rax,4
        inc esi  
        mov ecx,[rax]       
        dec edi
        cmp r9d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;czwarty znak
        mov rdx,r9
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;piaty znak        
        add rax,4        
        inc esi  
        dec edi
        mov ecx,[rax]
        cmp r10d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne


        ;szosty znak
        mov rdx,r10
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;siodmy znak
        add rax,4         
        mov ecx,[rax]       
        inc esi  
        dec edi
        cmp r11d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;osmy znak
        mov rdx,r11
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;dziewiaty znak
        add rax,4                
        inc esi
        mov ecx,[rax]
        dec edi
        cmp r12d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;10y znak
        mov rdx,r12
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;11y znak
        add rax,4         
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp r13d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;12y znak
        mov rdx,r13
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;13y znak
        add rax,4         
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp r14d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;14y znak
        mov rdx,r14
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;15y znak
        add rax,4         
        mov ecx,[rax]
        inc esi  
        dec edi    
        cmp r15d,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne

        ;16y znak
        mov rdx,r15
        add rax,4        
        rol rdx,32        
        mov ecx,[rax]      
        cmp edx,ecx
        jne nierowne
        inc bl
        cmp bh,bl 
        je rowne


nierowne:  
        mov byte ptr [rsp+jest$],0 ; dotychczasowe sprawdzanie doszlo do sciany wiec
        movzx eax,BYTE PTR [rsp+dlugoscWyrazeniaItem$] ; sprawdze, czy poszukiwane slowo moze wciaz zmiescic sie od 
        add eax,esi ; nastepnej litery
        cmp eax,DWORD PTR [rsp+koniec_slowa$] ; i czy bedzie to mniejsze niz wskaznik na koniec slowa
        jle VeryInnerLoop ; jezeli tak, to jedziemy dalej,             
        add esi,edi ; jezeli zas nie, to esi bedzie teraz wskazywalo na pierwszy znak nowego slowa
        jmp CompareWordsUntilTheContentIsTooSmallOrEndOfRecord
 
rowne: ;zgadza sie!
        mov byte ptr [rsp+jest$],1
        mov esi, DWORD PTR[rsp+wskaznikNaKoniecBiezacegoRekordu$]
        jmp CompareWordsUntilTheContentIsTooSmallOrEndOfRecordEND;


CompareWordsUntilTheContentIsTooSmallOrEndOfRecordEND:
        mov al,byte ptr [rsp+jest$]
        mov byte ptr [rsp+znaleziony$],al

przed_przed_koniec_petli:
        movzx eax, byte ptr [rsp+znaleziony$]
        test eax, eax
        jnz prawie_koniec_glownej_petli
        mov eax, DWORD PTR [rsp+currentRecordIndex$]; Załaduj currentRecordIndex do eax.
        shl eax, 2; Pomnóż eax przez 4 (rozmiar int).
        mov rdx, QWORD PTR[rsp + results$]; Załaduj adres tablicy results do rdx.
        add rdx, rax; Dodaj przesunięty indeks do adresu results.
        mov DWORD PTR[rdx], 0; Ustaw results[currentRecordIndex] na 0.

prawie_koniec_glownej_petli:
        inc DWORD PTR [rsp+currentRecordIndex$]
        jmp poczatek_glownej_petli

koniec_glownej_petli:        
        mov r12,qword ptr[rsp+r12Local$]
        mov r13,qword ptr[rsp+r13Local$]
        mov r14,qword ptr[rsp+r14Local$]
        mov r15,qword ptr[rsp+r15Local$]
        mov rsi,[rsp+rsiLocal$]
        mov rdi,[rsp+rdiLocal$]
        mov rbx,[rsp+rbxLocal$]
        add     rsp, 104                          
        ret     0

       
LoadWyrazenieItemToRs:
        movzx ebx, BYTE PTR [rsp+dlugoscWyrazeniaItem$]
        mov rax, QWORD PTR [rsp + wyrazeniaItem$]
  
        cmp bl, 2
        je wartosc_dwa; Skocz, jeśli równe 2
        jb wartosc_jeden; Skocz, jeśli mniejsze niż 2
        cmp bl, 4
        je wartosc_cztery
        jb wartosc_trzy
        cmp bl, 6
        je wartosc_szesc
        jb wartosc_piec
        cmp bl, 8
        je wartosc_osiem
        jb wartosc_siedem
        cmp bl, 10
        je wartosc_dziesiec
        jb wartosc_dziewiec
        cmp bl, 12
        je wartosc_12
        jb wartosc_11
        cmp bl, 14
        je wartosc_14
        jb wartosc_13
        cmp bl, 16
        je wartosc_16
        jb wartosc_15

wartosc_jeden:
        mov r8d, [rax]
        jmp  RsLoaded

wartosc_dwa:
        mov r8, [rax]
        jmp  RsLoaded

wartosc_trzy:
        mov r8, [rax]
        mov r9d, [rax + 8]
        jmp  RsLoaded

wartosc_cztery:
        mov r8, [rax]
        mov r9, [rax + 8]
        jmp  RsLoaded

wartosc_piec:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10d, [rax + 16]        
        jmp  RsLoaded

wartosc_szesc:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        jmp  RsLoaded

wartosc_siedem:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11d, [rax + 24]        
        jmp  RsLoaded

wartosc_osiem:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        jmp  RsLoaded

wartosc_dziewiec:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12d, [rax + 32]        
        jmp  RsLoaded

wartosc_dziesiec:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        jmp  RsLoaded

wartosc_11:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13d, [rax + 40]        
        jmp  RsLoaded

wartosc_12:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13, [rax + 40]
        jmp  RsLoaded


wartosc_13:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13, [rax + 40]
        mov r14d, [rax + 48]        
        jmp  RsLoaded

wartosc_14:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13, [rax + 40]
        mov r14, [rax + 48]
        jmp  RsLoaded

wartosc_15:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13, [rax + 40]
        mov r14, [rax + 48]
        mov r15d, [rax + 56]        
        jmp  RsLoaded

wartosc_16:
        mov r8, [rax]
        mov r9, [rax + 8]
        mov r10, [rax + 16]
        mov r11, [rax + 24]
        mov r12, [rax + 32]
        mov r13, [rax + 40]
        mov r14, [rax + 48]
        mov r15, [rax + 56]
        jmp  RsLoaded

FindWordsWithinUntilTheContentIsTooSmallOrEndOfRecordAsm ENDP


.data

currentRecordIndex$ = 0
IndexToCharInContentArray$ = 4
pointerToEndOfTheRecord$ = 8
jest$ = 12
koniec_slowa$ = 16
wskaznikNaKoniecBiezacegoRekordu$ = 20
znaleziony$ = 24
r12Local$ = 32
r13Local$ = 40
r14Local$ = 48
r15Local$ = 56
rsiLocal$ = 64
rbxLocal$ = 72
rdiLocal$ = 80
iloscWszystkichRekordow$ = 112
recordOffsets$ = 120
results$ = 128
recordIds$ = 136
contentArray$ = 144
contentArraySize$ = 152
descriptionArray$ = 160
wyrazeniaItem$ = 168
dlugoscWyrazeniaItem$ = 176
END