#ifndef TWBL_SRC_SHARED_MATH_H
#define TWBL_SRC_SHARED_MATH_H

#if __has_include(<base/math.h>)
#include <base/math.h>
#else

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstdlib>
#include <limits>

using std::clamp;

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

constexpr float pi = 3.1415926535897932384626433f;

constexpr inline int round_to_int(float f)
{
	return f > 0 ? (int)(f + 0.5f) : (int)(f - 0.5f);
}

constexpr inline int round_truncate(float f)
{
	return (int)f;
}

template<typename T, typename TB>
constexpr inline T mix(const T a, const T b, TB amount)
{
	return a + (b - a) * amount;
}

template<typename T, typename TB>
inline T bezier(const T p0, const T p1, const T p2, const T p3, TB amount)
{
	// De-Casteljau Algorithm
	const T C10 = mix(p0, p1, amount);
	const T C11 = mix(p1, p2, amount);
	const T C12 = mix(p2, p3, amount);

	const T C20 = mix(C10, C11, amount);
	const T C21 = mix(C11, C12, amount);

	return mix(C20, C21, amount); // c30
}

inline float random_float()
{
	return rand() / (float)(RAND_MAX);
}

inline float random_float(float Min, float Max)
{
	return Min + random_float() * (Max - Min);
}

inline float random_float(float Max)
{
	return random_float(0.0f, Max);
}

inline float random_angle()
{
	return 2.0f * pi * (rand() / std::nextafter((float)RAND_MAX, std::numeric_limits<float>::max()));
}

constexpr int fxpscale = 1 << 10;

// float to fixed
constexpr inline int f2fx(float v)
{
	return round_to_int(v * fxpscale);
}
constexpr inline float fx2f(int v)
{
	return v / (float)fxpscale;
}

// int to fixed
constexpr inline int i2fx(int v)
{
	return v * fxpscale;
}
constexpr inline int fx2i(int v)
{
	return v / fxpscale;
}

class fxp
{
	int value;

public:
	void set(int v)
	{
		value = v;
	}
	int get() const
	{
		return value;
	}
	fxp &operator=(int v)
	{
		value = i2fx(v);
		return *this;
	}
	fxp &operator=(float v)
	{
		value = f2fx(v);
		return *this;
	}
	operator int() const
	{
		return fx2i(value);
	}
	operator float() const
	{
		return fx2f(value);
	}
};

template<typename T>
constexpr inline T minimum(T a, T b)
{
	return std::min(a, b);
}
template<typename T>
constexpr inline T minimum(T a, T b, T c)
{
	return std::min(std::min(a, b), c);
}
template<typename T>
constexpr inline T maximum(T a, T b)
{
	return std::max(a, b);
}
template<typename T>
constexpr inline T maximum(T a, T b, T c)
{
	return std::max(std::max(a, b), c);
}
template<typename T>
constexpr inline T absolute(T a)
{
	return a < T(0) ? -a : a;
}

template<typename T>
constexpr inline T in_range(T a, T Lower, T Upper)
{
	return Lower <= a && a <= Upper;
}
template<typename T>
constexpr inline T in_range(T a, T Upper)
{
	return in_range(a, 0, Upper);
}

#endif

#endif
