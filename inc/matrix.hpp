#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <iostream>
#include "struct.hpp"

class Matrix{
    public:
        Matrix(const int& rows, const int& cols);
        Matrix(const Matrix& A);
        Matrix(std::vector<Point> x, int deg);
        ~Matrix();
        float & operator[](const int &index) const ;
        void operator=(const Matrix& A );
        Matrix operator*(const Matrix& A);
        Matrix operator+(const Matrix& A);
        Matrix operator-(const Matrix& A);
        Matrix operator^(const int& power) ;
        Matrix T() const;
        Matrix rowReduc() const;
        void id();
        void display();
        inline int getRow(const Matrix& A){return A.n_rows;};
        inline int getCol(const Matrix& A){return A.n_cols;};
    
    private:
        float* M;
        int n_rows;
        int n_cols;
};

#endif