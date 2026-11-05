#pragma once

#include <numeric>
#include <utility>
#include <vector>

// Система непересекающихся множеств (DSU)
class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n), size_(n, 1) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    // Корень множества, в котором лежит x
    int find(int x) {
        if (parent_[x] != x)
            parent_[x] = find(parent_[x]);
        return parent_[x];
    }

    // Объединяет множества; false, если они уже были одним
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        
        if (size_[a] < size_[b])
            std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }

private:
    std::vector<int> parent_;
    std::vector<int> size_;
};