#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>

#include "math/v3.h"
#include "tools/ray.h"
#include "tools/hit.h"

typedef struct {
    Surface base;
    V3 cen;
    float rad;
    V3 color;
} Sphere;


static inline void setSphereHitNormal(HitRecord* rec, Ray r, V3 outwardNormal){
    if(v3Dot(r.dir, outwardNormal) < 0)
        rec->normal = outwardNormal;
    else
        rec->normal = v3Scale(outwardNormal, -1.0f);
}

static inline int hitSphere(Surface* self, Ray r, float tMin, float tMax, HitRecord* rec) {
    Sphere* sphere = (Sphere*)self;

    // Quadratic formula
    V3 oc = v3Sub(r.o, sphere->cen);
    float a = v3Dot(r.dir, r.dir);
    float half_b = v3Dot(oc, r.dir);
    float c = v3Dot(oc, oc) - (sphere->rad * sphere->rad);
    float discrim = (half_b * half_b) - (a * c);

    if (discrim < 0) return 0;
    float sqrtd = sqrtf(discrim);

    float root = (-half_b - sqrtd) / a;
    if (root < tMin || root > tMax) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || root > tMax) return 0;
    }

    rec->t = root;
    rec->point = rayAt(r, rec->t);
    V3 outwardNormal = v3Sub(rec->point, sphere->cen);
    outwardNormal = v3Scale(outwardNormal, 1.0f / sphere->rad);
    setSphereHitNormal(rec, r, outwardNormal);
    rec->color = sphere->color;
    return 1;
}

static inline Sphere createSphere(V3 center, float radius, V3 color) {
    Sphere s;
    s.base.hit = hitSphere;
    s.cen = center;
    s.rad = radius;
    s.color = color;
    return s;
}

#endif
