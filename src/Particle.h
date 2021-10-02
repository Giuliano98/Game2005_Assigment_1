#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__
#include "DisplayObject.h"

class Particle final : public DisplayObject
{
public:
	Particle();
	~Particle();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	
};

#endif /* defined (__PARTICLE__) */