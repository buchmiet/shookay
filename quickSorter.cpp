#include "pch.h"
#include "quickSorter.h"

namespace QuickSorter {
    static int Partition(std::vector<WordDescription>& list, int left, int right);
    static void QuickSort(std::vector<WordDescription>& list, int left, int right);
    static void Swap(std::vector<WordDescription>& list, int i, int j);

    void Sort(std::vector<WordDescription>& list) {
        QuickSort(list, 0, list.size() - 1);
    }

    static int Partition(std::vector<WordDescription>& list, int left, int right) {
        WordDescription pivot = list[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (list[j].length > pivot.length) { 
                i++;
                Swap(list, i, j);
            }
        }
        Swap(list, i + 1, right);
        return i + 1;
    }

    static void QuickSort(std::vector<WordDescription>& list, int left, int right) {
        if (left < right) {
            int pivotIndex = Partition(list, left, right);
            QuickSort(list, left, pivotIndex - 1);
            QuickSort(list, pivotIndex + 1, right);
        }
    }

    static void Swap(std::vector<WordDescription>& list, int i, int j) {
        WordDescription temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }
}

