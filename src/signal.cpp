#include <signal.hpp>

/**
 * @brief  merge sort algorithm implementation
 * 
 * @param f function of points sorted along x.
 * @return std::vector<Point> sorted verctor along x axis
 */
std::vector<Point> mergeSort(std::vector<Point> f)
{
    int s = f.size();
    if(s<=1) return f;
    else
    {
        int step = 1;
        std::vector<Point> z;
        while(pow(2, step-1)< s)
        {
            int av = pow(2, step);
            int i = 0;
            z={};
            while(i<s)
            {
                if((s-i)<av && (s-i)%av)
                {
                    int k1 = 0, k2 = 0, lim;
                    if(pow(2, step-1)<(s-i)) lim = pow(2, step-1);
                    else lim = (s-i);
                    while(k1<lim || k2<(s-i-lim))
                    {
                        if(k1==lim)
                        {
                            z.push_back(f[i+pow(2, step-1)+k2]);
                            k2++;
                        }
                        else if(k2==(s-i-lim))
                        {
                            z.push_back(f[i+k1]);
                            k1++;
                        }
                        else if(f[i+k1].x >= f[i+pow(2, step-1)+k2].x)
                        {
                            z.push_back(f[i+pow(2, step-1)+k2]);
                            k2++;
                        }
                        else if(f[i+k1].x < f[i+pow(2, step-1)+k2].x)
                        {
                            z.push_back(f[i+k1]);
                            k1++;
                        }
                    }

                }
                else
                {
                    int k1 = 0, k2 = 0;
                    while(k1<pow(2, step-1) || k2<pow(2, step-1))
                    {
                        if(k1==pow(2, step-1))
                        {
                            z.push_back(f[i+pow(2, step-1)+k2]);
                            k2++;
                        }
                        else if(k2==pow(2, step-1))
                        {
                            z.push_back(f[i+k1]);
                            k1++;
                        }
                        else if(f[i+k1].x >= f[i+pow(2, step-1)+k2].x)
                        {
                            z.push_back(f[i+pow(2, step-1)+k2]);
                            k2++;
                        }
                        else if(f[i+k1].x < f[i+pow(2, step-1)+k2].x)
                        {
                            z.push_back(f[i+k1]);
                            k1++;
                        }
                    }
                }
                i+=av;
            }
            step++;
            f={};
            f = z;
        }
        return f;
    }
}

/**
 * @brief Cut a signal along x (need to be sorted)
 * 
 * @param g signal to cut
 * @param wdw window
 * @return std::vector<Point> cutted signal
 */
std::vector<Point> cut(std::vector<Point> g, float wdw[2])
{
    std::vector<Point> h;
    int i = 0;
    while(g[i].x<=wdw[1])
    {
        if(g[i].x>=wdw[0]) h.push_back(g[i]);
        i++;
    }
    return h;
}

/**
 * @brief sample f in range wdw with n_pts points with method interpolation
 * 
 * @param f signal to sample
 * @param n_pts number of points in the interval
 * @param method linear, quadratic, spine
 * @param wdw range to use
 * @return std::vector<Point> 
 */
std::vector<Point> sample(std::vector<Point> f, int n_pts, char* method, float wdw[2])
{
    std::vector<Point> g;
    std::vector<Point> h;
    g = cut(mergeSort(f), wdw);
    float step = (g.back().x-g.front().x)/(n_pts-1);
    int crtIdx = 0;
    float crtAbs = g.front().x;
    while(crtAbs < g.back().x)
    {
        Point p;
        while(g[crtIdx+1].x < crtAbs) crtIdx++;
        p.x = crtAbs;
        float a = (g[crtIdx+1].y-g[crtIdx].y)/(g[crtIdx+1].x-g[crtIdx].x);
        float x = p.x-g[crtIdx].x;
        p.y = a*x+g[crtIdx].y;
        h.push_back(p);
        crtAbs += step;
    }
    return h;
}

/**
 * @brief linear space points 
 * 
 * @param wdw range
 * @param n_pts points
 * @return std::vector<float> 
 */
