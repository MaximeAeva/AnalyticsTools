#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include "struct.hpp"

template <class T>
class Matrix{
    public:
        Matrix(const int& rows, const int& cols);
        Matrix(const Matrix<T>& A);
        Matrix(std::vector<Point> x, int deg);
        ~Matrix();
        T & operator[](const int &index) const ;
        void operator=(const Matrix<T>& A );
        Matrix<T> operator*(const Matrix<T>& A);
        Matrix<T> operator+(const Matrix<T>& A);
        Matrix<T> operator-(const Matrix<T>& A);
        Matrix<T> operator^(const int& power) ;
        Matrix<T> operator/(const T& value) ;
        Matrix<T> Trsp() const;
        T norm() const;
        Matrix<T> rowReduc() const;
        void ones(const int& rows, const int& cols) const;
        void id();
        void display();
        T sum();
        T eigenValue(const Matrix<T>& v);
        inline int getRow(const Matrix<T>& A){return A.n_rows;};
        inline int getCol(const Matrix<T>& A){return A.n_cols;};
        inline int getSize(){return (this->n_cols*this->n_rows);};
    
    private:
        T* M;
        int n_rows;
        int n_cols;
};

/**
 * @brief Construct a new Matrix:: Matrix object
 * 
 * @param rows 
 * @param cols 
 */
template <class T>
Matrix<T>::Matrix(const int& rows,const int& cols )
{
    this->n_rows=rows;
    this->n_cols = cols;
    M = new T [rows*cols]();          
}

/**
 * @brief Copy from A
 * 
 * @param A 
 */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& A)
{
    this->n_rows=getRow(A);
    this->n_cols = getCol(A);
    this->M=new T [n_rows*n_cols]();
    for(int i=0;i<n_rows;i++)
      for(int j=0;j<n_cols;j++)
        this->M[(i*n_cols)+j]=A[(i*n_cols)+j];            
}

/**
 * @brief Destroy the Matrix:: Matrix object
 * 
 */
template <class T>
Matrix<T>::~Matrix()
{
    M = NULL;
    delete [] M;
}

/**
 * @brief Identity matrix
 * 
 */
template <class T>
void Matrix<T>::id()
{
    if(n_rows==n_cols)
        for(int i=0;i<n_rows;i++) this->M[(i*n_cols)+i]++;
}

/**
 * @brief Fill with one
 * 
 * @tparam T 
 * @param rows 
 * @param cols 
 */
template <class T>
void Matrix<T>::ones(const int& rows, const int& cols) const
{
    for(int i=0;i<M.getSize();i++) M[i]++;
}

/**
 * @brief VanderMonde matrix from f :
 * 
 * x1^0 , x1^1, ..., x1^deg
 * .
 * .
 * .
 * xn^0, . . . . . , xn^deg
 * 
 * @param x Data to prepare
 * @param deg polynomialdegree
 */
template <class T>
Matrix<T>::Matrix(std::vector<Point> x, int deg)
{
    
    this->n_rows=x.size();
    this->n_cols = deg;
    this->M=new T [x.size()*deg]();
    for(int i=0;i<x.size();i++)
      for(int j=0;j<deg;j++)
        this->M[(i*n_cols)+j]=pow(x[i].x, j); 
}

/**
 * @brief Access element
 * 
 * @param index index to access
 * @return float*& 
 */
template <class T>
T & Matrix<T>::operator[](const int &index) const
{
  return  this->M[index];
}

/**
 * @brief Copy A
 * 
 * @param A 
 */
template <class T>
void Matrix<T>::operator=(const Matrix<T>& A)
{
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                this->M[(i*n_cols)+j]=A[(i*n_cols)+j]; 
    }
}

/**
 * @brief multiply by A (on the right)
 * 
 * @param A 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& A)
{
    Matrix<T> R(n_rows, getCol(A));
    if(getRow(A)==this->n_cols)
    {
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->getCol(A);j++)
                for(int k = 0; k<n_cols; k++)
                    R[(i*getCol(A))+j]+=this->M[(i*n_cols)+k]*A[(k*getCol(A))+j]; 
    }
    return R;
}

/**
 * @brief element element addition (no cast)
 * 
 * @param A 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& A)
{
    Matrix<T> R(n_rows, n_cols);
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {   
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[(i*n_cols)+j]=this->M[(i*n_cols)+j]+A[(i*n_cols)+j]; 
    }
    return R;
}

/**
 * @brief substract A
 * 
 * @param A 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& A)
{
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {
        Matrix<T> R(n_rows, n_cols);
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[(i*n_cols)+j]=this->M[(i*n_cols)+j]-A[(i*n_cols)+j]; 
    }
}

template <class T>
Matrix<T> Matrix<T>::operator^(const int& power)
{

}

/**
 * @brief Divide by value
 * 
 * @param value 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::operator/(const T& value)
{
    Matrix<T> R(n_rows, n_cols);
    for(int i = 0; i<n_rows; i++)
        for(int j = 0; j<n_cols; j++)
            R[(i*n_cols)+j] += this->M[(i*n_cols)+j]/value;
    return R;
}

/**
 * @brief Transpose
 * 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::Trsp() const
{
    Matrix<T> R(n_cols, n_rows);
    for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[(j*n_rows)+i]=this->M[(i*n_cols)+j];
    return R;
}

/**
 * @brief Frobenius norm
 * 
 * @tparam T 
 * @return T 
 */
