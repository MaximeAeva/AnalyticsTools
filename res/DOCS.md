# Welcome to docs

## Table of content

* Basic structures
* Plot
* Matrix
* Functions

-------------------------------------------------------------------------

# Basic structures

## Axis
Provide information related to axis forwarded to plot
* float range[2]
* float step = 1
* char color
* char* title

## Point
Provide an easy alternative to std::pair 
* float x
* float y

## data
Everything about a set of data
* std::vector<Point> values
* char* legend
* char color
* char style

## fdata
Provide a way to describe harmonic of a periodic signal
* float f
* float amp
* float phi

-------------------------------------------------------------------------

# Plot
    Plot is made on cmd. It will be overlapped if dimension exceed your max cmd dimensions.
<p align="center">
  <img width=900 height=600 src="https://github.com/MaximeAeva/AnalyticsTools/blob/master/res/FourierPlotExample.PNG">
</p>

## Prototype
    void plot(Axis x, Axis y, std::vector<data> dataCluster = {}, char* title = "Title", bool legend = false);

## More About
### Axis
    Provide x and y axis structures to it (care about point's number and cmd dimensions)

### dataCluster
    One or more data structures gathered in a vector (can plot several signals)

### title
    Title will be displayed on the top

### legend
    Legend will be displayed on bottom left corner (it content is made of data structures legend stuff)

-------------------------------------------------------------------------

# Matrix
    Matrix provide an efficient way to compute least squares, Fourier transform, autoregression and event more...
    This way, it is type invariant : int, float, double, long, std::complex<...> (obviously no string, char, bool ...)
<p align="center">
  <img src="https://github.com/MaximeAeva/AnalyticsTools/blob/master/res/MatrixPlotExample.PNG">
</p>

## Prorotype
    Matrix<typename T> 

## More About
### Constructors
* Basic
    Matrix(const int& rows, const int& cols)
* Copy 
    Matrix(const Matrix<T>& A)
* To VanderMonde (optimized for LS)
    Matrix(std::vector<Point> x, int deg)

### Operators
* Element access
    T & operator[](const int &index) const 
* Copy
    void operator=(const Matrix<T>& A )
* Matrix multiplication
    Matrix<T> operator*(const Matrix<T>& A)
* Matrix term to term addition
    Matrix<T> operator+(const Matrix<T>& A)
* Matrix term to term diff
    Matrix<T> operator-(const Matrix<T>& A)
* Matrix power
    Matrix<T> operator^(const int& power) 
* Matrix divide by a T value
    Matrix<T> operator/(const T& value) 

### Functions
* Transpose
    Matrix<T> Trsp() const
* Give the inverse of a square matrix
    Matrix<T> rowReduc() const
* Transform to identity matrix
    void id()
* A way to check values
    void display()
* Sum all the components
    T sum()