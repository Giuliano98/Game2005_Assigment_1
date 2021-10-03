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
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), xi, yi, xi + 485, yi);

	// ----------------------------
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	// pre-calculing varibles
	float dt = Game::Instance().getDeltaTime();
	t += dt;	// gets a estimate of seconds 

	updateDisplayList();
	
	
	//std::cout << t << std::endl;
	// finding final position
	xf = xi + Vx * t;
	yf = yi + Vy * t + g * 0.5f * pow(t, 2);

	m_pParticle->getTransform()->position = glm::vec2(xf, yf);
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
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	

	m_pParticle = new Particle();
	addChild(m_pParticle);
	m_pParticle->getTransform()->position = glm::vec2(100, 400);
	xi = m_pParticle->getTransform()->position.x;
	yi = m_pParticle->getTransform()->position.y;
	 
	

	/* Instructions Label */
	/*m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);*/

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("Launch Angle", &launchAng, -90.f, 180.0f, "%.1f,");
	ImGui::SliderFloat("Velocity", &v, 0.f, 100.0f, "%.1f,");
	//ImGui::SliderFloat("Start Point", &xi, 0.f, 100.0f, "%.1f,");
	ImGui::SliderFloat("Gravity", &g, -5.0f, 20.0f, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Time", &t, -10.f, 100.0f, "%.1f,");

	/*if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}*/
	
	ImGui::End();
}
