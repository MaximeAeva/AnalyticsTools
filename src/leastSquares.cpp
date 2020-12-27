#include "leastSquares.hpp"

/**
 * @brief Compute least squares coefficients
 * 
 * @param f data to fit
 * @param deg degree of the fit
 * @return Matrix 
 */
Matrix<float> lstSqr(std::vector<Point> f, int deg)
{
    Matrix<float> X(f, deg+1);
    Matrix<float> Y(f.size(), 1);
    for(int i = 0; i<f.size(); i++) Y[i] = f[i].y;  
    Matrix<float> XT(X.Trsp());
    Matrix<float> P(XT*X);
    Matrix<float> PINV(P.rowReduc());
    Matrix<float> XINV(PINV*XT);
    Matrix<float> A(XINV*Y);
    return A;
}

/**
 * @brief Return vector of residuals
 * 
 * @param f Function
 * @param coeff least squares coefficients
 * @return std::vector<Point> 
 */
std::vector<Point> residuals(std::vector<Point> f, Matrix<float> coeff)
{
    std::vector<Point> P;
    for(int i = 0; i<f.size(); i++)
    {
        Point p;
        p.x = f[i].x;
        p.y = 0;
        for(int k = 0; k<coeff.getSize(); k++)
            p.y+= coeff[k]*pow(p.x, k);
        p.y -= f[i].y;
        P.push_back(p);
    }
    return P;
}