// Raytracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
// TODO: Split raytracer itself from rendering. We create an image buffer using raytracing and then we 
// pass a reference to the buffer to the renderer. Once we've passed the buffer we can then use an SDL
// Adapter to adapt our pure buffer the screen. Possibly in the future we could develop an algo that can
// Turn our arbitrarily sized image into a smaller one with math.
#include <iostream>
#include "CApp.hpp"
#include "raytrace/line/Matrix4.hpp"
int main() {
    CApp theApp;
    std::cout << "Output:\n";
    return theApp.OnExecute();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
