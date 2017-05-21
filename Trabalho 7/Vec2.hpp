#ifndef VEC2HPP
#define VEC2HPP

#include <iostream>
#include <cmath>
#define VEC2_TOLERANCE 1e-6

class Vec2 {
public:
    float x, y;
    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2 &a);
    Vec2 &operator=(Vec2 arg);
    Vec2 &operator+=(const Vec2 &rhs);
    Vec2 &operator-=(const Vec2 &rhs);
    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    double magnitude();
    float ang_rad();
    float ang_deg();
    static Vec2 getVec2FromPolar(double mag, double theta);
    Vec2 rotated(double theta_rad);
    Vec2 rotatedAroundCenter(const Vec2 & c, double theta_rad);
    static double distanceBetweenPoints(const Vec2 &a, const Vec2 &b);
    Vec2 getNormalizedVector();
};
std::ostream &operator<<(std::ostream &os, const Vec2 &obj);
std::ostream &operator<<(std::ostream &os, Vec2 &obj);
bool operator==(const Vec2 &lhs, const Vec2 &rhs);
inline bool operator!=(const Vec2 &lhs, const Vec2 &rhs) { return !(lhs == rhs); }
Vec2 operator*(const Vec2 &lhs, const float &c);
Vec2 operator*(const float &c, const Vec2 &rhs);

#endif // VEC2HPP
