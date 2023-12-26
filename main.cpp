#define UNICODE
#define _UNICODE

#include <rtweekend.h>

#include <camera.h>
#include <color.h>
#include <device.h>
#include <hittableList.h>
#include <sphere.h>

#include <conio.h>

int main() {
	// 渲染场景

	HittableList World;

	auto GroundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	World.Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, GroundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto   ChooseMat = RandomDouble();
			Point3 Center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

			if ((Center - Point3(4, 0.2, 0)).Length() > 0.9) {
				std::shared_ptr<Material> SphereMaterial;

				if (ChooseMat < 0.8) {
					auto Albedo	   = Color::Random() * Color::Random();
					SphereMaterial = std::make_shared<Lambertian>(Albedo);
					World.Add(std::make_shared<Sphere>(Center, 0.2, SphereMaterial));
				} else if (ChooseMat < 0.95) {
					auto Albedo	   = Color::Random(0.5, 1);
					auto Fuzz	   = RandomDouble(0, 0.5);
					SphereMaterial = std::make_shared<Metal>(Albedo, Fuzz);
					World.Add(std::make_shared<Sphere>(Center, 0.2, SphereMaterial));
				} else {
					SphereMaterial = std::make_shared<Dielectric>(1.5);
					World.Add(std::make_shared<Sphere>(Center, 0.2, SphereMaterial));
				}
			}
		}
	}

	auto Material1 = std::make_shared<Dielectric>(1.5);
	World.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, Material1));

	auto Material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	World.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, Material2));

	auto Material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	World.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, Material3));

	Camera WorldCamera;

	WorldCamera.AspectRatio		= 256.f / 192.f;
	WorldCamera.ImageWidth		= 256;
	WorldCamera.SamplesPerPixel = 50;
	WorldCamera.MaxDepth		= 50;

	WorldCamera.VFov	 = 20;
	WorldCamera.LookFrom = Point3(13, 2, 3);
	WorldCamera.LookAt	 = Point3(0, 0, 0);
	WorldCamera.VUP		 = Vec3(0, 1, 0);

	WorldCamera.DefocusAngle  = 0.6;
	WorldCamera.FocusDistance = 10.f;

	WorldCamera.Render(World);

	saveimage(L"./final.png");

	_getch();

	return 0;
}
