#pragma once
#include "CApp.hpp"
#include <iostream>
#include "raytrace/Camera.hpp"
CApp::CApp() {
	isRunning = true;
	p_window = NULL;
	p_renderer = NULL;
}

bool CApp::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	p_window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 405, SDL_WINDOW_SHOWN);

	if (p_window != NULL) p_renderer = SDL_CreateRenderer(p_window, -1, 0);
	else return false;
    m_qbImage.initialize(720, 405, p_renderer);
	SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
	SDL_RenderClear(p_renderer);

    m_scene.render(m_qbImage);
    m_qbImage.display();

	SDL_RenderPresent(p_renderer);

	return true;
}
int CApp::OnExecute() {
	SDL_Event event;
	if (OnInit() == false) return -1;
	while (isRunning) {
		while (SDL_PollEvent(&event) != 0) OnEvent(&event);
		OnLoop();
		OnRender();
	}
}
void CApp::OnEvent(SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		isRunning = false;
	}
}
void CApp::OnLoop() {
}
void CApp::OnRender() {
}

void CApp::OnExit() {
	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);
	p_window = NULL;
	SDL_Quit();
}