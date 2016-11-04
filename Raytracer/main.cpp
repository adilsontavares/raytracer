#include <iostream>
#include <vector>

#include "Vector3.h"
#include "Bitmap.h"
#include "Camera.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Plane.h"

std::vector<Object*> sceneObjects;
std::vector<LightSource*> lightSources;
double accurancy = 0.000001;

Color getIntersectionColorAt(Vector3 position, Vector3 direction, unsigned int sceneObjectIndex, double ambientLight)
{
	Object *sceneObject = sceneObjects.at(sceneObjectIndex);

	Color color = sceneObject->getColor();
	Vector3 normal = sceneObject->getNormalAt(position);

	Color finalColor = color * ambientLight;

	for (int i = 0; i < lightSources.size(); ++i)
	{
		LightSource *source = lightSources.at(i);
		Vector3 lightDirection = (source->getPosition() - position).normalized();

		float cosine = normal.dot(lightDirection);

		if (cosine > 0) // test for shadows
		{
			bool shadowed = false;

			Vector3 distanceToLight = (source->getPosition() - position).normalized();
			double distanceToLightMag = distanceToLight.magnitude();

			Ray shadowRay(position, distanceToLight);

			std::vector<double> intersections;

			for (int j = 0; j < sceneObjects.size(); ++j)
				intersections.push_back(sceneObjects.at(j)->intersection(shadowRay));

			for (int j = 0; j < intersections.size() && !shadowed; ++j)
			{
				if (intersections.at(j) > accurancy)
				{
					if (intersections.at(j) <= distanceToLightMag)
						shadowed = true;
				}
			}

			if (!shadowed)
			{
				finalColor = finalColor + color * source->getColor() * cosine;

				// Scene object color (0 > SPECIAL >= 1)
				if (color.getS() > 0 && color.getS() <= 1.0)
				{
					double dot1 = normal.dot(direction.negative());
					Vector3 scalar1 = normal * dot1;
					Vector3 add1 = scalar1 + direction;

					Vector3 scalar2 = add1 * 2;
					Vector3 add2 = scalar2 - direction;
					
					Vector3 reflectionDirection = add2.normalized();

					double specular = reflectionDirection.dot(lightDirection);
					if (specular > 0)
					{
						specular = pow(specular, 10);
						finalColor = finalColor + source->getColor() * (specular * color.getS());
					}
				}
			}
		}
	}

	return finalColor.clipping();
}

int main(int argc, char *argv[])
{
	Size size(640, 640);
	Bitmap bmp(size);
	Color color;

	double aspectRatio = (double)size.getWidth() / size.getHeight();
	double ambientLight = 0.2;

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
	PointLight light(lightPosition, Color::white());
	Sphere sphere(Vector3::zero(), 1, sphereColor);
	Plane plane(Vector3::up(), -1, planeColor);

	sceneObjects.push_back(&plane);
	sceneObjects.push_back(&sphere);

	lightSources.push_back(&light);

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
				if (distance > accurancy && (firstIntersectionIndex == -1 || distance < firstIntersection))
				{
					firstIntersectionIndex = i;
					firstIntersection = distance;
				}
			}

			if (firstIntersectionIndex >= 0)
			{
				Vector3 intersectionPosition = rayOrigin + rayDirection * firstIntersection;
				Vector3 intersectionDirection = rayDirection;

				//color = sceneObjects.at(firstIntersectionIndex)->getColor();

				color = getIntersectionColorAt(intersectionPosition, intersectionDirection, firstIntersectionIndex, ambientLight);
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