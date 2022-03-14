#include "qbImage.hpp"

double getMaxValue(double a, double b, double c);

qbImage::qbImage()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;
    m_pRenderer = NULL;
}

// gracefully clear the data from site.
qbImage::~qbImage()
{
    // prevent premature shutdown.
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);
}

void qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
    // resize the images array
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    // store the dimensions
    m_xSize = xSize;
    m_ySize = ySize;

    // initialize the renderer
    m_pRenderer = pRenderer;

    // Initialize the texture.
    InitTexture();
}

int qbImage::GetXSize()
{
    return m_xSize;
}
int qbImage::GetYSize()
{
    return m_ySize;
}

void qbImage::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

void qbImage::Display()
{
    // first compute the max values for the colors
    ComputeMaxValues();
    // memory allocation for a pixel
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];
    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));
    for (int x = 0; x < m_xSize; ++x)
    {
        for (int y = 0; y < m_ySize; ++y)
        {
            tempPixels[(y * m_xSize) + x] =
                ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }
    }
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));
    // delete the pixel buffer.
    delete[] tempPixels;

    // render texture to the renderer.
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

// function to initialize the image.
void qbImage::InitTexture()
{
    Uint32 rmask, gmask, bmask, amask;

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
    // delete previously created textures.
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);
    // create surface that will hold the image.
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);

    // free surface
    SDL_FreeSurface(tempSurface);
}

Uint32 qbImage::ConvertColor(const double red, const double green, const double blue)
{
    // Convert the colours to unsigned to Uint32

    unsigned char r = static_cast<unsigned char>(convertColorValues(red));
    unsigned char g = static_cast<unsigned char>(convertColorValues(green));
    unsigned char b = static_cast<unsigned char>(convertColorValues(blue));
    Uint32 pixelColor;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
    pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif
    return pixelColor;
}

double qbImage::convertColorValues(double color)
{
    return ((color) / overallMax * 255.0);
}

// function to compute the max values for the 3 color and the overall max.
void qbImage::ComputeMaxValues()
{
    maxRed = 0.0;
    maxGreen = 0.0;
    maxBlue = 0.0;
    overallMax = 0.0;
    for (int x = 0; x < m_xSize; ++x)
        for (int y = 0; y < m_ySize; ++y)
        {
            double red = m_rChannel.at(x).at(y);
            double green = m_gChannel.at(x).at(y);
            double blue = m_bChannel.at(x).at(y);

            if (red > maxRed)
                maxRed = red;
            if (green > maxGreen)
                maxGreen = green;
            if (blue > maxBlue)
                maxBlue = blue;
            overallMax = getMaxValue(maxRed, maxBlue, maxBlue);
        }
}

double getMaxValue(double a, double b, double c)
{
    if (a >= b && a >= c)
        return a;
    if (b >= a && b >= c)
        return b;
    if (c >= a && c >= b)
        return c;
}