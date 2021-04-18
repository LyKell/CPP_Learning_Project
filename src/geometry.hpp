#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

template <int dimension, typename Type>
class Point
{
public:
    std::array<Type, dimension> values;
    
    Point() = default;

    Point(float x, float y) :
        values { x, y }
    {}

    Point(float x, float y, float z) :
        values { x, y, z }
    {}

    Type& x() { return values[0]; }
    Type x() const { return values[0]; }

    Type& y()
    {
        static_assert(dimension >= 2, "y coordinates can't exist if dimension is less than 2");
        return values[1];
    }

    Type y() const
    {
        static_assert(dimension >= 2, "y coordinates can't exist if dimension is less than 2");
        return values[1];
    }

    Type& z()
    {
        static_assert(dimension >= 3, "z coordinates can't exist if dimension is less than 3");
        return values[2];
    }

    Type z() const
    {
        static_assert(dimension >= 3, "z coordinates can't exist if dimension is less than 3");
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::plus<Type>());
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::minus<Type>());
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::multiplies<Type>());
        return *this;
    }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
            [scalar](float val)
            {
                return val * scalar;
            });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const float scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const
    {
        Point result = *this;
        result *= (-1);
        return result;
    }

    float length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.f,
            [](float v1, float v2)
            {
                return v1 + (v2 * v2);
            }));
    }

    float distance_to(const Point& other) const
    {
        return (*this - other).length();
    }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }
        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        assert(max_len > 0);
        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }
        return *this;
    }

    std::string to_string()
    {
        return "(" + std::accumulate(values.begin() + 1, values.end(), std::to_string(values[0]),
            [](std::string& v1, float v2)
            {
                return std::move(v1) + ", " + std::to_string(v2);
            }) + ")";
    }

};

using Point2D = Point<2, float>;
using Point3D = Point<3, float>;

template <int dimension, typename Type>
std::ostream& operator<<(std::ostream& stream, Point<dimension, Type>& point)
{
    return stream << point.to_string();
}

inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}

inline void test_generic_points()
{
    Point<2, float> p1;
    Point<2, float> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3.f;

    std::cout << p3 << std::endl;
}