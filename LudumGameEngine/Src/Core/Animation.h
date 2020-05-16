#pragma once

class Animation {
public:
	unsigned int index;
	unsigned int numFrame;
	unsigned int animationSpeed;

	Animation();
	Animation(unsigned int index, unsigned int numFrame, unsigned int animationSpeed);
	~Animation();
};