#ifndef MYINTHASHSET_H
#define MYINTHASHSET_H
#include <vector>

class MyIntHashSet {
public:
    explicit MyIntHashSet(int dlugosc);
    explicit MyIntHashSet(const std::vector<int>& ints);
    size_t Length() const;
    void Add(int value);
    void Clear();
    void ExceptWith(const MyIntHashSet& secondHashSet);
    void IntersectWith(const MyIntHashSet& secondHashSet);
 
    void UnionWith(const MyIntHashSet& secondHashSet);
    int getPositives();
    const std::vector<int>& Ints() const {
        return _ints;
    }

private:
    std::vector<int> _ints;
    size_t _dlugosc;
};

#endif 