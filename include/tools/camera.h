#ifndef CAMERA_H
#define CAMERA_H

#include "math/v3.h"
#include "tools/camera.h"

typedef struct {
    V3 origin;
    V3 horizontal;
    V3 vertical;
    V3 lowerLeft;
} Camera;


static inline Camera createCamera(float aspect){
    float viewportHeight = 2.0f;
    float viewportWidth = aspect * viewportHeight;
    float focalLength = 1.0f;

    Camera cam;
    cam.origin = (V3){0,0,0};
    cam.horizontal = (V3){viewportWidth, 0, 0};
    cam.vertical = (V3){0, viewportHeight, 0};
    cam.lowerLeft = (V3){
        -viewportWidth / 2,
        -viewportHeight / 2,
        -focalLength
    };

    return cam;
}

static inline Ray cameraRay(Camera* cam, float u, float v){
    V3 dir = v3Sub(
        v3Add(
            v3Add(cam->lowerLeft,
            v3Scale(cam->horizontal, u)),
            v3Scale(cam->vertical, v)
        ),
        cam->origin
    );

    return (Ray){cam->origin, dir};
}

#endif
