// Author: 绝迹的星
// Created on 2023/11/24

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define ElemType int //矩阵内的数据类型
#define MAXSIZE 100   //矩阵内最大元素个数

//三元组结构
typedef struct Triple {
    int i;  //元素所在行
    int j;  //元素所在列
    ElemType e;  //元素值
} Triple;

//稀疏矩阵
typedef struct SMatrix {
    Triple data[MAXSIZE]; // 0 三元组，存放有效数据
    int mu; //稀疏矩阵行数
    int nu; //稀疏矩阵列数
    int tu; //非零元素个数
} SMatrix;

//通过输入创建稀疏矩阵
void CreateMatrixByScanf(SMatrix *M) {
    //读数据：矩阵的行mu，矩阵的列nu
    printf("输入行数和列数:");
    fflush(stdout);
    scanf("%d %d", &M->mu, &M->nu);

    //读取矩阵内的数据
    int value;  //临时存放读取的值，用来判断读取的值是否为0
    int k = 0; //记录非零元素个数
    for (int i = 0; i < M->mu; ++i) {
        for (int j = 0; j < M->nu; ++j) {
            //读取矩阵内的一个元素
            scanf("%d", &value);
            if (value != 0) {//判断值是不是为0
                //不为0，将值以三元组的形式存入
                M->data[k].e = value; //值
                M->data[k].i = i;   //所在行
                M->data[k].j = j;   //所在列
                k++; //非零元素个数加一
            }
        }
    }
    M->tu = k; //更改稀疏矩阵中非零元素的个数
}

//按三元组形式输出稀疏矩阵
void PrintMatrixTriplet(SMatrix *M) {
    //打印稀疏矩阵的总函数和列数
    printf("row=%d, col=%d\n", M->mu, M->nu);
    //打印三元组中存放的稀疏矩阵中所有非零元素的所在行、所在列以及值
    for (int i = 0; i < M->tu; ++i) {
        printf("(%d, %d, %d)\n", M->data[i].i, M->data[i].j, M->data[i].e);
    }
    fflush(stdout);
}

