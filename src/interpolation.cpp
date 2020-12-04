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
