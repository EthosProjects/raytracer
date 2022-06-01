#pragma once
#include <string>
#include <vector>
#include "../SDL2/SDL.h"
class qbImage {
public:
    qbImage();
    ~qbImage();
    // initialize the image
    void initialize (const int xSize, const int ySize, SDL_Renderer *pRenderer);
    // stet pixel color
    void setPixel (const int x, const int y, const double red, const double green, const double blue);
    //display stuff
    void display();
    //Size getters
    int getXSize();
    int getYSize();
private: 
    uint32_t convertColor(const double red, const double green, const double blue);
    void initTexture();
    void computeMaxValues();
private:
    //Image stuff
    std::vector<std::vector<double>> m_redChannel;
    std::vector<std::vector<double>> m_greenChannel;
    std::vector<std::vector<double>> m_blueChannel;
    double maxRed, maxGreen, maxBlue, maxColor;
    int m_xSize, m_ySize;
    //SDL Stuff
    SDL_Renderer* m_p_renderer;
    SDL_Texture* m_p_texture;
};