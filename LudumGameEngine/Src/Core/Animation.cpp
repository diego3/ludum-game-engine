#include "Animation.h"

Animation::Animation()
{
	animationSpeed = 0;
	index = 0;
	numFrame = 0;
}

Animation::Animation(unsigned int index, unsigned int numFrame, unsigned int animationSpeed)
{
	this->animationSpeed = animationSpeed;
	this->index = index;
	this->numFrame = numFrame;
}

Animation::~Animation()
{
}
