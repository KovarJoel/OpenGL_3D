#include "DeltaTime.h"

double DeltaTime::lastFrame = 0.0f;
double DeltaTime::deltaTime = 0.0f;

void DeltaTime::set(double newFrameTime)
{
	deltaTime = newFrameTime - lastFrame;
	lastFrame = newFrameTime;
}

double DeltaTime::get()
{
	return deltaTime;
}

double DeltaTime::getFPS()
{
	return (1.0f / deltaTime);
}