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
    
    int iter = 0;
    double tempDistance = 0.0;
    int numOftimes = 0;
    tempDistance = m_intersections.at(0).distanceSqu;
    for(iter = 0; iter != m_intersections.max_size(); iter++)
    {
        if (tempDistance > m_intersections.at(iter).distanceSqu)
        {
            tempDistance = m_intersections.at(iter).distanceSqu;
            numOftimes = 1;
            pIntersection -> point = m_intersections.at(iter).point;
            pIntersection -> normal = m_intersections.at(iter).normal;
           // pIntersection -> surface = m_intersections.at(iter).this;
        }
        else
            if (tempDistance == m_intersections.at(iter).distanceSqu)
            {
                numOftimes++;
            }
    }
    return numOftimes;

    return(0);
}