std::vector<float> linspace(float wdw[2], int n_pts)
{
    std::vector<float> abscissa;
    float step = (wdw[1]-wdw[0])/(n_pts-1);   
    for(int i = 0; i<n_pts; i++)
        abscissa.push_back(wdw[0]+(i*step));
    return abscissa;
}

/**
 * @brief A polynomial function
 * 
 * @param coefficients a0, a1, ..., an
 * @param n_pts number of points
 * @param wdw range
 * @return std::vector<Point> 
 */
std::vector<Point> polynomial(std::vector<float> coefficients, 
                            int n_pts, float wdw[2], float xShift)
{
    std::vector<Point> P;
    std::vector<float> x = linspace(wdw, n_pts);
    for(int i = 0; i<n_pts; i++)
    {
        Point p;
        p.x = x[i];
        p.y = 0;
        for(int k = 0; k<coefficients.size(); k++)
            p.y+= coefficients[k]*pow(p.x-xShift, k);
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Define a periofic signal from n_pts points in range
 * wdw with frequencies in harmonic
 * 
 * @param harmonic amplitude and frequencies
 * @param n_pts points count
 * @param wdw range
 * @return std::vector<Point> 
 */
std::vector<Point> periodic(std::vector<fdata> harmonic, int n_pts, float wdw[2])
{
    std::vector<Point> P;
    std::vector<float> x = linspace(wdw, n_pts);
    for(int i = 0; i<n_pts; i++)
    {
        Point p;
        p.x = x[i];
        p.y = 0;
        for(int k = 0; k<harmonic.size(); k++)
            p.y += harmonic[k].amp*cos((2*PI*harmonic[k].f*i)+harmonic[k].phi);
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Get the mean of the signal
 * 
 * @param f 
 * @return float 
 */
float mean(std::vector<Point> f)
{
    float m = 0;
    for(int i = 0; i<f.size(); i++) m+= f[i].y;
    m/=f.size();
    return m;
}

/**
 * @brief Get the variance of f
 * 
 * @param f 
 * @return float 
 */
float var(std::vector<Point> f)
{
    float m = mean(f);
    float v = 0;
    for(int i = 0; i<f.size(); i++) v+= pow(f[i].y, 2)-m;
    v/=(f.size()-1);
    return v;
}

/**
 * @brief Normalized tau order covariance 
 * 
 * @param tau 
 * @param f 
 * @return float 
 */
float aCFn(int tau, std::vector<Point> f)
{
    float m = mean(f);
    float v = var(f);
    float acf = 0;
    for(int i = 0; i<f.size()-abs(tau)-1; i++) acf += f[i].y*f[i+abs(tau)].y;
    acf/=f.size()-abs(tau);
    acf -= pow(m, 2);
    acf /= v;
    return acf;
}

/**
 * @brief Give the degree deg components of the autoregressive model
 *  for a WSS signal
 * 
 * @param deg 
 * @param f 
 * @return Matrix 
 */
Matrix<float> AR(int deg, std::vector<Point> f)
{
    Matrix<float> AC(deg, deg);
    Matrix<float> RC(deg, 1);
    for(int i=0;i<deg;i++)
    {
            RC[i] = aCFn(i+1, f);
        for(int j=0;j<deg;j++)
            AC[(i*deg)+j]=aCFn(i-j, f);
    }
    Matrix<float> ACINV(AC.rowReduc());
    Matrix<float> R(ACINV*RC);
    return R;
}

/**
 * @brief Construct n_pts points from the AR regression
 * 
 * @param f 
 * @param coefficients 
 * @param n_pts 
 * @param wdw 
 * @return std::vector<Point> 
 */
std::vector<Point> buildAR(std::vector<Point> f, 
                            std::vector<float> coefficients, int n_pts)
{
    std::vector<Point> P;
    float step = f[1].x-f.front().x;
    for(int i = coefficients.size()-1; i>=0; i--)
        P.push_back(f[f.size()-1-i]);
    for(int k = 0; k<n_pts; k++)
    {
        Point p;
        p.x = P.back().x+step;
        p.y = 0;
        for(int i = 0; i<coefficients.size(); i++)
        {
            p.y += P[i+k].y*coefficients[coefficients.size()-1-i];
        }
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Give the derivative from f
 * 
 * @param f 
 * @return std::vector<Point> 
 */
std::vector<Point> differentiation(std::vector<Point> f)
{
    std::vector<Point> P;
    for(int i = 0; i<f.size()-1; i++)
    {
        Point p;
        p.x = f[i].x + (f[i+1].x-f[i].x)/2;
        p.y = (f[i+1].y-f[i].y)/(f[i+1].x-f[i].x);
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Give the tangeante in abscissa parameters
 * 
 * @param f 
 * @param abscissa 
 * @return std::vector<float> 
 */
std::vector<float> tangent(std::vector<Point> f, float abscissa)
{
    int i = 0;
    while(f[i].x<abscissa) i++;
    float fpa = (f[i+1].y-f[i].y)/(f[i+1].x-f[i].x);
    float fa = fpa*(abscissa-f[i-1].x)+f[i-1].y;
    std::vector<float> P; 
    P.push_back(fa);
    P.push_back(fpa); 
    return P; 
}

/**
 * @brief Give the order deg unshift moving average
 * 
 * @param f 
 * @param deg 
 * @return std::vector<Point> 
 */
std::vector<Point> centralMovingAverage(std::vector<Point> f, int deg)
{
    std::vector<Point> P;
    for(int i = 0; i<f.size()-(deg-1); i++)
    {
        Point p;
        p.x = (f[i+deg].x+f[i].x)/2;
        p.y = 0;
        for(int k = 0; k<deg; k++)
            p.y += f[i+k].y;
        p.y /= deg;
        P.push_back(p);
    }
    return P;
}

/**
 * @brief Add gaussian noise to a signal
 * 
 * @param f signal
 * @param mu Noise's mean
 * @param sigma Noise's standard deviation
 * @param yNoise Enable abscissa noise (default: false)
 * @return std::vector<Point> 
 */
std::vector<Point> gaussianNoise(std::vector<Point> f, float mu, float sigma, bool yNoise)
{
    std::vector<Point> P;
    P = f;
    for(int i = 0; i<f.size(); i++) P[i].y += boxMuller(mu, sigma);
    if(yNoise) for(int i = 0; i<f.size(); i++) P[i].x += boxMuller(mu, sigma);
    return P;
}

/**
 * @brief Transform uniform distribution to gaussian
 * 
 * @param mu 
 * @param sigma 
 * @return float 
 */
float boxMuller(float mu, float sigma)
{
    float a = (rand() % 100 + 0.001)/100;
    float b = (rand() % 100 + 0.001)/100;

    return (sqrt(-2*log(a))*cos(2*PI*b))*sigma + mu;
}

/**
 * @brief Discrete Fourier Transform
 * 
 * @param f function
 * @return Matrix<std::complex<float> > 
 */
Matrix<std::complex<float> > DFT(std::vector<Point> f)
{
    int n = f.size();
    std::complex<double> i(0, 1);
    std::complex<double> w = pow(exp(i), ((-2)*PI)/n);
    Matrix<std::complex<float> > M(f.size(), f.size());
    Matrix<std::complex<float> > X(f.size(), 1);
    for(int l = 0; l<n; l++)
    {
        X[l] = f[l].y;
        for(int j = 0; j<n; j++)
        {
            M[l*n+j] = pow(w, l*j);
        }
    }
    return M*X;
}

/**
 * @brief Power Spectral Density
 * 
 * @param f function
 * @return std::vector<Point> 
 */
std::vector<Point> PSD(std::vector<Point> f)
{
    Matrix<std::complex<float> > M = DFT(f);
    std::vector<Point> P;
    int N = f.size();
    float fe = N/(f.back().x-f.front().x);
    for(int i = 0; i<f.size(); i++)
    {
        Point p;
        p.x = i*(fe/N)-(fe/2);
        p.y = abs(M[f.size()-1-i])/(N/2);
        P.push_back(p);
    }
    return P;
}