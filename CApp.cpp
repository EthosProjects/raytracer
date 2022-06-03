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
    int width = 736;
    int height = width * 9 / 16;

    // TODO: begin marking various TODOs with numbers for easy reference
    
    // TODO: Arbitrary conversion algorithm
    // The method for doing so is as follows
    // I create an upscaled image using the least common multiple of their widths and heights
    // then i take all the pixels of the output and average them together
    // with this average I can then output the image at the desired size
    // This will allow me to begin testing the console tracer which I will test first by outputting
    // to the screen at the desired resolution of the console
    // This method will allow me to do raytraced supersampling later on, with a more sophisticated algor
    // ithm. I may be able to display simple color in the console as well. My output exe file hopefully
    // Will start a console, then compute the raytracer, then output the image as expected
    // I want to also be able to port this library from SDL. Possibly to opencl. currently I'm
    // Unsure but I'll focus for now

    // NOTE: related to above TODO. There may be an algorith similar to what I described
    // where it basically solves to find how much of each input pixel the output pixel will take up
    // and then taking a weighted average. This would be functionally equivalent to my original idea
    // but significantly faster as its likely been heavily optimized previously
    p_window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (p_window != NULL) p_renderer = SDL_CreateRenderer(p_window, -1, 0);
	else return false;
    m_qbImage.initialize(width, height, p_renderer);
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