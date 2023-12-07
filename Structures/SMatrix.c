// Author: 绝迹的星 
// Created on 2023/11/20
#include "Status.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i, j; //该非零元的行下标和列下标
    int e;
} Triple; //Triple:三倍的,三重的. 在这里指三元组

typedef struct {
    int mu, nu, tu; //矩阵的行数, 列数和非零元个数
    Triple *data;// 书上的写法:Triple data[MAXSIZE + 1];
} SMatrix;

Status CreateSMatrix(SMatrix *M) {
    printf("请输入矩阵的行数,列数,");
    printf("以及要存入的非零元的个数(以空格分隔):\n");
    fflush(stdout);

    scanf("%d %d %d", &M->mu, &M->nu, &M->tu);
    getchar(); // 读取换行符
    M->data = malloc(sizeof(Triple) * M->tu); // 分配内存
    if (!M->data) exit(ERROR);  //内存分配失败

    for (int k = 0; k < M->tu; k++) { //将值输入到数组中
        printf("请依次输入第%d个元素的行下标", k + 1);
        printf(",列下标和值(以空格分隔):\n");
        fflush(stdout);
        scanf("%d %d %d", &M->data[k].i, &M->data[k].j, &M->data[k].e);
        getchar(); // 读取换行符
    }
    return OK;
}

Status DestroySMatrix(SMatrix *M) {
    free(M->data);
    return OK;
}

Status CopySMatrix(SMatrix M, SMatrix *T) {
    T->tu = M.tu;
    T->nu = M.nu;
    T->mu = M.mu;
    for (int k = 0; k < M.tu; k++) {
        T->data[k].e = M.data[k].e;
        T->data[k].j = M.data[k].j;
        T->data[k].i = M.data[k].i;
    }
    return OK;
}

Status SubSMatrix(SMatrix M, SMatrix N, SMatrix *Q) {
    for (int k = 0; k < N.tu; k++) {
        N.data[k].e = -N.data[k].e;
    }
    free(Q->data);
    Q->data = malloc(sizeof(Triple) * (M.tu + N.tu)); //分配内存
    Q->tu = 0, Q->mu = M.mu, Q->nu = M.nu;
    int p = 0, q = 0;

    while (p < M.tu && q < N.tu) {
        int kM = (M.data[p].i - 1) * M.nu + M.data[p].j; //计算此时M,N中非零元的位序,方便比较
        int kN = (N.data[q].i - 1) * N.nu + N.data[q].j;
        if (kM == kN) {           //如果相等,就让两个非零元相加,相加值不为零则加入Q
            int e = M.data[p].e + N.data[q].e;
            if (e != 0) {
                Q->data[Q->tu].e = e;
                Q->data[Q->tu].i = M.data[p].i;
                Q->data[Q->tu].j = M.data[p].j;
                Q->tu++;
            }
            p++;
            q++;
        } else if (kM < kN) {      //M中的元素在N元素前面
            Q->data[Q->tu].e = M.data[p].e;
            Q->data[Q->tu].i = M.data[p].i;
            Q->data[Q->tu].j = M.data[p].j;
            Q->tu++;
            p++;
        } else if (kM > kN) {    //N中的元素在M元素前面
            Q->data[Q->tu].e = N.data[q].e;
            Q->data[Q->tu].i = N.data[q].i;
            Q->data[Q->tu].j = N.data[q].j;
            Q->tu++;
            q++;
        }
    }
    while (p < M.tu) {         //M中有剩余元素
        Q->data[Q->tu].e = M.data[p].e;
        Q->data[Q->tu].i = M.data[p].i;
        Q->data[Q->tu].j = M.data[p].j;
        Q->tu++;
        p++;
    }
    while (q < N.tu) {       //N中有剩余元素
        Q->data[Q->tu].e = N.data[q].e;
        Q->data[Q->tu].i = N.data[q].i;
        Q->data[Q->tu].j = N.data[q].j;
        Q->tu++;
        q++;
    }
    return OK;
}

Status FastTransPoseSMatrix(SMatrix M, SMatrix *T) {
    //先清空矩阵T,再为矩阵T分配内存空间
    if (T->data) free(T->data);
    T->data = malloc(sizeof(Triple) * M.tu);
    if (!T->data) exit(ERROR);
    //对矩阵T的行数,列数,及非零元素个数进行赋值
    T->tu = M.tu;
    T->nu = M.mu;
    T->mu = M.nu;

    if (T->tu) { // 矩阵T不为空
        return OK;
    }
    //求M中每一列含非零元的个数
    int num[M.nu + 1];
    for (int i = 0; i < M.nu; i++) { //初始化数组(变长数组不支持声明的时候初始化)
        num[i] = 0;
    }
    // 开始记录
    for (int i = 0; i < M.tu; i++) {
        num[M.data[i].j]++;
    }
    // 求第col列中第一个非零元在T->base中的序号
    int cpot[M.nu + 1];
    cpot[1] = 1;
    for (int i = 2; i <= M.nu; i++) {
        cpot[i] = cpot[i - 1] + num[i - 1];
    }

    for (int p = 0; p < M.tu; p++) {
        int col = M.data[p].j;
        int q = cpot[col] - 1;   // 根据p所指向的列数和cpot数组可以推出对应在矩阵T->data中的序号
        T->data[q].j = M.data[p].i;
        T->data[q].i = M.data[p].j;
        T->data[q].e = M.data[p].e;
        cpot[col]++; //M矩阵中同一列有多个元素时,使之更新到下一个
    } //for
    return OK;
}

