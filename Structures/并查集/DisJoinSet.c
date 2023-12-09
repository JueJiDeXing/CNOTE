// Author: 绝迹的星 
// Created on 2023/12/9


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DefaultSize 100
//并查集,主要用于判断两个项是否连通
//在Kruskal最小生成树算法中,判断两个顶点是否连通可以使用并查集
typedef struct DisJoinSet {
    //例: s[a]=b表示元素a的根是b, s[b]=b表示元素b就是根 a,b处于同一集合,而b是集合老大
    int s[DefaultSize];//TODO 使用哈希表进行映射
} DisJoinSet;

void InitDisJoinSet(DisJoinSet *set) {
    for (int i = 0; i < DefaultSize; i++) {
        set->s[i] = i;
    }
}

/**
 * 查找元素所在集合的根
 * @param set 并查集
 * @param x 要查找元素
 * @return 元素所在集合的根
 */
int Find(DisJoinSet *set, int x) {
    if (x < 0 || x >= DefaultSize) {
        exit(-1);//索引越界
    }
    if (x == set->s[x]) {//索引对应自身的为老大
        return x;
    }
    set->s[x] = Find(set, set->s[x]);//路径压缩,在查找中将老大的值赋值过来,下次在该集合里查找时路径缩短
    return set->s[x];
}

/**
 * 合并两个集合
 * @param set 并查集
 * @param x x所在集合
 * @param y y所在集合
 */
void Union(DisJoinSet *set, int x, int y) {
    int rootX = Find(set, x), rootY = Find(set, y);
    set->s[rootY] = rootX;
    //TODO 使用size数组记录每个集合的大小,根据集合大小合并集合
}
/**
 * 判断两个元素是否连通(两个元素是否处于同一集合)
 * @param set 并查集
 * @param x 元素x
 * @param y 元素y
 * @return 连通为true,否则false
 */
bool isConnect(DisJoinSet set, int x, int y) {
    return Find(&set, x) == Find(&set, y);
}

int main1() {//测试
    DisJoinSet set;
    InitDisJoinSet(&set);
    Union(&set, 1, 2);
    Union(&set, 1, 3);
    Union(&set, 1, 5);
    Union(&set, 2, 4);
    printf("%d", isConnect(set, 4, 5));//输出1,4和5连通
    return 0;
}