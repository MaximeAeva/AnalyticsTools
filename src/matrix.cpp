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
    M = new float [rows*cols]();          
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
    this->M=new float [n_rows*n_cols]();
    for(int i=0;i<n_rows;i++)
      for(int j=0;j<n_cols;j++)
        this->M[(i*n_cols)+j]=A[(i*n_cols)+j];            
}

/**
 * @brief Destroy the Matrix:: Matrix object
 * 
 */
Matrix::~Matrix()
{
    delete [] M;
}

/**
 * @brief Identity matrix
 * 
 */
void Matrix::id()
{
    if(n_rows==n_cols)
        for(int i=0;i<n_rows;i++) this->M[(i*n_cols)+i]++;
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
    this->M=new float [x.size()*deg]();
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
float & Matrix::operator[](const int &index) const
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
                this->M[(i*n_cols)+j]=A[(i*n_cols)+j]; 
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
Matrix Matrix::operator+(const Matrix& A)
{
    Matrix R(n_rows, n_cols);
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
Matrix Matrix::operator-(const Matrix& A)
{
    if(getRow(A)==this->n_rows && getCol(A)==this->n_cols)
    {
        Matrix R(n_rows, n_cols);
        for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[(i*n_cols)+j]=this->M[(i*n_cols)+j]-A[(i*n_cols)+j]; 
    }
}

Matrix Matrix::operator^(const int& power)
{

}

/**
 * @brief Divide by value
 * 
 * @param value 
 * @return Matrix 
 */
Matrix Matrix::operator/(const float& value)
{
    Matrix R(n_rows, n_cols);
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
Matrix Matrix::T() const
{
    Matrix R(n_cols, n_rows);
    for(int i=0;i<this->n_rows;i++)
            for(int j=0;j<this->n_cols;j++)
                R[(j*n_rows)+i]=this->M[(i*n_cols)+j];
    return R;
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
float Matrix::sum()
{
    float s = 0;
    for(int i = 0; i<n_rows; i++)
        for(int j = 0; j<n_cols; j++)
            s += this->M[(i*n_cols)+j];
    return s;
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
            std::cout << this->M[(i*n_cols)+j] << "|";
        }
        std::cout << std::endl;
    }
}