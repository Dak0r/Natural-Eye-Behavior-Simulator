#ifndef GEOMETRY_H
#define GEOMETRY_H



    #define GEO_PI 3.14159265
    
    struct Vector2
    {
       float x;
       float y;    
    };
    struct RangeInt
    {
       int min;
       int max;    
    };
    struct Range
    {
       float min;
       float max;    
    };
    struct AreaInt
    {
       int x_min;
       int y_min;
       int x_max;    
       int y_max;
    };
    struct Area
    {
       float x_min;
       float y_min;
       float x_max;    
       float y_max;
    };

    bool operator==(const Vector2& lhs, const Vector2& rhs);
    bool operator!=(const Vector2& lhs, const Vector2& rhs);

    double deg2rad (double degrees);
    float scaleOffsetToSize(float original, float used, float value);
    Vector2 rotate2d(Vector2 point,  float angle);
    float parametricBlend(float t);
    float lerp(Range range, float t);
    float lerp(float a, float b, float t);
    float slerp(float a, float b, float t);
    Vector2 lerp(Vector2 a, Vector2 b, float t);
    float random(float min, float max);
    float random(Range range);
    int randomInt(int min, int max);
 #endif