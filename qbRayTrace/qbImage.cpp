#include "qbImage.hpp"

qbImage::qbImage()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;
    m_pRenderer = NULL;
}

//gracefully clear the data from site.
qbImage::~qbImage()
{
    //prevent premature shutdown.
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);
}

void qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
    //resize the images array
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    //store the dimensions
    m_xSize = xSize;
    m_ySize = ySize;

    //initialize the renderer
    m_pRenderer = pRenderer;

    //Initialize the texture.
    InitTexture();
}

void qbImage::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

void qbImage::Display()
{
    //memory allocation for a pixel
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];
    memset(temPixels, m_xSize * m_ySize * sizeof(Uint32));
    for (int x = 0; x < m_xSize; ++x)
    {
        for (int y = 0; y < count; ++y)
        {
            tempPixels[(y * m_xSize) + x] =
                ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }
    }
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));
    //delete the pixel buffer.
    delete[] tempPixels;

    //render texture to the renderer.
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds)
}