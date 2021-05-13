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
    int k = 0;
    for(int i = 0; i<abscissa.size(); i++)
    {
        Point p;
        p.x = abscissa[i];
        while(f[k].x <= p.x)
            k++;
        p.y = ((f[k].y-f[k-1].y)/(f[k].x-f[k-1].x))*(p.x-f[k-1].x)+f[k-1].y;
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
 * @param abscissa 
 * @param natural Is the spline natural
 * @return std::vector<Point> 
 */
std::vector<Point> splineInterp(std::vector<Point> f, std::vector<float> abscissa, bool natural)
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
        C[i] = ((f[i+1].y-f[i].y)/h[i])-((h[i]/6)*(M[i+1]-M[i]));
        CP[i] = f[i].y-M[i]*(pow(h[i], 2)/6);
    }
    int l = 0;
    for(int i = 0; i<abscissa.size(); i++)
    {
        Point p;
        p.x = abscissa[i];
        while(f[l].x<p.x) l++;
        p.y = (M[l-1]*pow(f[l].x-p.x, 3)/(6*h[l-1])) + (M[l]*pow(p.x-f[l-1].x, 3)/(6*h[l-1])) + (C[l-1]*(p.x-f[l-1].x)) + CP[l-1];
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Smooth spline interpolation
 * 
 * @param f Function to interpolate
 * @param abscissa desired return abscissa
 * @param lambda smoothness factor
 * @return std::vector<Point> 
 */
std::vector<Point> smoothSplineInterp(std::vector<Point> f, std::vector<float> abscissa, float lambda)
{
    int n = f.size();
    std::vector<float> h;
    std::vector<Point> P;
    
    Matrix<float> Q(n, n-2);
    Matrix<float> R(n-2, n-2);
    Matrix<float> I(n, n);
    Matrix<float> Y(n, 1);
    I.id();

    for(int i = 0; i<n-1; i++)
        h.push_back(f[i+1].x-f[i].x);

    for(int i = 0; i<n; i++)
    {
        Y[i] = f[i].y;
        if(i<n-1 && i>0)
            Q[i*(n-2)+i-1] = (1/h[i-1])+(1/h[i]);
        if(i>1)
            Q[i*(n-2)+i-2] = -1/h[i-1];
        if(i<n-2)
        {
            Q[i*(n-2)+i] = -1/h[i];
            R[i*(n-2)+i] = (h[i]+h[i+1])/3;
            if(i>0)
                R[i*(n-2)+i-1] = -h[i-1]/6;
        }
        if(i<n-3)
            R[i*(n-2)+i+1] = -h[i]/6;
    }
    Matrix<float> K(Q*R.rowReduc()*Q.Trsp());
    Matrix<float> M((I+(K/(1/lambda))));
    Matrix<float> S(M.rowReduc()*Y);
    for(int i = 0; i<n; i++)
    {
        Point p;
        p.x = f[i].x;
        p.y = S[i];
        P.push_back(p);
    }
    P = splineInterp(P, abscissa, true);
    return P;
}

/**
 * @brief Give residuals from linear interp between 2 functions
 * 
 * @param f 
 * @param g 
 * @param ptsNumb 
 * @return std::vector<Point> 
 */
std::vector<Point> residuals(std::vector<Point> f, std::vector<Point> g, int ptsNumb)
{
    float mini, maxi, step;
    std::vector<float> abscissa;
    std::vector<Point> e, h, r;
    if(f[0].x<g[0].x)
        mini = g[0].x;
    else 
        mini = f[0].x;
    if(f.back().x>g.back().x)
        maxi = g.back().x;
    else 
        maxi = f.back().x;
    step = (maxi-mini)/(ptsNumb-1);
    std::cout << step;
    float i = mini;
    while(i<=maxi) 
    {
        abscissa.push_back(i);
        i+=step;
    }
    e = linearInterp(f, abscissa);
    h = linearInterp(g, abscissa);
    for(int i = 0; i<e.size(); i++)
    {
        Point p;
        p.x = abscissa[i];
        p.y = sqrt(pow(e[i].y-h[i].y, 2));
        r.push_back(p);
    }
    return r;
}