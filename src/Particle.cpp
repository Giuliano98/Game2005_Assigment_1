#include "Particle.h"
#include "TextureManager.h"

Particle::Particle()
{
	TextureManager::Instance().load("../Assets/textures/ship3.png", "particle");

	auto size = TextureManager::Instance().getTextureSize("particle");
	setWidth(size.x);
	setHeight(size.y);
}

Particle::~Particle()
{
}

void Particle::draw()
{
	TextureManager::Instance().draw("particle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Particle::update()
{
}

void Particle::clean()
{
}
