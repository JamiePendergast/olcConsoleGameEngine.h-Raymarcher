// Console Raymarcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "olcConsoleGameEngine.h"
#include "sRaymarchSettings.h"
#include "sVector3.h"

class cApplication : public olcConsoleGameEngine {
private:
	const sRaymarchSettings settings;


protected:
	double Sphere (sVector3 point, double radius = 0.5) {
		return point.length () - radius;
	}

	double Trace (sVector3 ray_origin, sVector3 ray_direction) {
		sVector3 point;
		double T = 0.0;
		for (int i = 0; i < settings.stepCount; i++) {
			T += Sphere (point) * 0.5;
			point = ray_origin + ray_direction * T;
		}
		return T;
	}

	std::pair<SHORT,SHORT> GetColor (double Ratio) {
		std::pair<SHORT, SHORT> pixel_and_color;
		if (Ratio == 1.0) {
			pixel_and_color.first = PIXEL_SOLID;
			pixel_and_color.second = FG_WHITE;
		}
		else if (Ratio < 1.0 && Ratio >= 0.75) {
			pixel_and_color.first = PIXEL_THREEQUARTERS;
			pixel_and_color.second = FG_GREY;
		}
		else if (Ratio < 0.75 && Ratio >= 0.5) {
			pixel_and_color.first = PIXEL_HALF;
			pixel_and_color.second = FG_GREY;
		}
		else if (Ratio < 0.5 && Ratio >= 0.25) {
			pixel_and_color.first = PIXEL_QUARTER;
			pixel_and_color.second = FG_DARK_GREY;
		}
		else {
			pixel_and_color.first = PIXEL_SOLID;
			pixel_and_color.second = FG_BLACK;
		}

		return pixel_and_color;
	}

	bool OnUserCreate () override {
		return true;
	}

	bool OnUserUpdate (float fElapsedTime) override {
		sVector3 ray_direction;
		sVector3 ray_origin{ 0.0,0.0,-1.0 };

		for (int y = 0; y < settings.height; y++) {
			const double uv_Y = (y / (double)settings.height) - 0.5;			

			for (int x = 0; x < settings.width; x++) {
				const double uv_X = (x / (double)settings.width) - 0.5;
				ray_direction.x = 2.0 * uv_X;
				ray_direction.y = 2.0 * (uv_Y);
				ray_direction.z = settings.fov;

				ray_direction = ray_direction.normalized ();

				double T = Trace (ray_origin, ray_direction);
				T = 1. / (1. + T * T * 0.1); //Fogging function
				std::pair<SHORT, SHORT> values = GetColor (T);
				Draw (x, y, values.first, values.second);
			}
		}

		DrawString (0, 0, L"Testing", FG_WHITE);
		return true;
	}

public:
	cApplication (const sRaymarchSettings settings) : settings{ settings } {
	}
};


int main() {
	const int width  { 100 };
	const int height { 100 };
	
	cApplication app ({ 1.0,0.5,32,width,height});
	app.ConstructConsole (width, height, 8, 8);
	app.Start ();
    return 0;
}

