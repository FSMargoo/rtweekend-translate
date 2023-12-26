/*
 * Copyright (c) 2023~Now Margoo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file vec3.h
 * \brief 定义了向量有关的操作
 */

#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
	Vec3() : e{0, 0, 0} {
	}
	Vec3(const double& e0, const double& e1, const double& e2) : e{e0, e1, e2} {
	}

public:
	double X() const {
		return e[0];
	}
	double Y() const {
		return e[1];
	}
	double Z() const {
		return e[2];
	}

public:
	Vec3 operator-() const {
		return Vec3{-e[0], -e[1], -e[2]};
	}
	double operator[](const int& Index) const {
		return e[Index];
	}
	double& operator[](const int& Index) {
		return e[Index];
	}

	Vec3& operator+=(const Vec3& Vector) {
		e[0] += Vector.e[0];
		e[1] += Vector.e[1];
		e[2] += Vector.e[2];

		return *this;
	}
	Vec3& operator*=(const Vec3& Vector) {
		e[0] *= Vector.e[0];
		e[1] *= Vector.e[1];
		e[2] *= Vector.e[2];

		return *this;
	}
	Vec3& operator*=(const double& Value) {
		e[0] *= Value;
		e[1] *= Value;
		e[2] *= Value;

		return *this;
	}
	Vec3& operator/=(const double& Value) {
		return *this *= 1 / Value;
	}

public:
	// 计算向量模长
	double Length() const {
		return sqrt(LengthSquared());
	}
	// 计算向量模长（未开方）
	double LengthSquared() const {
		return std::pow(e[0], 2) + std::pow(e[1], 2) + std::pow(e[2], 2);
	}
	static Vec3 Random() {
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	}
	static Vec3 Random(const double& Min, const double& Max) {
		return Vec3(RandomDouble(Min, Max), RandomDouble(Min, Max), RandomDouble(Min, Max));
	}
	bool NearZero() const {
		auto Judge = 1e-8;
		return (fabs(e[0]) < Judge) && (fabs(e[1]) < Judge) && (fabs(e[2]) < Judge);
	}

public:
	double e[3];
};

// Point3 只是一个 Vec3 的别名，但可以提高代码可读性
using Point3 = Vec3;

// 向量操作有关函数

inline std::ostream& operator<<(std::ostream& Output, const Vec3& Vector) {
	return Output << Vector.e[0] << ' ' << Vector.e[1] << ' ' << Vector.e[2];
}
inline Vec3 operator+(const Vec3& Left, const Vec3& Right) {
	return Vec3{Left.e[0] + Right.e[0], Left.e[1] + Right.e[1], Left.e[2] + Right.e[2]};
}
inline Vec3 operator-(const Vec3& Left, const Vec3& Right) {
	return Vec3{Left.e[0] - Right.e[0], Left.e[1] - Right.e[1], Left.e[2] - Right.e[2]};
}
inline Vec3 operator*(const Vec3& Left, const Vec3& Right) {
	return Vec3{Left.e[0] * Right.e[0], Left.e[1] * Right.e[1], Left.e[2] * Right.e[2]};
}
inline Vec3 operator*(const double& Value, const Vec3& Vector) {
	return Vec3{Value * Vector.e[0], Value * Vector.e[1], Value * Vector.e[2]};
}
inline Vec3 operator/(const Vec3& Left, const double& Value) {
	return (1 / Value) * Left;
}

// 向量点乘操作
inline double Dot(const Vec3& w, const Vec3& v) {
	return w.e[0] * v.e[0] + w.e[1] * v.e[1] + w.e[2] * v.e[2];
}
// 向量叉乘操作
inline Vec3 Cross(const Vec3& w, const Vec3& v) {
	return Vec3{w.e[1] * v.e[2] - w.e[2] * v.e[1], w.e[2] * v.e[0] - w.e[0] * v.e[2],
				w.e[0] * v.e[1] - w.e[1] * v.e[0]};
}
// 单位化向量
inline Vec3 UnitVector(const Vec3& Vector) {
	return Vector / Vector.Length();
}
// 生成一个离焦盘上的随机点
inline Vec3 RandomInUnitDisk() {
	while (true) {
		auto Point = Vec3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
		if (Point.LengthSquared() < 1) {
			return Point;
		}
	}
}
// 生成一个位于单位球体中的向量
inline Vec3 RandomInUnitSphere() {
	while (true) {
		auto Vector = Vec3::Random();
		if (Vector.LengthSquared() < 1) {
			return Vector;
		}
	}
}
// 生成一个随机单位向量
inline Vec3 RandomUnitVector() {
	return UnitVector(RandomInUnitSphere());
}
// 判断随机所在半球
inline Vec3 RandomOnHemisphere(const Vec3& Normal) {
	Vec3 OnUnitSphere = RandomInUnitSphere();
	if (Dot(OnUnitSphere, Normal) > 0.f) {
		return OnUnitSphere;
	} else {
		// 如果不在同一个平面则反转变量
		return -OnUnitSphere;
	}
}
Vec3 Reflect(const Vec3& Vector, const Vec3& Normal) {
	return Vector - 2.f * Dot(Vector, Normal) * Normal;
}
Vec3 Refract(const Vec3& UnitVector, const Vec3& Normal, const double& Frac) {
	auto CosTheta	  = fmin(Dot(-UnitVector, Normal), 1.f);
	Vec3 ROutPerp	  = Frac * (UnitVector + CosTheta * Normal);
	Vec3 ROutParallel = -sqrt(fabs(1.f - ROutPerp.LengthSquared())) * Normal;

	return ROutPerp + ROutParallel;
}