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
 * \file material.h
 * \brief 材质抽象类
 */

#pragma once

#include <color.h>
#include <hittableList.h>
#include <rtweekend.h>

class HitRecord;

class Material {
public:
	virtual ~Material()						   = default;
	virtual bool Scatter(const Ray& LightIn, const HitRecord& Record, Color& Attenuation,
						 Ray& Scattered) const = 0;
};

// 朗伯漫反射材质
class Lambertian : public Material {
public:
	Lambertian(const Color& IAlbedo) : Albedo(IAlbedo) {
	}
	bool Scatter(const Ray& LightIn, const HitRecord& Record, Color& Attenuation,
				 Ray& Scattered) const override {
		auto ScatterDirection = Record.NormalVector + RandomUnitVector();
		if (ScatterDirection.NearZero()) {
			ScatterDirection = Record.NormalVector;
		}

		Scattered	= Ray(Record.Point, ScatterDirection);
		Attenuation = Albedo;

		return true;
	}

private:
	Color Albedo;
};

class Metal : public Material {
public:
	Metal(const Color& IAlbedo, const double& IFuzz)
		: Albedo(IAlbedo), Fuzz(IFuzz < 1 ? IFuzz : 1) {
	}
	bool Scatter(const Ray& LightIn, const HitRecord& Record, Color& Attenuation,
				 Ray& Scattered) const override {
		Vec3 Reflected = Reflect(UnitVector(LightIn.RayDirection()), Record.NormalVector);
		Scattered	   = Ray(Record.Point, Reflected + Fuzz * RandomUnitVector());
		Attenuation	   = Albedo;

		return (Dot(Scattered.RayDirection(), Record.NormalVector) > 0);
	}

private:
	Color  Albedo;
	double Fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(const double& Refraction) : IndexRefraction(Refraction) {
	}
	bool Scatter(const Ray& LightIn, const HitRecord& Record, Color& Attenuation,
				 Ray& Scattered) const override {
		Attenuation			   = Color{1.f, 1.f, 1.f};
		double RefractionRatio = Record.FrontFace ? (1.f / IndexRefraction) : IndexRefraction;

		Vec3 UnitDirection = UnitVector(LightIn.RayDirection());

		double CosTheta = fmin(Dot(-UnitDirection, Record.NormalVector), 1.f);
		double SinTheta = sqrt(1.f - CosTheta * CosTheta);
		Vec3 Direction;

		if (RefractionRatio * SinTheta > 1.f || Reflectance(CosTheta, RefractionRatio) > RandomDouble()) {
			Direction = Reflect(UnitDirection, Record.NormalVector);
		} else {
			Direction = Refract(UnitDirection, Record.NormalVector, RefractionRatio);
		}

		Scattered = Ray(Record.Point, Direction);

		return true;
	}

private:
	// Schlick 近似法
	static double Reflectance(const double& Cosine, const double& RefIndex) {
		auto R0 = (1 - RefIndex) / (1 + RefIndex);
		R0 *= R0;

		return R0 + (1 - R0) * pow((1 - Cosine), 5);
	}

private:
	double IndexRefraction;
};