#include "QuatApp.h"
#include "Trig.h"

void QuatApp::Slerp(Quat& result, const Quat& source, const Quat& target, 
	const float slerpFactor)
{
	float cosTheta = source.dot(target);
	// Angle between the quaternions is greater than 90 degrees.
	if (cosTheta < 0.0f)
	{
		float theta = Trig::acos(-cosTheta);
		result = (source * (Trig::sin((1 - slerpFactor) * theta) / Trig::sin(theta)))
			+ (-target * (Trig::sin(slerpFactor * theta) / Trig::sin(theta)));
	}
	else if (cosTheta < 1.0f)
	{
		float theta = Trig::acos(cosTheta);
		result = (source * (Trig::sin((1 - slerpFactor) * theta) / Trig::sin(theta)))
			+ (target * (Trig::sin(slerpFactor * theta) / Trig::sin(theta)));
	}
	// If the angle between the quaternions is 0, the source and target are the same.
	else
	{
		result = source;
	}
}
void QuatApp::SlerpArray(Quat* result, const Quat* source, const Quat* target, 
	const float slerpFactor, const int numQuats)
{
	for (int i = 0; i < numQuats; i++)
	{
		float cosTheta = source[i].dot(target[i]);
		// Angle between the quaternions is greater than 90 degrees.
		if (cosTheta < 0.0f)
		{
			float theta = Trig::acos(-cosTheta);
			result[i] = (source[i] * (Trig::sin((1 - slerpFactor) * theta) / Trig::sin(theta))) 
				+ (-target[i] * (Trig::sin(slerpFactor * theta) / Trig::sin(theta)));
		}
		else if (cosTheta < 1.0f)
		{
			float theta = Trig::acos(cosTheta);
			result[i] = (source[i] * (Trig::sin((1 - slerpFactor) * theta) / Trig::sin(theta)))
				+ (target[i] * (Trig::sin(slerpFactor * theta) / Trig::sin(theta)));
		}
		// If the angle between the quaternions is 0, the source and target are the same.
		else
		{
			result[i] = source[i];
		}
	}
}
