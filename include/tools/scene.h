#ifndef SCENE_H
#define SCENE_H

#include "tools/camera.h"
#include "tools/ray.h"
#include "tools/hit.h"
#include "surfaces/surface.h"

typedef struct {
    Surface* objects[256];
    int count;
    Camera* camera;
} Scene;


static inline int hitScene(Scene* scene, Ray r, float tMin, float tMax, HitRecord* rec) {
    HitRecord temp;
    int hitAnything = 0;
    float closest = tMax;

    for (int i = 0; i < scene->count; i++) {
        Surface* obj = scene->objects[i];
        if (obj->hit(obj, r, tMin, closest, &temp)) {
            hitAnything = 1;
            closest = temp.t;
            *rec = temp;
        }
    }
    return hitAnything;
}

#endif
