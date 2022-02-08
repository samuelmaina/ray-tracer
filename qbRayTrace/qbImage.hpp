#ifndef QBIMAGE_H
#define QBIMAGE_H
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class qbImage
{
private:
    Uint32 ConvertColor(const double red, const double green, const double blue);
    void InitTexture();

private:
    // Arrays to store the image data
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;
    //store the dimensions of the image
    int m_xSize, m_ySize;
    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;

public:
    qbImage(/* args */);
    ~qbImage();
    //initializer
    void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderere);

    //function to set color of  pixel
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);
    int GetXSize();
    int GetYSize();
    //function that is used to display the image
    void Display();
};

#endif