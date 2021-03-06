#pragma once

#define PI (3.1415926535897932384626433832795f)
#include <Math.h>
#include "Engine/Math/Primitives/vec2.hpp"
#include "Engine/Math/Primitives/ivec2.hpp"
#include "Engine/Math/Primitives/uvec2.hpp"
#include "Engine/Math/Primitives/mat44.hpp"

#undef max
#undef min
class uvec2;
constexpr float fSQRT_3_OVER_3 = 0.577350269f;
class FloatRange;
class aabb2;
class ivec2;
class IntRange;
class Rgba;
typedef int int32_t;
class vec2;
class Disc2;


float convertRadiansToDegrees (float radians);
float convertDegreesToRadians (float degrees);
float cosDegrees (float degrees);
float sinDegrees (float degrees);
float asinDegrees(float sin);
float acosDegrees(float cos);
float atan2Degree(float y, float x);
float tanDegree(float degrees);
float getSquaredDistance(const vec2& a, const vec2& b);
float getDistance(const vec2& a, const vec2& b);
float getAngularDisplacement(float startDegrees, float endDegrees);

// it should work for all different scales, no matter degree or radian or whatever
// maxTurnAngle should not be negative
float turnToward(float current, float goal, float maxTurnAngle);
vec2 reflect(const vec2& in, const vec2& normal);

float getRandomf01();
float getRandomf(float minInclusive, float maxInclusive);
int32_t getRandomInt32(int32_t minInclusive, int32_t maxInclusive);
int32_t getRandomInt32LessThan(int32_t maxNotInclusive);
bool checkRandomChance(float chanceForSuccess);

template<class VectorType>
float dotProduct(const VectorType& a, const VectorType& b) {
  return a.dot(b);
}

inline float frac(float v) {
  return v - floor(v);
}

inline float step(float a, float b) {
  return (a >= b) ? 1.f : 0.f;
}

inline vec3 step(const vec3& a, const vec3& b) {
  return vec3{step(a.x, b.x), step(a.y, b.y), step(a.z, b.z) };
}

inline vec3 abs(const vec3& val) {
  return { abs(val.x), abs(val.y), abs(val.z) };
}

//--------------------------- ranging, clamping ------------------------------------------------------------

// QA: constexpr with link error
int rounding(float in);
float roundingf(float in);

int ceiling(float in);
float clampf(float v, float min, float max);
float clampf01(float v);
float clampfInAbs1(float v);

template<typename T>
auto clamp(const T& v, const T& min, const T& max) {
  return v > max ? max : (v < min ? min : v);
}

template<>
inline auto clamp(const vec2& v, const vec2& min, const vec2& max) {
  return vec2{ clampf(v.x, min.x, max.x), clampf(v.y, min.y, max.y) };
}

template<>
inline auto clamp(const vec3& v, const vec3& min, const vec3& max) {
  return vec3{ clampf(v.x, min.x, max.x), clampf(v.y, min.y, max.y), clampf(v.z, min.z, max.z) };
}

inline auto clamp(const ivec2& v, const ivec2& min, const ivec2& max) {
  return ivec2{ clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y) };
}

template<>
inline auto clamp(const uvec2& v, const uvec2& min, const uvec2& max) {
  return uvec2{ clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y) };
}

float getFraction(float v, float start, float end);

float rangeMapf(float v, float inStart, float inEnd, float outStart, float outEnd);

template<typename T>
auto rangeMap(const T& v, const T& inStart, const T& inEnd, const T& outStart, const T& outEnd) {
  if (inStart == inEnd) {
    return (outStart + outEnd) * 0.5f;
  }

  auto inRange = inEnd - inStart,
    outRange = outEnd - outStart,
    inFromStart = v - inStart,
    fractionInRange = inFromStart / inRange;

  auto outFromStart = fractionInRange * outRange;

  return outFromStart + outStart;
};


//-------------------------- interpolation --------------------------------------------------

float	smoothStart2(float t); // 2nd-degree smooth start (a.k.a. "quadratic ease in")
float	smoothStart3(float t); // 3rd-degree smooth start (a.k.a. "cubic ease in")
float	smoothStart4(float t); // 4th-degree smooth start (a.k.a. "quartic ease in")
float	smoothStop2(float t); // 2nd-degree smooth start (a.k.a. "quadratic ease out")
float	smoothStop3(float t); // 3rd-degree smooth start (a.k.a. "cubic ease out")
float	smoothStop4(float t); // 4th-degree smooth start (a.k.a. "quartic ease out")
float	smoothStep3(float t); // 3rd-degree smooth start/stop (a.k.a. "smoothstep")

// linear interpolate
inline float lerpf(float from, float to, float fraction);

template<typename T>
auto lerp(const T& from, const T& to, float fraction) {
  return from * (1.f - fraction) + to * fraction;
};

template<>
auto lerp(const mat44& from, const mat44& to, float fraction);

float lerp(float from, float to, float fraction);
vec2 lerp(const vec2& from, const vec2& to, float fraction);
FloatRange lerp(const FloatRange& from, const FloatRange& to, float fraction);
aabb2 lerp(const aabb2& from, const aabb2& to, float fraction);
Disc2 lerp(const Disc2& from, const Disc2& to, float fraction);

int lerp(int from, int to, float fraction);
unsigned char lerp(unsigned char from, unsigned char to, float fraction);
ivec2 lerp(const ivec2& from, const ivec2& to, float fraction);
IntRange lerp(const IntRange& from, const IntRange& to, float fraction);
Rgba lerp(const Rgba& from, const Rgba& to, float fraction);

vec3 slerp(const vec3& from, const vec3& to, float fraction);
vec3 slerpUnit(const vec3& from, const vec3& to, float fraction);

//---------------------------- Bitwise operation --------------------------------------------
bool areBitsSet(unsigned char flag8, unsigned char mask);
bool areBitsSet(unsigned int flag32, unsigned int mask);
void setBits(unsigned char& flag8, unsigned char mask);
void setBits(unsigned int& flag32, unsigned int mask);
void clearBits(unsigned char& flag8, unsigned char mask);
void clearBits(unsigned int& flag32, unsigned int mask);

constexpr float EPS = 1e-5f;

inline constexpr bool equal(float a, float b) { return (a - b <= EPS) && (a - b >= -EPS); }
inline constexpr bool equal0(float a) { return (a >= 0 && a <= EPS) || (a < 0 && a >= -EPS); }
/** Returns whether a number is a power of two
*/

template<typename T>
inline bool isPow2(T a) {
  uint64_t t = (uint64_t)a;
  return (t & (t - 1)) == 0;
}