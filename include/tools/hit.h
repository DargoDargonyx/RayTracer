#ifndef HIT_H
#define HIT_H

#include "math/v3.h"
#include "tools/ray.h"
#include "tools/hit.h"

typedef struct {
    V3 point;
    V3 normal;
    float t;
    V3 color;
} HitRecord;

#endif