Status TransPoseSMatrix(SMatrix M, SMatrix *T) {
    //先清空矩阵T,再为矩阵T分配内存空间
    if (T->data) free(T->data);
    T->data = malloc(sizeof(Triple) * M.tu);
    if (!T->data) exit(ERROR);
    //对矩阵T的行数,列数,及非零元素个数进行赋值
    T->tu = M.tu;
    T->nu = M.mu;
    T->mu = M.nu;
    if (T->tu) {
        int q = 0;
        for (int col = 1; col <= M.nu; col++) //将矩阵M中的每个列遍历一遍
            for (int p = 0; p < M.tu; p++)   //将矩阵M中的非零元素遍历一遍
                if (M.data[p].j == col) {    //找到非零元素的列后,就进行赋值
                    T->data[q].i = M.data[p].j;
                    T->data[q].j = M.data[p].i;
                    T->data[q].e = M.data[p].e;
                    q++;
                } // if
    } //if
    return OK;
}

Status MultSMatrix(SMatrix A, SMatrix B, SMatrix *C) {
    if (A.nu != B.mu) return ERROR; //如果A的列数不等于B的行数，不能相乘
    if (!C->data) free(C->data);
    C->data = malloc(sizeof(Triple) * A.mu * B.nu);
    if (!C->data) exit(ERROR);
    C->mu = A.mu;
    C->nu = B.nu;
    C->tu = 0; //初始化结果矩阵
    if (A.tu * B.tu) { //非零元素个数都不为0
        for (int a = 0; a < A.tu; ++a) { //遍历A中的非零元
            for (int b = 0; b < B.tu; ++b) { //遍历B中的非零元
                if (A.data[a].j == B.data[b].i) { //如果A中元素的列下标等于B中元素的行下标
                    int c;
                    for (c = 0; c < C->tu; ++c) { //在C中查找是否已有对应位置的元素
                        if (C->data[c].i == A.data[a].i && C->data[c].j == B.data[b].j) {
                            C->data[c].e += A.data[a].e * B.data[b].e; //如果有，累加上乘积
                            break;
                        }
                    }
                    if (c == C->tu) { //如果没有找到对应位置的元素
                        C->data[C->tu].i = A.data[a].i;
                        C->data[C->tu].j = B.data[b].j;
                        C->data[C->tu].e = A.data[a].e * B.data[b].e; //新建一个元素
                        C->tu++; //非零元个数增加
                    }
                }
            }
        }
    }
    return OK;
}

Status AddSMatrix(SMatrix M, SMatrix N, SMatrix *Q) {
    free(Q->data);
    Q->data = malloc(sizeof(Triple) * (M.tu + N.tu)); //分配内存
    Q->tu = 0, Q->mu = M.mu, Q->nu = M.nu;
    int p = 0, q = 0;

    while (p < M.tu && q < N.tu) {
        int kM = (M.data[p].i - 1) * M.nu + M.data[p].j; //计算此时M,N中非零元的位序,方便比较
        int kN = (N.data[q].i - 1) * N.nu + N.data[q].j;
        if (kM == kN) {           //如果相等,就让两个非零元相加,相加值不为零则加入Q
            int e = M.data[p].e + N.data[q].e;
            if (e != 0) {
                Q->data[Q->tu].e = e;
                Q->data[Q->tu].i = M.data[p].i;
                Q->data[Q->tu].j = M.data[p].j;
                Q->tu++;
            }
            p++;
            q++;
        } else if (kM < kN) {
            Q->data[Q->tu].e = M.data[p].e;
            Q->data[Q->tu].i = M.data[p].i;
            Q->data[Q->tu].j = M.data[p].j;
            Q->tu++;
            p++;
        } else if (kM > kN) {
            Q->data[Q->tu].e = N.data[q].e;
            Q->data[Q->tu].i = N.data[q].i;
            Q->data[Q->tu].j = N.data[q].j;
            Q->tu++;
            q++;
        }
    }
    while (p < M.tu) {
        Q->data[Q->tu].e = M.data[p].e;
        Q->data[Q->tu].i = M.data[p].i;
        Q->data[Q->tu].j = M.data[p].j;
        Q->tu++;
        p++;
    }
    while (q < N.tu) {
        Q->data[Q->tu].e = N.data[q].e;
        Q->data[Q->tu].i = N.data[q].i;
        Q->data[Q->tu].j = N.data[q].j;
        Q->tu++;
        q++;
    }
    return OK;
}

Status PrintSMatrix(SMatrix M) {
    int k = 0;
    for (int m = 0; m < M.mu; m++) {
        for (int n = 0; n < M.nu; n++) {
            if (M.data[k].i == m + 1 && M.data[k].j == n + 1)  //为非零元素
                printf("%d\t", M.data[k++].e);
            else                                    //为零元素
                printf("0\t");
        }
        printf("\n");
    }
    printf("\n");
    return OK;
}

int main() {
    SMatrix M;
    CreateSMatrix(&M);
    SMatrix N;
    CreateSMatrix(&N);
    FastTransPoseSMatrix(M, &N);
    PrintSMatrix(N);
    /*
3 3 3
1 1 1
1 2 2
1 3 3
3 3 0
     */
}
