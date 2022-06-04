#pragma once
#include <SDL2/SDL.h>
#include "raytrace/qbImage.hpp"
#include "raytrace/Scene.hpp"
class CApp {
public: 
	CApp();
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event *event);
	void OnLoop();
	void OnRender();
	void OnExit();
private:
    Scene m_scene;
    qbImage m_qbImage;
	// SDL2 stuff
	bool isRunning;
	SDL_Window* p_window;
	SDL_Renderer* p_renderer;

};