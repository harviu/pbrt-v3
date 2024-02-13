#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_SHAPES_BADMINTON_H
#define PBRT_SHAPES_BADMINTON_H

#include "shape.h"
#include "cylinder.h"
#include "sphere.h"
#include "cone.h"
#include "../core/transform.h"

namespace pbrt {

// SnowMan Declarations
class Badminton : public Shape {
  public:
    // SnowMan Public Methods
    Badminton(const Transform *ObjectToWorld, const Transform *WorldToObject,
              bool reverseOrientation, Float radiusRacquet,
              Float orientationShuttlecock, Float distance)
        : Shape(ObjectToWorld, WorldToObject, reverseOrientation),
          radiusRacquet(radiusRacquet),
          radiusRatio(1.22f),
          handleRatio(3.48f),
          shuttlecockRatioLength(0.826f),
          shuttlecockRatioRadius(0.274f),
          orientationShuttlecock(orientationShuttlecock),
          distance(distance),
          o2wRacquet((*ObjectToWorld) * Scale(radiusRatio, 1, 1)),
          w2oRacquet(Inverse(Scale(radiusRatio, 1, 1)) * (*WorldToObject)),
          racquet(&o2wRacquet, &w2oRacquet, false, radiusRacquet,
                  -radiusRacquet * 0.05, radiusRacquet * 0.05, 360.f),
          o2wHandle((*ObjectToWorld) * RotateY(90.0f) * Translate(Vector3f(0.,0.,radiusRatio*radiusRacquet))),
          w2oHandle(Inverse(RotateY(90.0f) * Translate(Vector3f(0.,0.,radiusRatio*radiusRacquet))) * (*WorldToObject)),
          handle(&o2wHandle, &w2oHandle, false, radiusRacquet * 0.05, 0, handleRatio * radiusRacquet, 360.f),
          o2wShuttlecock((*ObjectToWorld) * Translate(Vector3f(0.,0.,radiusRacquet * shuttlecockRatioLength + distance)) * RotateY(180.0f + orientationShuttlecock) ),
          w2oShuttlecock(Inverse(Translate(Vector3f(0.,0.,radiusRacquet * shuttlecockRatioLength + distance)) * RotateY(180.0f + orientationShuttlecock))  * (*WorldToObject)),
          shuttlecock(&o2wShuttlecock, &w2oShuttlecock, false, radiusRacquet * shuttlecockRatioLength, radiusRacquet * shuttlecockRatioRadius, 360.f){}

    Bounds3f ObjectBound() const;
    bool Intersect(const Ray &ray, Float *tHit, SurfaceInteraction *isect,
                   bool testAlphaTexture) const;
    bool IntersectP(const Ray &ray, bool testAlphaTexture) const;
    Interaction Sample(const Point2f &u, Float *pdf) const;
    Float Area() const;
    
  private:
    // SnowMan Private Data
    const Float radiusRacquet;
    const Float radiusRatio;
    const Float handleRatio;
    const Float shuttlecockRatioLength;
    const Float shuttlecockRatioRadius;
    const Float orientationShuttlecock;
    const Float distance;

    const Transform o2wRacquet, o2wHandle, o2wShuttlecock;
    const Transform w2oRacquet, w2oHandle, w2oShuttlecock;
    Cone shuttlecock;
    Sphere racquet;
    Cylinder handle;
};


std::shared_ptr<Shape> CreateBadmintonShape(const Transform *o2w,
                                         const Transform *w2o,
                                         bool reverseOrientation,
                                         const ParamSet &params);

}  // namespace pbrt

#endif  // PBRT_SHAPES_BADMINTON_H
