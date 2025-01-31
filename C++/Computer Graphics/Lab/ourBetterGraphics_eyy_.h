#pragma once
#include <Windows.h>
#include <cmath>
#include <algorithm>
#include <vector>
constexpr float pi = 3.14159f;
constexpr int max_Vertex = 12;

struct Vect2 {
	float x, y;
};
struct Bect2 {
	int x, y;
};
class Vect3 {
public:
	int x, y, z;
	Vect3(int x = 0, int y = 0, int z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
struct Bitmap {
	BITMAPINFO info;
	int width, height;
	void* memory;
};
int counterGod;
Bitmap globalBuffer;
bool globalRunning = true;

void consoleLog(const char* out) {
	OutputDebugStringA(out);
}
void consoleLog(int out) {
	char output[100];
	sprintf_s(output, 100, "%d", out);
	OutputDebugStringA(output);
}
void consoleLogSpace(int out) {
	char output[100];
	sprintf_s(output, 100, "%d\n", out);
	OutputDebugStringA(output);
}

int Clamp(int current, int min, int max) {
	return current < min ? min : current > max ? max : current;
}
void drawRect(Bect2 v1, Bect2 v2, unsigned int color) {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory + v1.y * globalBuffer.height + v1.x;

	for (int y = v1.y; y < v2.y; y++) {
		for (int x = v1.x; x < v2.x; x++) {
			*pixel++ = color;
		}
		pixel += globalBuffer.width - (v2.x - v1.x);
	}
}
void clrScr() {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory;

	for (int y = 0; y < globalBuffer.height; y++) {
		for (int x = 0; x < globalBuffer.width; x++) {
			*pixel++ = 0;
		}
	}
}
inline void drawPixel(int x, int y, unsigned int color) {
	*((unsigned int*)globalBuffer.memory + y * globalBuffer.width + x) = color;
}
void drawDDALine(Bect2 v1, Bect2 v2, unsigned int color)
{
	int dx, dy, steps;
	float xincr, yincr, x, y;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;

	if (abs(dx) >= abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	xincr = (float)dx / steps;
	yincr = (float)dy / steps;

	x = v1.x;
	y = v1.y;

	for (int k = 1; k <= steps; k++)
	{
		drawPixel((int)(x + 0.5f), (int)(y + 0.5f), color);
		x += xincr;
		y += yincr;
	}
}
void drawBresLine(Bect2 v1, Bect2 v2, unsigned int color) {
	//Bresengham's Algorithm
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (v2.x < v1.x) incx = -1;
	incy = 1;
	if (v2.y < v1.y) incy = -1;
	x = v1.x; y = v1.y;
	if (dx > dy) {
		drawPixel(x, y, color);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			drawPixel(x, y, color);
		}

	}
	else {
		drawPixel(x, y, color);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			drawPixel(x, y, color);
		}
	}
}
void matMul(float mat1[][3], float mat2[][3], float ans[][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ans[i][j] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				ans[i][j] += mat1[i][k] * mat2[k][j];
}
void translation(float point[][3], float newPoint[][3], Vect2 translationFactor) {
	float composite[3][3] = { {1,0,translationFactor.x},{0,1,translationFactor.y},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotation(float point[][3], float newPoint[][3], int angle) {
	float rad = 3.14 * angle / 180;
	float composite[3][3] = { {cos(rad),-sin(rad),0},{sin(rad),cos(rad),0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotate(float point[][3], float newPoint[][3], float rad) {
	float composite[3][3] = { {cos(rad),-sin(rad),0},{sin(rad),cos(rad),0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scaling(float point[][3], float newPoint[][3], Vect2 scalingFactor) {
	float composite[3][3] = { {scalingFactor.x,0,0},{0,scalingFactor.y,0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scale(float point[][3], float newPoint[][3], float sx, float sy) {
	float composite[3][3] = { {sx,0,0},{0,sy,0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotationPivot(float point[][3], float newPoint[][3], int angle, Bect2 pivot) {
	float rad = 3.14 * angle / 180;
	float composite[3][3] = { {cos(rad),-sin(rad),pivot.x * (1 - cos(rad)) + pivot.y * sin(rad)},
		{sin(rad),cos(rad),pivot.y * (1 - cos(rad)) - pivot.x * sin(rad)},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scalingFixed(float point[][3], float newPoint[][3], Bect2 fixedPoint, Vect2 scalingFactor) {
	float composite[3][3] = { {scalingFactor.x,0,fixedPoint.x * (1 - fixedPoint.x)},
		{0,scalingFactor.y,fixedPoint.y * (1 - scalingFactor.y)},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scalingWithAngle(float point[][3], float newPoint[][3], int angle, Vect2 scalingFactor) {
	float rad = 3.14 * angle / 180;
	rotate(point, newPoint, -rad);
	scale(newPoint, newPoint, scalingFactor.x, scalingFactor.y);
	rotate(newPoint, newPoint, rad);
}
//1.y=0 2.x=0 3.y=x 4.y=-x
void reflection(float point[][3], float newPoint[][3], int choice) {
	switch (choice)
	{
	case 1: {
		float composite1[3][3] = { {1,0,0},{0,-1,0},{0,0,1} };
		matMul(composite1, point, newPoint);
		break;
	}
	case 2: {
		float composite2[3][3] = { {-1,0,0},{0,1,0},{0,0,1} };
		matMul(composite2, point, newPoint);
		break;
	}
	case 3: {
		float composite3[3][3] = { {0,1,0},{1,0,0},{0,0,1} };
		matMul(composite3, point, newPoint);
		break;
	}
	case 4: {
		float composite4[3][3] = { {0,-1,0},{-1,0,0},{0,0,1} };
		matMul(composite4, point, newPoint);
		break;
	}
	}
}
void shearing(float point[][3], float newPoint[][3], int choice, Vect2 shearingParams) {
	//1.x-direction relative to x-axis(y=0) 2.y-direction relative to yaxis(x=0) 3.In both direction
	switch (choice) {
	case 1: {
		float composite2[3][3] = { {1,shearingParams.x,0},{0,1,0},{0,0,1} };
		matMul(composite2, point, newPoint);
		break;
	}
	case 2: {
		float composite3[3][3] = { {1,0,0},{shearingParams.y,1,0},{0,0,1} };
		matMul(composite3, point, newPoint);
		break;
	}
	case 3: {
		float composite1[3][3] = { {1,shearingParams.x,0},{shearingParams.y,1,0},{0,0,1} };
		matMul(composite1, point, newPoint);
	}
	default:
		break;
	}
}
void shearigRef(float point[][3], float newPoint[][3], int choice, float shearingParameter, float referenceParameter)
{
	//1.x-direction relative to y=yref 2.y-direction relative to x=xref
	switch (choice) {
	case 1: {
		float composite1[3][3] = { {1,shearingParameter,-shearingParameter * referenceParameter},{0,1,0},{0,0,1} };
		matMul(composite1, point, newPoint);
		break;
	}
	case 2: {
		float composite2[3][3] = { {1,0,0},{shearingParameter,1,-shearingParameter * referenceParameter},{0,0,1} };
		matMul(composite2, point, newPoint);
		break;
	}
	default:
		break;
	}
}
void drawTriangle(float newPoint[][3], unsigned color) {
	int nx1 = newPoint[0][0];
	int ny1 = newPoint[1][0];
	int nx2 = newPoint[0][1];
	int ny2 = newPoint[1][1];
	int nx3 = newPoint[0][2];
	int ny3 = newPoint[1][2];

	//Draw Output
	drawBresLine(Bect2{ nx1 + 500, ny1 + 400 }, Bect2{ nx2 + 500, ny2 + 400 }, color);
	drawBresLine(Bect2{ nx2 + 500, ny2 + 400 }, Bect2{ nx3 + 500, ny3 + 400 }, color);
	drawBresLine(Bect2{ nx3 + 500, ny3 + 400 }, Bect2{ nx1 + 500, ny1 + 400 }, color);
}
int getMaxX() {
	return globalBuffer.width / 2;
}
int getMaxY() {
	return globalBuffer.height / 2;
}

void DDAlgorithm(float x1, float y1, float x2, float y2) {
	drawDDALine(Bect2{ (int)x1,(int)y1 }, Bect2{ (int)x2, (int)y2 }, 0xffffff);
}
void DDAlgorithm(float x1, float y1, float x2, float y2, unsigned color) {
	drawDDALine(Bect2{ (int)x1,(int)y1 }, Bect2{ (int)x2, (int)y2 }, color);
}