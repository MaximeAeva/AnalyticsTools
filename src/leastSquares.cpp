#include "leastSquares.hpp"

/**
 * @brief Compute least squares coefficients
 * 
 * @param f data to fit
 * @param deg degree of the fit
 * @return Matrix 
 */
Matrix lstSqr(std::vector<Point> f, int deg)
{
    Matrix X(f, deg+1);
    Matrix Y(f.size(), 1);
    for(int i = 0; i<f.size(); i++) Y[i][0] = f[i].y;  
    Matrix XT(X.T());
    Matrix P(XT*X);
    Matrix PINV(P.rowReduc());
    Matrix XINV(PINV*XT);
    Matrix A(XINV*Y);
    return A;
}
