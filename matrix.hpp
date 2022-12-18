#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif
template<class T>
class Matrix {

private:
    int row;
    int col;
    int channel;
    T *nums;
    int ROIBeginRow;
    int ROIBeginCol;
    int ROIRow;
    int ROICol;
    int span;
    static int num_matrices;
    int* ref_count;

public:
    //返回矩阵对象存在个数
    static int Matrix_num();
    //返回共用该元素数组矩阵对象个数
    int get_ref_count(){
        return ref_count[0];
    }

    int getRow(){
        return row;
    }
    int getCol(){
        return col;
    }
    int getChannel(){
        return channel;
    }
    int getSpan(){
        return span;
    }

    //构造器
    //根据传入数组来创建矩阵的构造函数
    Matrix(int row = 3, int col = 3, int channel = 1, T* nums = nullptr, int ROIBeginRow = 0, int ROIBeginCol = 0, int ROIRow = 0, int ROICol = 0, int *ref_count = nullptr, int span = 0);
    //根据传入文件流来创建矩阵的构造函数
    Matrix(int row, int col, int channel, std::ifstream & fin, int size);
    
    //向量点乘
    static T dotmul(int r1, T* nums1, int r2, T* nums2);

    //复制构造器
    Matrix(const Matrix&);
    //析构函数
    ~Matrix();
};