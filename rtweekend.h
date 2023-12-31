﻿/*
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
 * \file rtweekend.h
 * \brief 常用数学常量和功能性函数定义
 */

#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <numbers>
#include <random>

// 数学常量

constexpr double Infinity = std::numeric_limits<double>::infinity();
constexpr double Pi		  = std::numbers::pi;

// 功能性函数

inline double DegreeToRad(const double& Degrees) {
	return Degrees * Pi / 180.f;
}

inline double RandomDouble() {
	// 返回一个随机数位于 [0, 1) 中
	static std::uniform_real_distribution<double> Distribution(0.0, 1.0);
	static std::mt19937							  Generator;
	return Distribution(Generator);
}
inline double RandomDouble(const double& Min, const double& Max) {
	// 返回一个随机数位于 [Min, Max) 中
	return Min + RandomDouble() * (Max - Min);
}

#include <interval.h>
#include <ray.h>
#include <vec3.h>