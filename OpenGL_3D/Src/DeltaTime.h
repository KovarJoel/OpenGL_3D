#pragma once

class DeltaTime
{
private:
	static double lastFrame;
	static double deltaTime;

	DeltaTime() = default;
	DeltaTime(const DeltaTime& original) = default;
	~DeltaTime() = default;

public:
	// set the new frames time in seconds
	static void set(double newFrameTime);
	// get deltaTime in seconds
	static double get();
	// get the current FPS
	static double getFPS();
};