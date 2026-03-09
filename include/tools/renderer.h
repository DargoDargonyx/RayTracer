#ifndef RENDERER_H
#define RENDERER_H

#include <math.h>
#include "math/v3.h"
#include "tools/ray.h"
#include "tools/scene.h"
#include "tools/hit.h"


static inline V3 skyColor(Ray r){
    V3 unit = v3Normalize(r.dir);
    float t = 0.5f * (unit.y + 1.0f);
    V3 white = {1,1,1};
    V3 blue = {0.5,0.7,1};

    return v3Add(
        v3Scale(white, 1.0f - t),
        v3Scale(blue, t)
    );
}

static inline V3 rayColor(Ray r, Scene* scene){
    HitRecord rec;
    if(hitScene(scene, r, 0.001f, 1000.0f, &rec)){
        float light = rec.normal.y * 0.5f + 0.5f;
        return v3Scale(rec.color, light);
    }
    return skyColor(r);
}

static inline void renderScene(uint32_t* buffer, int width, 
        int height, Scene* scene, Camera* cam){

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            float u = (float)x / (width-1);
            float v = (float)y / (height-1);
            Ray r = cameraRay(cam, u, v);
            V3 col = rayColor(r, scene);
            uint8_t R = (uint8_t)(255 * col.x);
            uint8_t G = (uint8_t)(255 * col.y);
            uint8_t B = (uint8_t)(255 * col.z);

            buffer[y * width + x] = 
                (255 << 24) | 
                (R << 16) | 
                (G << 8) | 
                B;
        }
    }
}

#endif
