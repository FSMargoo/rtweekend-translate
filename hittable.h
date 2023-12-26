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
 * \file hittable.h
 * \brief 有关求交的类定义
 */

#pragma once

#include <rtweekend.h>

class Material;

class HitRecord {
public:
	HitRecord() = default;

	void SetFaceNormal(const Ray& Light, const Vec3& OutwardNormal) {
		// 设置 HitRecord 法向量
		// 注意：参数‘OutwardNormal’已经假设拥有单位长度
		FrontFace	 = Dot(Light.RayDirection(), OutwardNormal) < 0;
		NormalVector = FrontFace ? OutwardNormal : -OutwardNormal;
	}

public:
	Point3					  Point;
	Vec3					  NormalVector;
	double					  TValue{};
	bool					  FrontFace;
	std::shared_ptr<Material> OMaterial;
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& Light, const Interval& RayRange, HitRecord& Record) const = 0;
};