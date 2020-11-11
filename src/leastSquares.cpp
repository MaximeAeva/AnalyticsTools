#include "leastSquares.hpp"

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
 * @brief sample f in range wdw at frequency freq with method interpolation
 * 
 * @param f signal to sample
 * @param freq frequency
 * @param method linear, quadratic, spine
 * @param wdw range to use
 * @return std::vector<Point> 
 */
std::vector<Point> sample(std::vector<Point> f, float freq, char* method, float wdw[2])
{
    std::vector<Point> g;
    std::vector<Point> h;
    g = cut(mergeSort(f), wdw);
    float step = 1/freq;
    int crtIdx = 0;
    float crtAbs = g.front().x;
    while(crtAbs <= g.back().x)
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

