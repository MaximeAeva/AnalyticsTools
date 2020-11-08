#ifndef STR_H
#define STR_H

#include <vector>

/**
 * @brief Axis definition
 * 
 * @param range axis [min, max]
 * @param step axis accuracy
 * @param color axis color
 * @param title Name of the axis
 */
struct Axis{
    float range[2];
    float step = 1;
    char color = 'w';
    char* title = "axis";
};

/**
 * @brief Point definition
 * 
 * @param x float x coordinate
 * @param y float y coordinate
 */
struct Point{
    float x;
    float y;
};

/**
 * @brief Data definition
 *
 * @param values vector of Point
 * @param legend Name of the curve
 * @param color Color of the curve
 */
struct data{
    std::vector<Point> values;
    char* legend;
    char color;
};



#endif