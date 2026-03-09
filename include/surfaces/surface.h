#ifndef SURFACE_H
#define SURFACE_H

#include "tools/ray.h"
#include "tools/hit.h"

typedef struct Surface Surface;
struct Surface {
    int (*hit)(
        Surface* self,
        Ray ray,
        float tMin,
        float tMax,
        HitRecord* rec
    );
};

#endif
