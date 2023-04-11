#pragma once
#include <cmath>
#include <numbers>
#include <math.h>

class CEasing {
public:
	// üŒ`•âŠÔ
	float lerp(float startPos, float endPos, float t)
	{
		float val;
		val = startPos + t * (endPos - startPos);
		return val;
	}
	// “™‘¬’¼ü‰^“®
	float liner(float t, float speed)
	{
		float x;
		x = t * speed;
		return x;
	}

	// ƒC[ƒYƒCƒ“
	float easeIn(float x)
	{
		return x * x * x;
	}

	float easeOut(float x)
	{
		return 1 + (x - 1) * (x - 1) * (x - 1);
	}

	/*float easeOutBack(float x) {
		return 1 - (x - 1) * (x - 1) * (-2.70158 * (x - 1) - 1.70158);
	}*/

	// ƒC[ƒYƒAƒEƒg
	float easeOutElastic(float x)
	{
		float amplitude = 1.0f;
		float period = 0.01f;
		float val = amplitude * std::pow(2, -3 * x) * std::sinf((x - (period / (2 * 3.14) * std::asin(1 / amplitude))) * (2 * 3.14) / period) + 1;

		return val;
	}

	//sin”g       x:U•  w:Špü”g”  t:•b
	float SinVibe(float x, float w, float t)
	{
		float val;
		float w2 = w * 3.14f;
		val = x * sinf(w2 * t);

		return val;
	}
	// •ú•¨ü
	float Parabola(float y,float t) {
		float vy = y;
		float g = 9.8f;
		vy -= (g * t);

		return vy;
	}
	// “™‰Á‘¬“x’¼ü‰^“®
	float addv(float a, float v,float t) {
		float vx = v + a * t;
		float val = vx * t;

		return val;
	}

	static CEasing& GetInstance() {
		static CEasing Instance;
		return Instance;
	}
};