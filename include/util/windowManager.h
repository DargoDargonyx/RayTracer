#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL2/SDL.h>

#include "math/v3.h"
#include "surfaces/sphere.h"


int runWindow(int sWidth, int sHeight);

void renderScene(SDL_Texture* texture, V3 origin, int width,
        int height, int aaSamples, Sphere* sphere);

#endif
