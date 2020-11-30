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
