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
 * \file sphere.h
 * \brief 球体相关定义代码
 */

#pragma once

#include <hittable.h>

class Sphere : public Hittable {
public:
	Sphere(Point3 ICenter, const double& IRadius, std::shared_ptr<Material> IMaterial)
		: Center(ICenter), Radius(IRadius), OMaterial(IMaterial) {
	}
	bool Hit(const Ray& Light, const Interval& RayRange, HitRecord& Record) const override {
		Vec3 Origin = Light.OriginPoint() - Center;

		// 求判别式

		const auto A	 = Light.RayDirection().LengthSquared();
		const auto HalfB = Dot(Origin, Light.RayDirection());
		const auto C	 = Origin.LengthSquared() - Radius * Radius;
		const auto Delta = HalfB * HalfB - A * C;
		if (Delta < 0) {
			return false;
		}

		const auto SqrtDelta = sqrt(Delta);
		// 这里只采用最靠近原点（即最小的根）
		auto Root = (-HalfB - SqrtDelta) / A;
		// 如果超出范围，则选用另一个根
		if (!RayRange.Surrounds(Root)) {
			// 如果依然 OOR 则没有交点
			Root = (-HalfB + SqrtDelta) / A;
			if (!RayRange.Surrounds(Root)) {
				return false;
			}
		}

		// 求解出交点并记录在 Record 中
		Record.TValue	   = Root;
		Record.Point	   = Light.At(Root);
		Record.OMaterial   = OMaterial;
		Vec3 OutwardNormal = (Record.Point - Center) / Radius;
		Record.SetFaceNormal(Light, OutwardNormal);

		return true;
	}

private:
	Point3					  Center;
	double					  Radius;
	std::shared_ptr<Material> OMaterial;
};