//按矩阵形式打印输出矩阵
void PrintMatrix(SMatrix *M) {
    int **p = NULL;
    int i, j;
    // 申请全部行的首指针
    p = (int **) malloc(M->mu * sizeof(int *));
    assert(p != NULL);
    for (i = 0; i < M->mu; i++) {
        //申请列的指针
        *(p + i) = (int *) malloc(M->nu * sizeof(int));
        if (*(p + i) == NULL) {
            return;
        }
    }
    //  初始化数组
    for (i = 0; i < M->mu; i++) {
        for (j = 0; j < M->nu; j++) {
            p[i][j] = 0;
        }
    }

    //将非零元素值放入对应位置
    for (i = 0; i < M->tu; ++i) {
        p[M->data[i].i][M->data[i].j] = M->data[i].e;
    }

    //打印
    //打印稀疏矩阵的总函数和列数
    printf("row=%d, col=%d\n", M->mu, M->nu);
    //打印值
    for (i = 0; i < M->mu; i++) {
        for (j = 0; j < M->nu; j++) {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
}


//稀疏矩阵的加法:M+N=T
void AddMatrix(SMatrix *M, SMatrix *N, SMatrix *T) {
    //判断M T两个矩阵是否符合加法运算的条件
    if ((M->mu != N->mu) || (M->nu != N->nu)) {
        return;//不满足退出
    }
    //满足
    T->mu = M->mu; //加法后的行数
    T->nu = M->nu; //加法后的列数
    int q = 0; //用来记录执行矩阵加法后的非零元素个数
    int i = 0, j = 0;

    while ((i < M->tu) && (j < N->tu)) {
        //将非零元素的二维位置转化为一维位置
        int lieM = M->data[i].i * M->nu + M->data[i].j;
        int lieN = N->data[j].i * N->nu + N->data[j].j;
        //判断位置
        if (lieM == lieN) {//位置相同，则将两者进行相加，相加结果非零就将结果存入T
            int r = M->data[i].e + N->data[j].e; //计算运算的结果,如果要计算M-N,将相加改为相减,存N时乘以-1
            if (r != 0) {//如果计算结果不为0，则进行存储
                T->data[q].i = M->data[i].i;
                T->data[q].j = M->data[i].j;
                T->data[q].e = r;
                q++;
            }
            //如果计算结果为0，则不进行存储,直接下移
            i++;
            j++;
        } else if (lieM < lieN) {//M在前，则只需要将M中的非零元素存入T
            T->data[q].i = M->data[i].i;
            T->data[q].j = M->data[i].j;
            T->data[q].e = M->data[i].e;
            q++;
            i++;
        } else if (lieM > lieN) {//N在前，则只需要将N中的非零元素存入T
            T->data[q].i = N->data[j].i;
            T->data[q].j = N->data[j].j;
            T->data[q].e = N->data[j].e;
            q++;
            j++;
        }
    }

    while (i < M->tu) {//只剩M中有元素，则将M中剩余的元素加入T
        T->data[q].i = M->data[i].i;
        T->data[q].j = M->data[i].j;
        T->data[q].e = M->data[i].e;
        q++;
        i++;
    }
    while (j < N->tu) {//只剩N中有元素，则将N中剩余的元素加入T
        T->data[q].i = N->data[j].i;
        T->data[q].j = N->data[j].j;
        T->data[q].e = N->data[j].e;
        q++;
        j++;
    }
    T->tu = q; //修改T中非零元素个数
}


//进行两个稀疏矩阵之间的乘法，返回值为乘积矩阵
void MulMatrix(SMatrix *M, SMatrix *N, SMatrix *T) {
    if (M->nu != N->mu) return;

    int p, j, q, i, r, k, t;
    //用于结果的暂存
    int *temp = (int *) malloc(sizeof(int) * N->nu);
    assert(temp != NULL);

    //num[]保存每一行的非零元素个数  rpos[]保存每行元素起始地址
    int *num = (int *) malloc(sizeof(int) * N->mu);
    assert(num != NULL);
    int *rpot = (int *) malloc(sizeof(int) * N->mu);
    assert(rpot != NULL);


    T->mu = M->mu;
    T->nu = N->nu;
    //当M或N中的非零元素为0时
    if (M->tu * N->tu == 0) {
        T->tu = 0;
        return;
    }
    //计算N矩阵中每行非0元素的个数
    for (i = 0; i < N->mu; i++)
        num[i] = 0;
    for (i = 0; i < N->tu; i++)
        num[N->data[i].i]++;
    rpot[0] = 0;
    //计算N矩阵中每行首位非0元素的位置
    for (i = 1; i < N->mu; i++)
        rpot[i] = rpot[i - 1] + num[i - 1];
    r = 0;//记录当前T矩阵中非0元素的个数
    p = 0;//指示当前M矩阵中非零元素的位置
    //进行矩阵的乘积运算
    for (i = 0; i < M->mu; i++) {
        //将Tij的累加器初始化
        for (j = 0; j < N->nu; j++)
            temp[j] = 0;
        //求Tij第i行的元素集合
        while (i == M->data[p].i) {
            k = M->data[p].j;//获取M矩阵中第p个非零元素的列值
            //确定N中的k行的非零元素在N.data中的下限位置
            if (k < N->mu - 1)
                t = rpot[k + 1];
            else
                t = N->tu;
            //将N中第k行的每一列非零元素与M中非零元素记录到累加器中
            for (q = rpot[k]; q < t; q++) {
                j = N->data[q].j;
                temp[j] += M->data[p].e * N->data[q].e;
            }
            p++;
        }
        //将第i行的结果赋值给C矩阵
        for (j = 0; j < N->nu; j++) {
            if (temp[j] != 0) {
                T->data[r].i = i;
                T->data[r].j = j;
                T->data[r].e = temp[j];
                r++;
            }
        }
    }
    T->tu = r;

    //释放空间
    free(temp);
    free(num);
    free(rpot);
}

//拷贝稀疏矩阵，将M拷贝到T
void CopyMatrix(SMatrix *M, SMatrix *T) {
    T->mu = M->mu; //拷贝行
    T->nu = M->nu; //拷贝列
    T->tu = M->tu; //拷贝稀疏矩阵非零元素个数

    //将M中每个非零元素以三元组形式拷贝到T
    for (int i = 0; i < M->tu; i++) {
        T->data[i].i = M->data[i].i; //非零元素所在行
        T->data[i].j = M->data[i].j; //非零元素所在列
        T->data[i].e = M->data[i].e; //非零元素的值
    }
}
//稀疏矩阵的转置：将 M 转置存入 T
/*
基本思想：按列优先的形式对 M 中的非零元素进行搜索,
然后将非零元素的所在M中的行列互换之后存入T，此时T的行数
等于M的列数，T的列数等于M的行数。
*/
void TransposeMatrix(SMatrix *M, SMatrix *T) {
    T->mu = M->nu;  //将M的列数传给T行数
    T->nu = M->mu;  //将M的行数传给T列数
    T->tu = M->tu;  //将M中的非零元素个数传给T
    if (M->tu == 0) {//判断非零元素个数是否为零
        return;
    }
    int q = 0;//记录转置后的非零元素在T矩阵中的存放位置
    //按列优先的形式
    for (int col = 0; col < M->nu; ++col) {
        //对 M 中的非零元素进行搜索
        for (int p = 0; p < M->tu; ++p) {
            if (M->data[p].j == col) {//如果为第col列的非零元素
                T->data[q].i = M->data[p].j; //将M中col列中的非零元素的列传给T中非零元素的行
                T->data[q].j = M->data[p].i; //将M中col列中的非零元素的行传给T中非零元素的列
                T->data[q].e = M->data[p].e; //将M中col列中的非零元素的值传给T中非零元素的值
                q++;//记录该非零元素在T中的存放位置
            }
        }

    }
}

//快速转置
void FastTransposeMatrix(SMatrix *M, SMatrix *T) {
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;

    //为num向量开辟空间：num[col]表示矩阵M中第col列中非零元的个数
    int *num = (int *) malloc(sizeof(int) * M->nu);//需要的最大空间为M中列的数量个
    assert(num != NULL);
    //为cpot向量开辟空间：cpot[col]指示M中第col列的第一个未转置的非零元素在T->data中的恰当位置
    int *cpot = (int *) malloc(sizeof(int) * M->nu);//需要的最大空间为M中列的数量个
    assert(cpot != NULL);

    //判断非零元素个数是否为零
    if (T->tu != 0) {//不为零
        //初始化num向量
        for (int col = 0; col < M->nu; ++col) {
            num[col] = 0;
        }
        //为num向量赋值
        for (int t = 0; t < M->tu; ++t) //搜索M中所有非零元素
        {
            /*
            在搜索M所有非零元素的过程中，遇到相应列的非零元素就让num[col]的值加一，
            其中col指的是对应的列，这样就实现了：对每列非零元素个数的统计并存入num[col]中
            */
            num[M->data[t].j]++;
        }

        /*
            为cpot向量赋值
            此时M中的所有非零元素都还未进行转置，所以此时cpot[col]指示M中
            第col列的第一个非零元素在T->data中的恰当位置
        */
        cpot[0] = 0;  //第0列的第一个非零元素在T->data中的位置在0下标处
        //为cpot向量剩下的位置赋值
        int col;
        for (col = 1; col < M->nu; ++col) {
            //从1列位置开始，cpot[col]的值等于前一列非零元素在T->data中的位置加上前一列非零元素的个数
            cpot[col] = cpot[col - 1] + num[col - 1];
        }

        //利用num向量和cpot向量实现M矩阵的转置（转置结果存放在T矩阵中）
        int q = 0; //用来临时存放提取的cpot[col]的值
        for (int p = 0; p < M->tu; ++p)//遍历M中的所有非零元素
        {
            col = M->data[p].j; //获取非零元素的列值
            q = cpot[col];     //由这个列到cpot向量中获取该列第一个未转置的非零元素在T->data中的恰当位置
            //将M中的这个非零元素转置存入T
            T->data[q].i = M->data[p].j; //M中的列--->T中的行
            T->data[q].j = M->data[p].i; //M中的行--->T中的列
            T->data[q].e = M->data[p].e; //M中的值--->T中的值
            /*
             将第col列的第一个未转置的非零元素在T->data中的位置加一
            （因为原先T中的那个位置已经被插入，下一个转置过来的元素只能存入下一个位置）
            */
            cpot[col]++;
        }
    }
    free(num); //释放为num向量的空间
    free(cpot);//释放cpot向量的空间
}

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

int main() {
    SMatrix A;
    CreateMatrixByScanf(&A);
    PrintMatrix(&A);
}