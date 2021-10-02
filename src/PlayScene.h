#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Particle.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Particle* m_pParticle;
	/*float t = 0.0f;
	float c = 500;
	float v = -100;
	float a = 10;*/
	const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;
	float t = 0.0f;
	float v = 90.0f;
	float d = 485.0f;
	float g = 9.8f;
	float xi = 0.0f;
	float xf = 0.0f;
	float yi = 0.0f;
	float yf = 0.0f;
	float launchAng = 63.606f;
	float vx = cos(-launchAng * DEG_TO_RADIANS) * v;
	float vy = sin(-launchAng * DEG_TO_RADIANS) * v;

	//Plane* m_pPlaneSprite;
	//Player* m_pPlayer;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__PLAY_SCENE__) */