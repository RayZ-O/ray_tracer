//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _SURFACE_H
#define _SURFACE_H

#include <algorithm>
#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"



class Surface
{

    public:
                                    Surface                             (void);
                                    ~Surface                            (void);

    virtual bool                    FindIntersection                    (Ray ray, Intersection &intersection){ return(false);}
    int                             FindClosestIntersection             (Intersection &intersection);
    RGBR_f                          GetColor                            ();

protected:



    // TO DO: Proj2 raytracer
    // CAP5705 - Note: You have to manage your intersection list
    // 1. Know when to clear and add items to your list
    //------------------------------------------------
    //------------------------------------------------
    IntersectionList                m_intersections;

    STVector3                       m_center;

    RGBR_f                          m_color;


};

#endif //_SURFACE_H



