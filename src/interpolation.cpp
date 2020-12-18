#include "interpolation.hpp"

/**
 * @brief Linear interpolation
 * 
 * @param f 
 * @param abscissa 
 * @return std::vector<Point> 
 */
std::vector<Point> linearInterp(std::vector<Point> f, std::vector<float> abscissa)
{
    std::vector<Point> P;
    for(int i = 0; i<abscissa.size(); i++)
    {
        Point p;
        p.x = abscissa[i];
        int k = 0;
        while(f[k].x < p.x)
            k++;
        p.y = ((f[k+1].y-f[k].y)/(f[k+1].x-f[k].x))*(p.x-f[k].x)+f[k].y;
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Lagrangian interpolation
 * 
 * @param f 
 * @param abscissa 
 * @return std::vector<Point> 
 */
std::vector<Point> lagrangeInterp(std::vector<Point> f, std::vector<float> abscissa)
{
    std::vector<Point> l;
    for(int k = 0; k < abscissa.size(); k++)
    {
        Point p;
        p.x = abscissa[k];
        p.y = 0;
        for(int j = 0; j<f.size(); j++)
        {
            float pdr = 1;
            for(int i = 0; i<f.size(); i++)
                if(i!=j) pdr *= (p.x-f[i].x)/(f[j].x-f[i].x);
            p.y += f[j].y*pdr;
        }
        l.push_back(p);
    }
    return l;
}

/**
 * @brief Give optimized points to fit while avoiding Runge-Kutta effect
 * 
 * @param f function to fit
 * @param deg degree of the fit polynomial
 * @return std::vector<Point> 
 */
std::vector<Point> chebychevNodes(std::vector<Point> f, int deg)
{
    std::vector<Point> P;
    float a = f.front().x;
    float b = f.back().x;
    for(int k = 1; k<deg+2; k++)
    {
        Point p;
        p.x = (0.5*(a+b))+(0.5*(b-a)*cos(PI*((2*k)-1)/(2*(deg+1))));
        p.y = tangent(f, p.x).front();
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Natural cubic spline interpolation
 * 
 * @param f 
 * @param abscissa must be in f range
 * @return std::vector<Point> 
 */
std::vector<Point> splineInterp(std::vector<Point> f, std::vector<float> abscissa)
{
    int n = f.size();
    std::vector<float> h;
    std::vector<Point> P;
    
    Matrix<float> F(n, 1);
    Matrix<float> C(n-1, 1);
    Matrix<float> CP(n-1, 1);
    Matrix<float> R(n, n);

    F[0] = 0;
    F[n-1] = 0;
    R[0] = 1;
    R[pow(n, 2)-1] = 1;
    for(int i = 0; i<n-1; i++)
    {
        h.push_back(f[i+1].x-f[i].x);
        if(i>0)
        {
            F[i] = ((f[i+1].y-f[i].y)/h[i])-((f[i].y-f[i-1].y)/h[i-1]);
            R[i*n+i] = (h[i-1]+h[i])/3;
            R[i*n+i+1] = h[i]/6;
            R[i*n+i-1] = h[i-1]/6;
        }
    }
    Matrix<float> M(R.rowReduc()*F);
    for(int i = 0; i<n-1; i++)
    {
        C[i] = ((f[i+1].y-f[i].y)/h[i])-(h[i]/6)*(M[i+1]-M[i]);
        CP[i] = f[i].y-M[i]*(pow(h[i], 2)/6);
    }
    int l = 0;
    for(int i = 0; i<abscissa.size(); i++)
    {
        Point p;
        p.x = abscissa[i];
        while(p.x<f[l].x) l++;
        p.y = (M[l]*pow(f[l+1].x-p.x, 3)/(6*h[l])) + (M[l+1]*pow(p.x-f[l].x, 3)/(6*h[l])) + (C[l]*(p.x-f[l].x)) + CP[l];
        P.push_back(p);
    }
    return P;
}