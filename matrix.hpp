#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif
#ifndef CSTRING
#define CSTRING
#include<cstring>
#endif
template<class T>
class Matrix {

private:
    size_t r,c,channel;
    T *num;
    int* used_time;
    // int ROIc,ROIr;感兴趣区域，但是对于简单的线性变换&矩阵乘没有用

public:
    int get_used_time() {
        return *used_time;
    }

    int getRow() {
        return r;
    }
    int getCol() { 
        return c;
    }
    int getChannel() {
        return channel;
    }

    Matrix(size_t row=0, size_t col=0, size_t channel=1, T* nums = NULL);
    Matrix(size_t row=0, size_t col=0, size_t channel=1, std::ifstream & fin=NULL);
    Matrix(const Matrix& src);
    ~Matrix();
    
    Matrix operator!() const;//reverse
    Matrix operator+(T num) const;
    Matrix operator+(const Matrix &b)const;
    Matrix& operator+=(T num);
    Matrix& operator+=(const Matrix &b);
    Matrix operator-(T num) const;
    Matrix operator-(const Matrix &b)const;
    Matrix& operator-=(T num);
    Matrix& operator-=(const Matrix &b);
    Matrix operator*(T num) const;
    Matrix operator*(const Matrix &b)const;
    Matrix& operator*=(T num);
    Matrix& operator*=(const Matrix &b);
    

    template<class Type>
    friend std::ostream & operator<<(std::ostream &os, Matrix<Type>& mat);
};

template<typename T>
Matrix<T>::Matrix(size_t row=0, size_t col=0, size_t channel=1, T* num = NULL) {
    if(row < 0 || col < 0) {
        std::cerr << "Illegal input row or col" << std::endl;
        row=col=0;
    }
    if(channel < 1) {
        std::cerr << "Illegal input channel" << std::endl;
        channel=1;
    }
    this ->used_time = new int;
    *(this ->used_time) = 1;
    this ->r = row;
    this ->c = col;
    this ->channel = channel;
    this ->num = new T[row * col * channel];
    if(num) {
        memcpy(this ->num, num, sizeof(T)*row*col*channel);
    }
}

template<typename T>
Matrix<T>::Matrix(size_t row=0, size_t col=0, size_t channel=1, std::ifstream & fin=NULL) {
    if(row < 0 || col < 0) {
        std::cerr << "Illegal input row or col" << std::endl;
        row=col=0;
    }
    if(channel < 1) {
        std::cerr << "Illegal input channel" << std::endl;
        channel=1;
    }
    this ->used_time = new int;
    *(this ->used_time) = 1;
    this ->r = row;
    this ->c = col;
    this ->channel = channel;
    this ->num = new T[row * col * channel];
    if(fin == NULL) {
        std::cerr << "Illegal input file" << std::endl;
    }
    else {
        while(!fin.eof()) {
            std::string line;
            getline(fin, line);
            std::stringstream ipt(line);
            T tmp;
            ize_t pos=0;
            while(ipt >> tmp) {
                this -> nums[pos++] = tmp;
            }    
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix& src) {
    this ->r = src ->r;
    this ->c = src ->c;
    this ->channel = src ->channel;
    this ->used_time = src ->used_time;
    this ->num = src ->num;
    *(this ->used_time)++;
}

template<typename T>
Matrix<T>::~Matrix() {
    *(this ->used_time)--;
    if(*(this ->used_time) == 0) {
        delete[] this -> used_time;
        delete[] this -> nums;
    }
}