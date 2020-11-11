#include "matrix.hpp"

/**
 * @brief Construct a new Matrix:: Matrix object
 * 
 * @param rows 
 * @param cols 
 */
Matrix::Matrix(const int& rows,const int& cols )
{
    this->n_rows=rows;
    this->n_cols = cols;
    this->M=new float* [cols];
    for(int i =0;i<rows;i++)
    {
       this->M[i]=new float[cols];
    }
    for(int i=0;i<rows;i++)
      for(int j=0;j<cols;j++)
        this->M[i][j]=0;            
}

/**
 * @brief Copy from A
 * 
 * @param A 
 */
Matrix::Matrix(const Matrix& A)
{
    this->n_rows=getRow(A);
    this->n_cols = getCol(A);
    this->M=new float* [n_cols];
    for(int i =0;i<n_rows;i++)
    {
       this->M[i]=new float[n_cols];
    }
    for(int i=0;i<n_rows;i++)
      for(int j=0;j<n_cols;j++)
        this->M[i][j]=A[i][j];            
}

/**
 * @brief Destroy the Matrix:: Matrix object
 * 
 */
Matrix::~Matrix()
{
    for(int i =0;i<this->n_rows;i++)
        delete [] this->M[i]; 
    delete [] this->M;
}

/**
 * @brief Identity matrix
 * 
 */
void Matrix::id()
{
    if(n_rows==n_cols)
        for(int i=0;i<n_rows;i++) this->M[i][i]++;
}

/**
 * @brief Swap abscissa coordinates to matrix like :
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
Matrix::Matrix(std::vector<Point> x, int deg)
{
    
    this->n_rows=x.size();
    this->n_cols = deg;
    this->M=new float* [deg];
    for(int i =0;i<x.size();i++)
    {
       this->M[i]=new float[deg];
    }
    for(int i=0;i<x.size();i++)
      for(int j=0;j<deg;j++)
        this->M[i][j]=pow(x[i].x, j); 
}

/**
 * @brief Access element
 * 
 * @param index index to access
 * @return float*& 
 */
float* & Matrix::operator[](const int &index) const
{
  return  this->M[index];
}

/**
 * @brief Copy A
 * 
 * @param A 
 */
void Matrix::operator=(const Matrix& A)
{
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                this->M[i][j]=A[i][j]; 
    }
}

/**
 * @brief multiply by A (on the right)
 * 
 * @param A 
 * @return Matrix 
 */
Matrix Matrix::operator*(const Matrix& A)
{
    Matrix R(n_rows, getCol(A));
    if(getRow(A)==this->n_cols)
    {
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->getCol(A);j++)
                for(int k = 0; k<n_cols; k++)
                    R[i][j]+=this->M[i][k]*A[k][j]; 
    }
    return R;
}

/**
 * @brief element element addition (no cast)
 * 
 * @param A 
 * @return Matrix 
 */
Matrix Matrix::operator+(const Matrix& A)
{
    Matrix R(n_rows, n_cols);
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {   
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[i][j]=this->M[i][j]+A[i][j]; 
    }
    return R;
}

/**
 * @brief substract A
 * 
 * @param A 
 * @return Matrix 
 */
Matrix Matrix::operator-(const Matrix& A)
{
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {
        Matrix R(n_rows, n_cols);
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[i][j]=this->M[i][j]-A[i][j]; 
    }
}

Matrix Matrix::operator^(const int& power)
{

}

/**
 * @brief Transpose
 * 
 * @return Matrix 
 */
Matrix Matrix::T() const
{
    Matrix R(n_cols, n_rows);
    for(int i=0;i<this->n_cols;i++)
            for(int j=0;j<this->n_rows;j++)
                R[i][j]=this->M[j][i];
}

/**
 * @brief Return the inverse of a square matrix
 * 
 * @return Matrix 
 */
Matrix Matrix::rowReduc() const
{
    Matrix eye(n_rows, n_cols);
    Matrix R(n_rows, n_cols);
    R.id();
    if(this->n_cols == this->n_rows)
    {   
        for(int i=0;i<n_rows;i++)
            for(int j=0;j<n_cols;j++)
                eye[i][j]=this->M[i][j];
        
        int r = 0;
        for(int j = 0; j<n_cols; j++)
        {
            float max = abs(eye[r][j]);
            int k = r;
            for(int l = r; l<n_cols; l++)
            {
                if(abs(eye[l][j])>max)
                {
                    max = abs(eye[l][j]);
                    k = l; 
                }
            }
            if(eye[k][j]!=0)
            {
                for(int l = 0; l<n_cols; l++)
                {
                    R[k][l]/=eye[k][j];
                    eye[k][l]/=eye[k][j];
                }
                if(k!=r)
                {
                    float c;
                    for(int l = 0; l<n_cols; l++)
                    {
                        c = eye[k][l];
                        eye[k][l] = eye[r][l];
                        eye[r][l] = c;
                        c = R[k][l];
                        R[k][l] = R[r][l];
                        R[r][l] = c;
                    }
                }
                for(int i = 0; i<n_rows; i++)
                {  
                    if(i!=r)
                    {
                        for(int l = 0; l<n_cols; l++)
                        {
                            R[i][l]-=eye[r][l]*eye[i][j];
                            eye[i][l]-=eye[r][l]*eye[i][j];
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
 * @brief Display Matrix
 * 
 */
void Matrix::display()
{
    for(int i = 0; i<this->n_rows; i++)
    {
        std::cout << "|";
        for(int j = 0; j<this->n_cols; j++)
        {
            std::cout << this->M[i][j] << "|";
        }
        std::cout << std::endl;
    }
}