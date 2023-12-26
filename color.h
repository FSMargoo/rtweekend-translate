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
 * \file color.h
 * \brief 定义颜色
 */

#pragma once

#include <vec3.h>
#include <graphics.h>

using Color = Vec3;

// 线性空间到伽马空间的变化
inline double LinearToGamma(const double& LinearComponent) {
	return sqrt(LinearComponent);
}
// 将颜色转换为对应的内存 DWORD 值
DWORD ColorToDWORD(const Color& Value, const int& SamplesPerPixel) {
	auto R = Value.X();
	auto G = Value.Y();
	auto B = Value.Z();

	// 将颜色除以采样数
	auto Scale = 1.f / SamplesPerPixel;
	R *= Scale;
	G *= Scale;
	B *= Scale;

	// 进行线性空间到 Gamma 空间的变换
	R = LinearToGamma(R);
	G = LinearToGamma(G);
	B = LinearToGamma(B);

	// 再重新将颜色分量映射到 RGB 空间上
	static const Interval Intensity(0.f, 0.999);
	return BGR(RGB(Intensity.Clamp(R) * 255, Intensity.Clamp(G) * 255, Intensity.Clamp(B) * 255));
}