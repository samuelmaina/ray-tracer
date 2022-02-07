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

qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *pRender)
{
    //resize the images array
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));
}