#include "EyeMathUtils.h"


#if ARDUINO
    #include <Arduino.h>
#else
    #include <cstdlib>
#endif

#include <math.h> 

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

 float scaleOffsetToSize(float original, float used, float value){
     return (used / original) * value;
 }

/*double deg2rad (double degrees) {
    return degrees * 4.0 * atan (1.0) / 180.0;
}*/

double deg2rad (double degrees) {
    return ( degrees * GEO_PI ) / 180 ;
}

 Vector2 rotate2d(Vector2 point,  float angle){
    float theta = deg2rad(angle);
    float cs = cos(theta);
    float sn = sin(theta);
    Vector2 out;
    out.x = point.x * cs - point.y * sn; 
    out.y = point.x * sn + point.y * cs;
    return out;
 }

 float parametricBlend(float t)
{
    float sqt = sqrt(t);
    return sqt / (2.0f * (sqt - t) + 1.0f);
}

 float lerp(Range range, float t){
     return range.min+(range.max-range.min)*t;
 }
 float lerp(float a, float b, float t){
     return a+(b-a)*t;
 }
 float slerp(float a, float b, float t){
     return  lerp(a, b, parametricBlend(t));
 }
 Vector2 lerp(Vector2 a, Vector2 b, float t){
     Vector2 result;
     result.x = lerp(a.x, b.x, t);
     result.y = lerp(a.y, b.y, t);
     return result;
 }
 Vector2 slerp(Vector2 a, Vector2 b, float t){
     return lerp(a, b, parametricBlend(t));
 }

 float randomFloat(float min, float max){
     return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
 }
  float randomFloat(Range range){
     return range.min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(range.max-range.min)));
 }
 int randomInt(int min, int max){
    /*unsigned int r;
    do {
        r = rand();
    } while (r < ((unsigned int)(RAND_MAX) + 1) % (max + 1 - min));
    return r % (max + 1 - min) + min;*/
    return min + (rand() % static_cast<int>(max - min + 1));
 }