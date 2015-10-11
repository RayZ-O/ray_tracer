//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>



Surface::Surface(void)
{

}


Surface::~Surface()
{

}


// Returns the closest intersection point
int Surface::FindClosestIntersection(Intersection *pIntersection)
{
    // TO DO: Proj2 raytracer
    // CAP5705 - Find the closest intersection.
    // 1. Return the closest intersection in m_intersections
    //    0 returned for no intersection; otherwise the number
    //    of close intersections within a small threshold
    //    and the pIntersection is updated with the closest intersection
    //------------------------------------------------
    //------------------------------------------------

    if (m_intersections.empty()) {
        return 0;
    } else {
        pIntersection = &m_intersections[0];
        double min = m_intersections[0].distanceSqu;
        int closeNumber = 0;
        for (auto ins : m_intersections) {
            if (ins.distanceSqu < min) {
                pIntersection = &ins;
            }
            if (abs(ins.distanceSqu - min) < EPSILON) {
                closeNumber++;
            }
        }
        return closeNumber;  // TO DO number of close intersection
    }
}

