#pragma once

struct sRaymarchSettings {
	const double fov;
	const double stepLength;
	const int stepCount;
	const int width;
	const int height;

	sRaymarchSettings(const double fov, 
		const double stepLength,
		const int stepCount,
		const int width,
		const int height) :
		fov{fov},
		stepLength{ stepLength },
		stepCount{ stepCount },
		width{ width },
		height{ height }
	{}
	
};