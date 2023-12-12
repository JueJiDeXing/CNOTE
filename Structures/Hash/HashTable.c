// Author: 绝迹的星 
// Created on 2023/12/12
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 Entry节点类

 @属性 hash 哈希码
 @属性 key, value 存储的键值对
 @属性 next 下一个节点
 */
typedef struct Entry {
    int hash;//哈希码
    int key;
    int value;
    struct Entry *next;
} Entry;

void InitEntry(Entry *entry, int hash, int key, int value) {
    entry->hash = hash;
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
}

#define DefaultSize 16
/**
 哈希表<br>
 基于数组与链表实现
 */
typedef struct HashTable {
    Entry **table;//2^n大小
    int size;
    int currCapacity;
    float loadFactor;//负载因子,当 元素个数/数组长度=0.75时 扩容数组
    int threshold;//阈值
} HashTable;

void InitHashMap(HashTable *map) {
    map->size = 0;
    map->loadFactor = 0.75F;
    map->currCapacity = DefaultSize;
    map->threshold = (int) (map->loadFactor * DefaultSize);
    map->table = malloc(sizeof(Entry *) * map->currCapacity);
    for (int i = 0; i < map->currCapacity; i++) {
        map->table[i] = NULL;
    }
}

/**
 <div color=rgb(155,200,80)>
 <h1>根据hash码获取value</h1>
 </div>
 */
int _Get(HashTable *map, int hash, int key) {
    int index = hash & (map->currCapacity - 1);
    //hash mod length = hash & (length-1) 当且仅当 length=2^n
    //  2进制除10、100、1000,余数为被除数的后1、2、3位

    if (map->table[index] == NULL) {
        return -1;// return NULL
    }
    Entry *p = map->table[index];
    while (p != NULL) {//遍历链表
        if (p->key == key) {//比较
            return p->value;
        }
        p = p->next;
    }
    return -1; // return NULL
}

/**
 <div color=rgb(155,200,80)>
 <h1>扩容</h1>
 </div>
 */
void resize(HashTable *map) {
    //扩容散列原数据
    int newCapacity = map->currCapacity << 1;

    Entry *newTable[newCapacity];//扩容两倍
    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = NULL;
    }
    for (int i = 0; i < map->currCapacity; i++) {
        Entry *p = map->table[i];//链表头
        if (p == NULL) continue;
        //拆分链表到新数组
        //拆分规律:一个链表最多拆分为两个,按hash & length是否为0
        //  2^n 对于后n位与后n+1位相同的index,扩容后位置不变
        //  例如 8 0100 扩容后还是原位置  ; 9 1001 扩容后 位置改变
        //  所以 检查倒数第n+1位是否为0即可
        Entry *aHead = NULL, *bHead = NULL;//拆分的两个新链表
        Entry *a = NULL, *b = NULL;
        while (p != NULL) {
            if ((p->hash & map->currCapacity) == 0) {
                if (a != NULL) {
                    a->next = p;//先指向下一个节点
                } else {
                    aHead = p;//第一次记录头指针
                }
                a = p;//再更新位置
            } else {
                if (b != NULL) {
                    b->next = p;
                } else {
                    bHead = p;
                }
                b = p;
            }
            p = p->next;
        }
        //循环后将两个新链的尾节点指向null
        if (a != NULL) {
            a->next = NULL;
            newTable[i] = aHead;//a表位置不变
        }
        if (b != NULL) {
            b->next = NULL;
            newTable[i + map->currCapacity] = bHead;//b表为索引加数组长
        }
    }
    //扩容
    map->currCapacity = newCapacity;
    map->table = realloc(map->table, sizeof(Entry *) * map->currCapacity);
    if (map->table == NULL) {
        exit(-1);//扩容失败
    }
    for (int i = 0; i < map->currCapacity; i++) {
        map->table[i] = NULL;
    }
    //重拷贝到原数组
    for (int i = 0; i < map->currCapacity; i++) {
        map->table[i] = newTable[i];
    }
    //计算下次扩容阈值
    map->threshold = (int) (map->loadFactor * map->currCapacity);
}

/**
 <div color=rgb(155,200,80)>
 <h1>向hash表存入键值对</h1>
 如果key重复则更新value</div>
 */
