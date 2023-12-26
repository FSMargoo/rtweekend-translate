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
 * \file interval.h
 * \brief 一个区间类
 */

#pragma once

#include <rtweekend.h>

class Interval {
public:
	// 默认一个空区间
	Interval() : Minimum(+Infinity), Maximum(-Infinity) {
	}
	Interval(const double& Min, const double& Max) : Minimum(Min), Maximum(Max) {
	}

public:
	// 闭区间
	bool Contains(const double& Value) const {
		return Value >= Minimum && Value <= Maximum;
	}
	// 开区间
	bool Surrounds(const double& Value) const {
		return Value > Minimum && Value < Maximum;
	}
	double Clamp(const double& X) const {
		if (X < Minimum) {
			return Minimum;
		} else if (X > Maximum) {
			return Maximum;
		} else {
			return X;
		}
	}

public:
	static const Interval Empty;
	static const Interval Universe;

public:
	double Minimum;
	double Maximum;
};

const static Interval Empty(+Infinity, -Infinity);
const static Interval Universe(-Infinity, +Infinity);