template <class T>
T Matrix<T>::norm() const
{
    T value = 0;
    for(int i = 0; i<n_rows; i++)
        for(int j = 0; j<n_cols; j++)
        {
            value += pow(M[(j*n_rows)+i], 2);
        }
    return sqrt(value);
}

/**
 * @brief Return the inverse of a square matrix
 * 
 * @return Matrix 
 */
template <class T>
Matrix<T> Matrix<T>::rowReduc() const
{
    Matrix<T> eye(n_rows, n_cols);
    Matrix<T> R(n_rows, n_cols);
    R.id();
    if(this->n_cols == this->n_rows)
    {   
        for(int i=0;i<n_rows;i++)
            for(int j=0;j<n_cols;j++)
                eye[(i*n_cols)+j]=this->M[(i*n_cols)+j];
        
        int r = 0;
        for(int j = 0; j<n_cols; j++)
        {
            float max = abs(eye[(r*n_cols)+j]);
            int k = r;
            for(int l = r; l<n_cols; l++)
            {
                if(abs(eye[(l*n_cols)+j])>max)
                {
                    max = abs(eye[(l*n_cols)+j]);
                    k = l; 
                }
            }
            if(eye[(k*n_cols)+j]!=0)
            {
                float dv = eye[(k*n_cols)+j];
                for(int l = 0; l<n_cols; l++)
                {
                    R[(k*n_cols)+l]/=dv;
                    eye[(k*n_cols)+l]/=dv;
                }
                if(k!=r)
                {
                    float c;
                    for(int l = 0; l<n_cols; l++)
                    {
                        c = eye[(k*n_cols)+l];
                        eye[(k*n_cols)+l] = eye[(r*n_cols)+l];
                        eye[(r*n_cols)+l] = c;
                        c = R[(k*n_cols)+l];
                        R[(k*n_cols)+l] = R[(r*n_cols)+l];
                        R[(r*n_cols)+l] = c;
                    }
                }
                for(int i = 0; i<n_rows; i++)
                {  
                    if(i!=r)
                    {
                        float ml = eye[(i*n_cols)+j];
                        for(int l = 0; l<n_cols; l++)
                        {
                            R[(i*n_cols)+l]-=R[(r*n_cols)+l]*ml;
                            eye[(i*n_cols)+l]-=eye[(r*n_cols)+l]*ml;
                        }
                    }
                }
                r++;        
            }
        }
    }
    return R;
}

/**
 * @brief Sum components of a matrix
 * 
 * @return float 
 */
template <class T>
T Matrix<T>::sum()
{
    T s = 0;
    for(int i = 0; i<n_rows; i++)
        for(int j = 0; j<n_cols; j++)
            s += this->M[(i*n_cols)+j];
    return s;
}

/**
 * @brief Display Matrix
 * 
 */
template <class T>
void Matrix<T>::display()
{
    int m = 0;
    for(int i = 0; i<this->n_rows; i++)
    {
        for(int j = 0; j<this->n_cols; j++)
        {
            std::ostringstream s;
            s << M[(i*n_cols)+j];
            if(s.str().length() > m) m = s.str().length();
        }
    }
    for(int i = 0; i<this->n_rows; i++)
    {
        std::cout << "|";
        for(int j = 0; j<this->n_cols; j++)
        {
            int k = 0;
            std::ostringstream s;
            s << M[(i*n_cols)+j];
            if((m-s.str().length())%2) k++;
            for(int l = 0; l<(m-s.str().length())/2; l++) std::cout << " ";
            std::cout << M[(i*n_cols)+j];
            for(int l = 0; l<(m-s.str().length())/2+k; l++) std::cout << " ";
            std::cout << "|";
        }
        std::cout << std::endl << std::endl;
    }
}

/**
 * @brief Give the eigenValue associated with the desired vector
 * 
 * @tparam T 
 * @param v 
 * @return T 
 */
template <class T>
T Matrix<T>::eigenValue(const Matrix<T>& v)
{
    T vInv = v/pow(v.norm(), 2);
    return M*v*vInv;
}

#endif