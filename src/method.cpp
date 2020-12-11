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

