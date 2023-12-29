// Author: 绝迹的星 
// Created on 2023/12/15
// 模拟数据库

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fileapi.h>


const char *dataPath = "E:\\CLionProject\\CProjects\\DataStructure\\LibraryManagementSystem\\data.txt";
const int maxLineCount = 100, maxLineLen = 100;


typedef struct Data {
    char **lines;
    int count;
} Data;//文件数据,count行

typedef struct SelectData {
    Data *data;
    char *idOrTitle;
    int index;
} SelectData;//通过idOrTitle查询数据,data为总体数据,index为查询到的索引(-1表示不存在)

enum Method {
    Add = 1, Delete, Update, Select
};

const char *method[5] = {"", "添加", "删除", "更新", "查询"};

/**
 * 获取当前全局id
 */
int getId() {
    FILE *fp;
    fp = fopen(dataPath, "r");
    fseek(fp, 0, SEEK_END);
    int c;
    long pos = ftell(fp) - 2;
    while (pos > 0) {
        fseek(fp, --pos, SEEK_SET);
        c = fgetc(fp);
        if (c == '\n') {
            break;
        }
    }
    int id = 0;
    char title[maxLineLen];
    fscanf_s(fp, "%d %[^\n]", &id, title);
    fclose(fp);
    return id;
}

/**
 * 从文件里加载
 * @return
 */
Data *loadData() {
    Data *data = malloc(sizeof(Data));
    data->count = 0;
    data->lines = malloc(sizeof(char *) * maxLineCount);
    FILE *file = fopen(dataPath, "r");
    // 读取文件内容并保存到数组中
    while (true) {
        data->lines[data->count] = malloc(sizeof(char) * maxLineLen);
        char *response = fgets(data->lines[data->count], maxLineLen, file);
        if (response == NULL)break;
        data->count++;
    }
    fclose(file);
    return data;
}

char *getQueryFields();

void AddBook(int *global_id);

int selectById(char lines[100][100], int count, int id);

int selectByTitle(char lines[100][100], int count, char *title);

void DeleteBook();

void UpdateBook();

SelectData *SelectBook();

int doSelect(Data *data, char *idOrTitle);

void MainMenu();

void publicSelect(SelectData *selectData);

void writeBack(const Data *data, int index);

int main() {
    FILE *fp;
    fp = fopen(dataPath, "a");
    if (fp == NULL) {
        printf("ERROR:文件无法创建\n");
        exit(-1);
    }
    int global_id = getId() + 1;//全局书籍id
    while (true) {
        MainMenu();
        int ch = getchar() - '0';
        getchar();
        if (ch == Add) {
            printf("----------%s----------\n", method[ch]);
            AddBook(&global_id);
        } else if (ch == Delete) {
            printf("----------%s----------\n", method[ch]);
            DeleteBook();
        } else if (ch == Update) {
            printf("----------%s----------\n", method[ch]);
            UpdateBook();
        } else if (ch == Select) {
            printf("----------%s----------\n", method[ch]);
            SelectBook();
        } else {
            break;
        }
    }
    return 0;
}

void MainMenu() {
    printf("---------主界面----------\n");
    printf("1.添加书籍\n");
    printf("2.删除书籍\n");
    printf("3.修改书籍\n");
    printf("4.搜索书籍\n");
    printf("按其他任意键退出\n");
    fflush(stdout);
}

void UpdateBook() {
    SelectData *selectData = SelectBook();
    if (selectData == NULL)return;
    printf("请输入修改后的书名\n");
    fflush(stdout);
    char title[100];
    scanf_s("%s", title);
    int len = strlen(title);
    title[len] = '\n';
    getchar();
    //修改
    int start;
    for (start = 0; start < maxLineLen; start++) {
        if (!isdigit(selectData->data->lines[selectData->index][start]))break;
    }
    strcpy(selectData->data->lines[selectData->index] + start + 1, title);
    //回写
    writeBack(selectData->data, -1);
    printf("修改成功\n");
}

SelectData *SelectBook() {
    SelectData *selectData = malloc(sizeof(SelectData));
    publicSelect(selectData);//加载数据
    if (selectData->index == -1) {
        printf("没有找到这本书\n");
        return NULL;
    }
    printf("%s", selectData->data->lines[selectData->index]);
    return selectData;
}

char *getQueryFields() {//获取查询字段
    printf("请输入书名或者书籍id:");
    fflush(stdout);
    char *idOrTitle = malloc(sizeof(char) * 100);
    scanf("%s", idOrTitle);
    getchar();
    return idOrTitle;
}

int doSelect(Data *data, char *idOrTitle) {
    char lineCopy[maxLineCount][maxLineLen]; // 用副本查找,防止破坏原数据
    for (int i = 0; i < data->count; i++) {
        strcpy(lineCopy[i], data->lines[i]);
    }
    if (isdigit(idOrTitle[0])) {
        return selectById(lineCopy, data->count, atoi(idOrTitle));
    } else {
        return selectByTitle(lineCopy, data->count, idOrTitle);
    }
}

void DeleteBook() {
    SelectData *selectData = SelectBook();
    printf("%s", selectData->data->lines[selectData->index]);
    selectData->data->count--;
    //写回文件中
    writeBack(selectData->data, selectData->index); //从数据中删除该项
    printf("删除成功\n");
}

void writeBack(const Data *data, int index) {
    FILE *file = fopen(dataPath, "w");
    for (int i = 0; i < data->count; i++) {
        if (i != index) fputs(data->lines[i], file);
    }
    fclose(file);
}

int selectByTitle(char lines[maxLineCount][maxLineLen], int count, char *title) {
    int lenTitle = strlen(title);
    for (int i = 0; i < count; i++) {
        char *bookTitle = strtok(lines[i], " ");
        bookTitle = strtok(NULL, " ");
        if (bookTitle == NULL)continue;
        if (strncmp(bookTitle, title, lenTitle) == 0) {
            return i;
        }
    }
    return -1;
}

int selectById(char lines[maxLineCount][maxLineLen], int count, int id) {
    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int line_id = atoi(strtok(lines[mid], " "));
        if (line_id < id) {
            left = mid + 1;
        } else if (line_id > id) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

void AddBook(int *global_id) {
    char title[100];
    printf("请输入书名:\n");
    fflush(stdout);
    scanf("%s", title);
    getchar();
    // 检查重复
    Data *data = loadData();
    int index = doSelect(data, title);
    if (index != -1) {
        printf("该书已存在\n");
        return;
    }
    //写入到文件
    FILE *fp;
    fp = fopen(dataPath, "a");
    fprintf(fp, "%d %s\n", *global_id, title); // 向文件中追加写入字符串
    fclose(fp);
    fflush(fp);
    *global_id = *global_id + 1;
    printf("成功添加\n");

}

void publicSelect(SelectData *selectData) {
    selectData->idOrTitle = getQueryFields();
    selectData->data = loadData();
    selectData->index = doSelect(selectData->data, selectData->idOrTitle);
}