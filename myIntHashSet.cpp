#pragma once
#include "pch.h"
#include "myIntHashSet.h"
#include <algorithm>

MyIntHashSet::MyIntHashSet(int dlugosc)
    : _ints(dlugosc, -1), _dlugosc(dlugosc) {}

MyIntHashSet::MyIntHashSet(const std::vector<int>& ints)
    : _ints(ints.size(), 1), _dlugosc(ints.size()) {}

size_t MyIntHashSet::Length() const {
    return _ints.size();
}

void MyIntHashSet::Add(int value) {
   
        _ints[value] = 1;
}

void MyIntHashSet::Clear() {
    std::ranges::fill(_ints.begin(), _ints.end(), -1);
}

void MyIntHashSet::ExceptWith(const MyIntHashSet& secondHashSet) {
    for (int i = 0; i < _dlugosc; i++) {
        if (secondHashSet._ints[i] == 1) {
            _ints[i] = -1;
        }
    }
}

void MyIntHashSet::IntersectWith(const MyIntHashSet& secondHashSet) {
    for (int i = 0; i < _dlugosc; i++) {
        _ints[i] = _ints[i] == 1 && secondHashSet._ints[i] == 1 ? 1 : -1;
    }
}


void MyIntHashSet::UnionWith(const MyIntHashSet& secondHashSet) {
    for (int i = 0; i < _dlugosc; i++) {
        if (secondHashSet._ints[i] == 1) {
            _ints[i] = 1;
        }
    }
}

int MyIntHashSet::getPositives() {
    int x = 0;
    for (int i = 0; i < _dlugosc; i++) {
        if (_ints[i] == 1){
            x++;
        }
    }
    return x;
}
