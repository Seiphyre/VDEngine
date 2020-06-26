#ifndef VDENGINE_CORE_H_
#define VDENGINE_CORE_H_

// Standard C++ libs
#include <math.h>
#include <limits>

namespace VDEngine
{

#define EPSILON_DOUBLE std::numeric_limits<double>::epsilon()
#define EPSILON_FLOAT std::numeric_limits<float>::epsilon()

inline float min(float x, float y)
{
    return (y < x) ? y : x;
}

inline float max(float x, float y)
{
    return (y > x) ? y : x;
}

inline float clamp(float x, float min_value, float max_value)
{
    return min(max(x, min_value), max_value);
}

inline float to_radians(float degrees)
{
    return ((degrees * M_PI) / 180.0);
}

inline float to_degrees(float radians)
{
    return ((radians * 180.0) / M_PI);
}

} // namespace VDEngine

#endif /* VDENGINE_CORE_H_ */