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
 * \file HittableList.h
 * \brief 一个 Hittable 类的列表
 */

#pragma once

#include <hittable.h>

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
	HittableList() = default;
	explicit HittableList(const std::shared_ptr<Hittable>& Object) {
		Add(Object);
	}

public:
	void Clear() {
		Objects.clear();
	}
	void Add(const std::shared_ptr<Hittable>& Object) {
		Objects.push_back(Object);
	}
	bool Hit(const Ray& Light, const Interval& RayRange, HitRecord& Record) const override {
		HitRecord Temp;
		auto	  HitFlag = false;
		auto	  Closet  = RayRange.Maximum;

		for (const auto& Object : Objects) {
			if (Object->Hit(Light, Interval(RayRange.Minimum, Closet), Temp)) {
				HitFlag = true;
				Closet	= Temp.TValue;
				Record	= Temp;
			}
		}

		return HitFlag;
	}

public:
	std::vector<std::shared_ptr<Hittable>> Objects;
};