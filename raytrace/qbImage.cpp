#pragma once
#include "qbImage.hpp"
qbImage::qbImage () {
    m_xSize = 0;
    m_ySize = 0;
    m_p_texture = NULL;
}
qbImage::~qbImage () {
    if (m_p_texture != NULL) SDL_DestroyTexture(m_p_texture);
}
void qbImage::initialize(const int xSize, const int ySize, SDL_Renderer* p_renderer) {
    m_redChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_greenChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_blueChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    m_xSize = xSize;
    m_ySize = ySize;
    m_p_renderer = p_renderer;

    initTexture();
}

void qbImage::setPixel (const int x, const int y, const double red, const double green, const double blue) {
    m_redChannel.at(x).at(y) = red;
    m_greenChannel.at(x).at(y) = green;
    m_blueChannel.at(x).at(y) = blue;
}
void qbImage::display() {
    uint32_t* tempPixels = new uint32_t[m_xSize * m_ySize];
    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(uint32_t));
    for (int x = 0;x < m_xSize;x++) {
        for (int y = 0; y < m_ySize;y++) {
            tempPixels[(y * m_xSize) + x] = convertColor(
                m_redChannel.at(x).at(y),
                m_greenChannel.at(x).at(y),
                m_blueChannel.at(x).at(y)
            );
        }
    }
    
    SDL_UpdateTexture(m_p_texture, NULL, tempPixels, m_xSize * sizeof(uint32_t));
    
    delete[] tempPixels;

    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_p_renderer, m_p_texture, &srcRect, &bounds);
}
void qbImage::initTexture() {
    uint32_t rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
	#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
	#endif
    //Delete previous texture
    if (m_p_texture != NULL) SDL_DestroyTexture(m_p_texture);
    //Create texture
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_p_texture = SDL_CreateTextureFromSurface(m_p_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

uint32_t qbImage::convertColor (const double red, const double green, const double blue) {
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN 
        uint32_t pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;   
    #else 
        uint32_t pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
    #endif
    return pixelColor;
}
int qbImage::getYSize () { return m_ySize; }
int qbImage::getXSize () { return m_xSize; }