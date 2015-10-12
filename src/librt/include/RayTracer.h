//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------



#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__


#include<string>
#include "defs.h"
#include "Scene.h"
#include "RGBR_f.h"

#define MULTIPLE_INTERSECTION 1

class Shader;

class RayTracer
{

public:
                                RayTracer                                       (void);
                                ~RayTracer                                      (void);

    void                        Run                                             (Scene *pScene, std::string fName, RenderMode mode);



private:

    Shader                      *pShader;

    int                         m_maxLevel;
    float                       m_intensityThreshold;

    bool                        MinimumColor                                    (RGBR_f color);

    RGBR_f                      Shade                                           (Ray ray, Scene *pScene, Intersection &intersection, int depth);

    STColor4ub                  ColorToPixel                                    (RGBR_f color);

};


#endif //__RAYTRACER_H__

