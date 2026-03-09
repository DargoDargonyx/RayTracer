#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/v3.h"
#include "tools/ray.h"
#include "tools/hit.h"

typedef struct Material Material;

struct Material {
    int (*scatter)(
        Material* self,
        Ray inRay,
        HitRecord* rec,
        V3* attenuation,
        Ray* scattered
    );
};


#endif
