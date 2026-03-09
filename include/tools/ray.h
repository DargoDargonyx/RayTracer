#ifndef RAY_H
#define RAY_H

#include "math/v3.h"

typedef struct {
    V3 o;
    V3 dir;
} Ray;


static inline V3 rayAt(Ray r, float t) {
    return v3Add(r.o, v3Scale(r.dir, t));
}

#endif
