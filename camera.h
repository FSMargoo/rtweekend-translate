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
 * \file camera.h
 * \brief 相机类有关定义
 */

#pragma once

#include <rtweekend.h>

#include <color.h>
#include <device.h>
#include <hittable.h>
#include <material.h>

class Camera {
public:
	void Render(const Hittable& World) {
		Initialize();

		// 渲染部分

		for (size_t Y = 0; Y < ImageHeight; ++Y) {
			std::clog << "\r还剩下：" << (ImageHeight - Y) << "条扫描线待渲染。 " << std::flush;
			const auto HeightVec = static_cast<double>(Y) * PixelDeltaV;
			for (size_t X = 0; X < ImageWidth; ++X) {
				Color WriteColor;
				for (int Sample = 0; Sample < SamplesPerPixel; ++Sample) {
					Ray Light = GetRay(X, Y, HeightVec);
					WriteColor += RayColor(Light, MaxDepth, World);
				}

				Graphics->At(X, Y) = ColorToDWORD(WriteColor, SamplesPerPixel);
			}
		}

		std::clog << "\r渲染完毕。			\n";

		Device::Flush();
	}

public:
	double AspectRatio	   = 16.0 / 9.0; // 图像纵高比
	int	   ImageWidth	   = 640;		 // 图像像素宽
	int	   SamplesPerPixel = 10;		 // 采样率
	int	   MaxDepth		   = 10;		 // 最大光反射数量

	Point3 LookFrom = Point3(0, 0, -1);
	Point3 LookAt	= Point3(0, 0, 0);
	Vec3   VUP		= Vec3(0, 1, 0);
	double VFov		= 90.f; // 垂直视角（视野）

	double DefocusAngle	 = 0;
	double FocusDistance = 10;

private:
	void Initialize() {
		// 计算图像的高，并且确保其起码为一

		ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
		ImageHeight = (ImageHeight < 1) ? 1 : ImageHeight;

		CameraCenter = LookFrom;

		// 相机部分

		const auto Theta		  = DegreeToRad(VFov);
		const auto H			  = tan(Theta / 2);
		const auto ViewportHeight = 2 * H * FocusDistance;
		const auto ViewportWidth =
			ViewportHeight * (static_cast<double>(ImageWidth) / ImageHeight);

		W = UnitVector(LookFrom - LookAt);
		U = UnitVector(Cross(VUP, W));
		V = Cross(W, U);

		// 计算横纵向量 u 和 v

		const auto ViewportU = ViewportWidth * U;
		const auto ViewportV = ViewportHeight * -V;

		// 由像素间距计算横纵增量向量

		PixelDeltaU = ViewportU / ImageWidth;
		PixelDeltaV = ViewportV / ImageHeight;

		// 计算左上角像素的位置

		const auto ViewportUpperLeft =
			CameraCenter - (FocusDistance * W) - ViewportU / 2 - ViewportV / 2;
		Pixel100Loc = ViewportUpperLeft + 0.5 * (PixelDeltaU + PixelDeltaV);
		Graphics	= std::make_shared<Device>(ImageWidth, ImageHeight);

		auto DefocusRadius = FocusDistance * tan(DegreeToRad(DefocusAngle / 2));
		DefocusDiskU = DefocusRadius * U;
		DefocusDiskV = DefocusRadius * V;
	}

	Ray GetRay(const size_t& X, const size_t& Y, const Vec3& HeightVec) const {
		// 从位于 (X, Y) 的像素获得获取一个随机采样光线
		auto PixelCenter = Pixel100Loc + (static_cast<double>(X) * PixelDeltaU) + HeightVec;
		auto PixelSample = PixelCenter + PixelSampleSquare();

		const auto RayOrigin	= (DefocusAngle <= 0) ? CameraCenter : DefocusDiskSample();
		const auto RayDirection = PixelSample - RayOrigin;

		return Ray{RayOrigin, RayDirection};
	}
	Point3 DefocusDiskSample() const {
		auto Point = RandomInUnitDisk();
		return CameraCenter + (Point[0] * DefocusDiskU) + (Point[1] * DefocusDiskV);
	}
	Vec3 PixelSampleSquare() const {
		// 返回一个位于像素为中心的正方形内的随机采样点
		auto PointX = -0.5 + RandomDouble();
		auto PointY = -0.5 + RandomDouble();

		return (PointX * PixelDeltaU) + (PointY * PixelDeltaV);
	}

	Color RayColor(const Ray& Light, int Depth, const Hittable& World) const {
		HitRecord Record;
		if (Depth <= 0) {
			return Color{0, 0, 0};
		}

		if (World.Hit(Light, Interval(0.001, Infinity), Record)) {
			Ray	  Scattered;
			Color Attenuation;
			if (Record.OMaterial->Scatter(Light, Record, Attenuation, Scattered)) {
				return Attenuation * RayColor(Scattered, Depth - 1, World);
			}
			return Color{0, 0, 0};
		}

		Vec3	   UnitDirection = UnitVector(Light.RayDirection());
		const auto a			 = 0.5 * (UnitDirection.Y() + 1.0);
		auto	   Result		 = (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);

		return Result;
	}

public:
	std::shared_ptr<Device> Graphics;

	int	   ImageHeight;
	Point3 CameraCenter;

	Vec3 PixelDeltaU;
	Vec3 PixelDeltaV;
	Vec3 Pixel100Loc;

	Vec3 U;
	Vec3 V;
	Vec3 W;
	Vec3 DefocusDiskU;
	Vec3 DefocusDiskV;
};