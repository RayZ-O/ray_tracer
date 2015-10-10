//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"
//#include "ray.h"

// constructor
Sphere::Sphere(void)
    : m_radius(0.5)

{
      m_center = STVector3(0,0,0);
}


// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    // 2. Store the results of the intersection 
    // 3. if found and return true, otherwise, return false
    // NOTE: The IntersectionPoint pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

   //------------------------------------------------------

    STVector3 origin = ray.Origin();
    STVector3 direction = ray.Direction();
    //ori.x＊（direc.x-m_center.x)+ori.y＊（direc.y-m_center.y)+ori.z＊（direc.z-m_center.z);
    STVector3 result;
    STVector3 Distance_EtoC = origin - m_center;
    double t1;
    double distance1;
    STVector3 point1;
    STVector3 normal1;
    float delta = result.Dot(direction, Distance_EtoC) * result.Dot(direction, Distance_EtoC) - result.Dot(direction, direction) * (result.Dot(Distance_EtoC, Distance_EtoC) - m_radius * m_radius);
    if (delta < 0)
        return (bFound);
    else
        if ( delta == 0)
        {
            t1 = result.Dot(-direction, Distance_EtoC) / result.Dot(direction,direction);
            point1 = origin + t1 * direction;
            normal1 = (point1 - m_center) / m_radius;
            distance1 = result.Dot(point1 - origin, point1 - origin);
            //distance = t * t * result.Dot(direction, direction);
            pIntersection -> point = point1;
            pIntersection -> normal = normal1;
            pIntersection -> distanceSqu = distance1;
            bFound = true;
        }
        else
        {
            t1 = result.Dot(-direction, Distance_EtoC) / result.Dot(direction,direction) - sqrt(delta);
         //  t2 = result.Dot(-direction, Distance_EtoC) / result.Dot(direction,direction) + sqrt(delta);
            point1 = origin + t1 * direction;
         // point2 = origin + t2 * direction;
            normal1 = (point1 - m_center) / m_radius;
         // normal2 = (point2 - m_center) / m_radius;
            distance1 = result.Dot(point1 - origin, point1 - origin);
         // distance1 = result.Dot(point1 - origin, point1 - origin);
            pIntersection -> point = point1;
            pIntersection -> normal = normal1;
            pIntersection -> distanceSqu = distance1;
            pIntersection -> surface = this;
            bFound = true;
        }


   return(bFound);
}

