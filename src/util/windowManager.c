#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "tools/renderer.h"
#include "tools/scene.h"
#include "surfaces/sphere.h"
#include "tools/camera.h"
#include "math/v3.h"


int runWindow(int sWidth, int sHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR, couldn't initialize SDL_VIDEO: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        printf("ERROR, couldn't initialize TTF: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window;
    window = SDL_CreateWindow(
        "RayTracer", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        sWidth, 
        sHeight, 
        0
    );
    if (!window) {
        printf("ERROR, couldn't initialize window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        printf("ERROR, couldn't initialize renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture;
    texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        sWidth,
        sHeight
    );
    if (!texture) {
        printf("ERROR, couldn't initialize texture: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font;
    font = TTF_OpenFont(
        "/usr/share/fonts/TTF/JetBrainsMono-Regular.ttf",
        24
    );
    if (!font) {
        printf("ERROR, couldn't load font: %s\n", TTF_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_Quit();
        return 1;
    }

    printf("Successfully started the ray tracer\n");    

    uint32_t* pixels = malloc(sizeof(uint32_t) * sWidth * sHeight);
    Scene scene = {0};
    Sphere sphere1 = createSphere(
        (V3){0, 0, -1},
        0.25f,
        (V3){0.2f, 0.2f, 1.0f}
    );

    scene.objects[scene.count++] = (Surface*)&sphere1;
    Camera camera = createCamera((float)sWidth / sHeight);
    renderScene(
        pixels,
        sWidth,
        sHeight,
        &scene,
        &camera
    );

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                running = 0;

        SDL_UpdateTexture(texture, NULL, pixels, sWidth * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
