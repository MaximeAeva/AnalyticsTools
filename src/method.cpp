#include "method.hpp"

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
 * @brief Call to clear screen
 * 
 */
void clearScreen()
{ 
    if (system("CLS")) system("clear");
    std::cout << "\033[2J";
}

template <class T>
std::vector<Matrix<T> > svd_iter(Matrix<T> A)
{ 
    std::vector<Matrix<T> > k;
    T evNew;
    T ev;
    int r = A.getRow();
    int c = A.getCol();
    Matrix<T> v(1, c);
    v.ones()/sqrt(c);
    ev = A.eigenValue(v);
    while(true)
    { 
        Matrix<T> Av(A*v);
        Matrix<T> vNew(Av/Av.norm());
        evNew = A.eigenValue(vNew);
        if(abs(ev-evNew)<0.01)
            break;
        v = vNew;
        ev = evNew;
    }
    k.push_back(v);
    k.push_back(v);
    return k;
}

float wHann(Point p, float t)
{ 
    if(p.x>0 && p.x<t)
        return p.y*(0.5-(0.5*cos(2*PI*(p.x/t)))); 
    return 0;
}

float wHamming(Point p, float t)
{ 
    if(p.x>0 && p.x<t)
        return p.y*(0.54-(0.46*cos(2*PI*(p.x/t)))); 
    return 0;
}

float wBlackman(Point p, float t)
{ 
    if(p.x>0 && p.x<t)
        return p.y*(0.42-(0.5*cos(2*PI*(p.x/t)))+(0.08*cos(4*PI*(p.x/t)))); 
    return 0;
}

/**
 * @brief k means method
 * 
 * @param p vector of points to classify
 * @param clas Points of each class's center of mass
 * @param iterations 
 * @return Matrix<float> Distance and current linked class
 */
Matrix<float> kmeans(std::vector<Point> p, std::vector<Point> *clas, int iterations)
{
    float d;
    Matrix<float> ind(2, p.size());
    while(iterations)
    {
        Matrix<float> meanN(3, clas->size());
        //Check which is the nearest class
        for(int i = 0; i<p.size(); i++)
        {
            ind[i] = sqrt(pow(p[i].x-clas->at(0).x, 2)+pow(p[i].y-clas->at(0).y, 2));
            ind[i+p.size()] = 0;
            for(int j = 1; j<clas->size(); j++)
            {
                d = sqrt(pow(p[i].x-clas->at(j).x, 2)+pow(p[i].y-clas->at(j).y, 2));
                if(d < ind[i])
                {
                    ind[i] = d;
                    ind[i+p.size()] = j; 
                }
            }
            meanN[int(ind[i+p.size()])] += p[i].x;
            meanN[int(ind[i+p.size()])+clas->size()] += p[i].y;
            meanN[int(ind[i+p.size()])+2*clas->size()] ++;  
        }
        //Update class position
        for(int i = 0; i<clas->size(); i++)
        {
            clas->at(i).x = meanN[i]/meanN[i+2*clas->size()];
            clas->at(i).y = meanN[i+clas->size()]/meanN[i+2*clas->size()];
        }
        iterations--;
        meanN.~Matrix();
    }
    return ind;
}
