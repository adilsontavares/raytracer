#include <iostream>
#include <vector>

#include "Vector3.h"
#include "Bitmap.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

int main(int argc, char *argv[])
{
	Size size(640, 640);
	Bitmap bmp(size);
	Color color;

	double aspectRatio = (double)size.getWidth() / size.getHeight();

	Vector3 cameraPosition = Vector3(3, 1.5, -4);
	Vector3 lookAt = Vector3::zero();
	Vector3 diff = cameraPosition - lookAt;
	Vector3 cameraDirection = diff.negative().normalized();
	Vector3 cameraRight = Vector3::up().cross(cameraDirection).normalized();
	Vector3 cameraDown = cameraRight.cross(cameraDirection);
	Vector3 lightPosition(-7, 10, -10);
	Color sphereColor(0.5f, 1.0f, 0.5f, 0.3f);
	Color planeColor(0.5f, 0.25f, 0.25f, 0.f);

	Camera camera(cameraPosition, cameraDirection, cameraRight, cameraDown);
	Light light(lightPosition, Color::white());
	Sphere sphere(Vector3::zero(), 1, sphereColor);
	Plane plane(Vector3::up(), -1, planeColor);

	std::vector<Object*> sceneObjects;
	sceneObjects.push_back(&plane);
	sceneObjects.push_back(&sphere);

	double xamnt;
	double yamnt;

	for (unsigned int x = 0; x < size.getWidth(); ++x)
	{
		for (unsigned int y = 0; y < size.getHeight(); ++y)
		{
			if (size.getWidth() > size.getHeight())
			{
				// image is LANDSCAPE
				xamnt = ((x + 0.5) / size.getWidth()) * aspectRatio - (((size.getWidth() - size.getHeight()) / (double)size.getHeight()) / 2.0);
				yamnt = ((size.getHeight() - y) + 0.5) / size.getHeight();
			}
			else if (size.getHeight() > size.getWidth())
			{
				// image is PORTRAIT
				xamnt = (x + 0.5) / size.getWidth();
				yamnt = (((size.getHeight() - y) + 0.5) / size.getHeight()) / aspectRatio - (((size.getHeight() - size.getWidth()) / (double)size.getWidth()) / 2);
			}
			else
			{
				// image is SQUARED
				xamnt = (x + 0.5) / size.getWidth();
				yamnt = ((size.getHeight() - y) + 0.5) / size.getHeight();
			}

			Vector3 rayOrigin = camera.getPosition();
			Vector3 rayDirection = (cameraDirection + cameraRight * (xamnt - 0.5) + cameraDown * (yamnt - 0.5)).normalized();

			Ray ray(rayOrigin, rayDirection);

			double firstIntersection;
			int firstIntersectionIndex = -1;

			for (int i = 0; i < sceneObjects.size(); ++i)
			{
				double distance = sceneObjects.at(i)->intersection(ray);
				if (distance > 0 && (firstIntersectionIndex == -1 || distance < firstIntersection))
				{
					firstIntersectionIndex = i;
					firstIntersection = distance;
				}
			}

			if (firstIntersectionIndex >= 0)
			{
				color = sceneObjects.at(firstIntersectionIndex)->getColor();
			}
			else
			{
				color = Color::gray();
			}

			bmp.setPixel(x, y, color);
		}
	}

	bmp.save("C:\\Users\\Adilson\\Desktop\\hello_world.bmp");

	printf("Press ENTER to exit...\n");
	getchar();

	return 0;
}