void _Put(HashTable *map, int hash, int key, int value) {
    int index = hash & (map->currCapacity - 1);
    Entry *added = malloc(sizeof(Entry));
    if (added == NULL) {
        return;
    }
    InitEntry(added, hash, key, value);
    if (map->table[index] == NULL) {
        //无元素,直接添加
        map->table[index] = added;
    } else {
        //有元素
        Entry *p = map->table[index];
        while (true) {
            if (p->key == key) {
                p->value = value;//有key相同元素,更新元素值
                free(added);
                return;
            }
            if (p->next == NULL) {
                break;
            }
            p = p->next;
        }
        //没有重复的key,新建一个节点
        p->next = added;
    }
    map->size++;
    if (map->size > map->threshold) {
        resize(map);
    }
}

/**
 <div color=rgb(155,200,80)>
 <h1>根据hash码删除</h1>
 </div>
 */
int _Remove(HashTable *map, int hash, int key) {
    int index = hash & (map->currCapacity - 1);
    if (map->table[index] == NULL) {
        //无元素,直接添加
        return -1;
    }
    Entry *p = map->table[index];
    Entry *prev = NULL;
    while (p != NULL) {//遍历链表
        if (p->key == key) {
            //找到元素,删除
            if (prev != NULL) {
                prev->next = p->next;
            } else {
                map->table[index] = p->next;//删除的是链表的第一个节点
            }
            map->size--;
            return p->value;
        }
        prev = p;
        p = p->next;
    }
    return -1;
}

static int getHash(int key) {
    int hash = 0;
    char s[32];
    int len = 0;
    while (key != 0) {
        s[len++] = (char) (key % 10);
        key /= 10;
    }
    for (int i = 0; i < len; i++) {
        char c = s[i];
        hash = (hash << 5) - hash + c;//字符串的每位字符转ASCII码后拼接,乘以一个大质数31使冲突的几率更小
        //优化 hash*31 -> hash*32-hash > (hash<<5)-hash
    }
    return hash ^ (hash >> 16);
}

int Get(HashTable *map, int key) {
    int hash = getHash(key);
    return _Get(map, hash, key);
}


void Put(HashTable *map, int key, int value) {
    int hash = getHash(key);
    _Put(map, hash, key, value);
}

int Remove(HashTable *map, int key) {
    int hash = getHash(key);
    return _Remove(map, hash, key);
}

int GetLength(HashTable map) {
    return map.size;
}

/**
 * 打印链表长度,按长度分组,长度为1有xx个...
 */
void PrintLength(HashTable map) {
    int sums[map.currCapacity];
    for (int i = 0; i < map.currCapacity; i++) {
        sums[i] = 0;
    }
    int maxLen = 0;
    for (int i = 0; i < map.currCapacity; i++) {
        Entry *p = map.table[i];
        while (p != NULL) {
            sums[i]++;
            p = p->next;
        }
        if (sums[i] > maxLen)maxLen = sums[i];
    }
    int count[maxLen + 1];
    for (int i = 0; i <= maxLen; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < map.currCapacity; i++) {
        if (sums[i] != 0) {
            count[sums[i]]++;
        }
    }
    for (int i = 1; i <= maxLen; i++) {
        printf("长度为%d有%d个, ", i, count[i]);
    }
    printf("\b\b\n");
}


/**
 * 打印链表长度,按长度分组,长度为1有xx个...
 */
void PrintMap(HashTable map) {
    for (int i = 0; i < map.currCapacity; i++) {
        Entry *p = map.table[i];
        printf("[");
        while (p != NULL) {
            printf("%d->", p->value);
            p = p->next;
        }
        printf("NULL], ");
    }
    printf("\b\b\n");
}

bool ContainsKey(HashTable map, int key) {
    int hash = getHash(key);
    int index = (hash & 0x7FFFFFFF) % map.currCapacity;
    for (Entry *e = map.table[index]; e != NULL; e = e->next) {
        if ((e->hash == hash) && e->key == key) {
            return true;
        }
    }
    return false;
}


int main1() {
    HashTable map;
    InitHashMap(&map);
    for (int i = 0; i < 100; i++) {
        Put(&map, i, i);
    }
    PrintLength(map);//长度为1有77个, 长度为2有10个, 长度为3有1个
    PrintMap(map);//[0->88->NULL], [1->10->98->NULL], [2->20->NULL], [3->30->NULL], [4->40->NULL],...
    printf("%d\n", Get(&map, 11));//11
    printf("%d\n", Get(&map, 12));//12
    Remove(&map, 13);
    printf("%d\n", Get(&map, 13)); // -1 表示没有
    Put(&map, 13, 13);
    printf("%d\n", Get(&map, 13)); // 13
    printf("%d", ContainsKey(map, 13));//1
    return 0;
}