#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
	TextureManager::Instance().load("../Assets/textures/A1_background.png", "bg");

	auto size = TextureManager::Instance().getTextureSize("bg");
	setWidth(size.x);
	setHeight(size.y);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance().draw("bg",
		getTransform()->position.x, getTransform()->position.y, 0, 255, false);
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), xi, yi, xi + d, yi);

	// ----------------------------
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	if (startFlag)
	{
		// pre-calculing varibles
		float dt = Game::Instance().getDeltaTime();
		t += dt;	// gets a estimate time in seconds

		Vx = cos(-launchAng * DEG_TO_RADIANS) * v;
		Vy = sin(-launchAng * DEG_TO_RADIANS) * v;

		// finding final position
		xf = xi + Vx * t;
		yf = yi + Vy * t + (0.5f * g * pow(t, 2));

		// updating new position
		m_pParticle->getTransform()->position = glm::vec2(xf, yf);
	}

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		t = 0.0f;
		m_pParticle->getTransform()->position.x = 100.0f;
		m_pParticle->getTransform()->position.y = 500.0f;

		startFlag = false;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		startFlag = true;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	

	m_pParticle = new Particle();
	addChild(m_pParticle);
	m_pParticle->getTransform()->position = glm::vec2(100, 500);
	xi = m_pParticle->getTransform()->position.x;
	yi = m_pParticle->getTransform()->position.y;
	 

	/* Labels */
	m_pStart = new Label("Press (S) to start the motion", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(476.0f, 30.0f));
	addChild(m_pStart);

	m_pRestart = new Label("Press (R) to Restart the level motion", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(520.0f, 60.0f));
	addChild(m_pRestart);
	
	m_pInstructionsLabel = new Label("Press (`) to toggle Debug View", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(483.0f, 90.0f));
	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Assignment 1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("IniPos X", &xi, 50.0f, 750.0f, "%.1f,");
	ImGui::SliderFloat("IniPos Y", &yi, 50.0f, 550.0f, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Velocity", &v, 0.f, 100.0f, "%.1f,");
	ImGui::SliderFloat("Launch Angle", &launchAng, 0.0f, 90.0f, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Gravity", &g, -5.0f, 20.0f, "%.1f,");
	ImGui::SliderFloat("Distance", &d, 0.0f, 600, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Time", &t, -10.f, 100.0f, "%.1f,");
	
	// ------------------------------------
	ImGui::End();
}
