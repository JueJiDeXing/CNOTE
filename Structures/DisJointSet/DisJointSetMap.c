// Author: 绝迹的星 
// Created on 2023/12/12


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Hash/HashTable.c"

typedef struct DisjointSetMap {
    HashTable father;//使用Map映射
} DisJointSetMap;

void InitDisJointSet(DisJointSetMap *set) {
    InitHashMap(&set->father);
}

void Add(DisJointSetMap *set, int x) {
    if (ContainsKey(set->father, x)) {
        return;
    }
    Put(&set->father, x, -1);
}

int Find(DisJointSetMap *set, int x) {
    int root = x;
    while (Get(&set->father, root) != -1) {//查找root
        root = Get(&set->father, root);
    }
    while (x != root) {//将路径上的点归并到root集合
        int curFather = Get(&set->father, x);
        Put(&set->father, x, root);
        x = curFather;
    }
    return root;
}

void Union(DisJointSetMap *set, int x, int y) {
    int rootX = Find(set, x);
    int rootY = Find(set, y);
    if (rootX != rootY) {
        Put(&set->father, rootX, rootY);
    }
}

bool IsConnected(DisJointSetMap *set, int x, int y) {
    return Find(set, x) == Find(set, y);
}


int main1_() {
    DisJointSetMap set;
    InitDisJointSet(&set);
    Add(&set, 1);
    Add(&set, 2);
    Add(&set, 3);
    Add(&set, 4);
    Add(&set, 5);
    Union(&set, 1, 2);
    Union(&set, 2, 3);
    Union(&set, 4, 5);
    printf("%d\n", IsConnected(&set, 1, 3));//1
    printf("%d\n", IsConnected(&set, 1, 5));//0
    return 0;
}