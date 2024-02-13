#include "shapes/cylinder.h"
#include "shapes/badminton.h"
#include "shapes/sphere.h"
#include "shapes/cone.h"
#include "sampling.h"
#include "paramset.h"
#include "efloat.h"
#include "stats.h"
#include <iostream> // for print

namespace pbrt {
            

Bounds3f Badminton::ObjectBound() const {
    Point3f pmin, pmax;
    pmin.x = -radiusRacquet * radiusRatio;
    pmax.x = radiusRacquet * (radiusRatio + handleRatio);
    pmin.y = -radiusRacquet;
    pmax.y = radiusRacquet;
    pmin.z = std::min(-radiusRacquet * 0.05f, -radiusRacquet * 0.05f + distance);
    pmax.z = std::max(radiusRacquet * 0.05f, radiusRacquet * 0.05f + distance + radiusRacquet * 0.871f);

    return Bounds3f(pmin, pmax);
}


bool Badminton::Intersect(const Ray &r, Float *tHit, SurfaceInteraction *isect,
                       bool testAlphaTexture) const {
    ProfilePhase p(Prof::ShapeIntersect);
    
    // get intersections information from two spheres
    SurfaceInteraction isect1, isect2, isect3;
    Float tHit1, tHit2, tHit3;
    bool hit1 = racquet.Intersect(r, &tHit1, &isect1, testAlphaTexture);
    bool hit2 = handle.Intersect(r, &tHit2, &isect2, testAlphaTexture);
    bool hit3 = shuttlecock.Intersect(r, &tHit3, &isect3, testAlphaTexture);
    int condition;

    condition = hit1 + (hit2 << 1) + (hit3 << 2);
    
    switch (condition)  {
        case 0:
            return false;
            break;

        case 1:
            *isect = isect1;
            *tHit = tHit1;
            return true;
            break;

        case 2:
            *isect = isect2;
            *tHit = tHit2;
            return true;
            break;

        case 3:
            if (tHit2 < tHit1){
                *isect = isect2;
                *tHit = tHit2;
            } else {
                *isect = isect1;
                *tHit = tHit1;
            }
            return true;
            break;

        case 4:
            *isect = isect3;
            *tHit = tHit3;
            return true;
            break;

        case 5:
            if (tHit3 < tHit1){
                *isect = isect3;
                *tHit = tHit3;
            } else {
                *isect = isect1;
                *tHit = tHit1;
            }
            return true;
            break;

        case 6:
            if (tHit3 < tHit2){
                *isect = isect3;
                *tHit = tHit3;
            } else {
                *isect = isect2;
                *tHit = tHit2;
            }
            return true;
            break;

        case 7:
            if (tHit3 <= tHit2 && tHit3 <= tHit1){
                *isect = isect3;
                *tHit = tHit3;
            } else if (tHit2 <= tHit3 && tHit2 <= tHit1){
                *isect = isect2;
                *tHit = tHit2;
            } else {
                *isect = isect1;
                *tHit = tHit1;
            }
            return true;
            break;

        default:
            return false;
    }
}


bool Badminton::IntersectP(const Ray &r, bool testAlphaTexture) const {
    ProfilePhase p(Prof::ShapeIntersectP);
    
    if ( racquet.IntersectP(r, testAlphaTexture) ||
         handle.IntersectP(r, testAlphaTexture) ||
         shuttlecock.IntersectP(r, testAlphaTexture)
        ) 
        return true;
    return false;
}


Float Badminton::Area() const {
    return racquet.Area() + handle.Area() + shuttlecock.Area();
}

Interaction Badminton::Sample(const Point2f &u, Float *pdf) const {
    LOG(FATAL) << "Badminton::Sample not implemented.";
    return Interaction();
}


std::shared_ptr<Shape> CreateBadmintonShape(const Transform *o2w,
                                         const Transform *w2o,
                                         bool reverseOrientation,
                                         const ParamSet &params) {
    Float radiusRacquet = params.FindOneFloat("radiusRacquet", 1.f);
    Float orientationShuttlecock = params.FindOneFloat("orientationShuttlecock", 10.f);
    Float distance = params.FindOneFloat("distance", .5f);
    return std::make_shared<Badminton>(o2w, w2o, reverseOrientation, 
                        radiusRacquet, orientationShuttlecock, distance);
}

}  // namespace pbrt
