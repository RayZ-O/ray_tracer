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

Sphere::Sphere(float radius, STVector3 center, RGBR_f color)
    : m_radius(radius)
{
    m_center = center;
    m_color = color;
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
bool Sphere::FindIntersection(Ray ray, Intersection &intersection)
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
    STVector3 Distance_EtoC = origin - m_center;
    double t1;
    double distance1;
    STVector3 point1;
    STVector3 normal1;
    float delta = STVector3::Dot(direction, Distance_EtoC) * STVector3::Dot(direction, Distance_EtoC) -
                  STVector3::Dot(direction, direction) * (STVector3::Dot(Distance_EtoC, Distance_EtoC) - m_radius * m_radius);
    if (delta < 0)
        return (bFound);
    else
    {
        if (delta < EPSILON)
        {
            t1 = STVector3::Dot(-direction, Distance_EtoC) / STVector3::Dot(direction,direction);
            point1 = origin + t1 * direction;
            normal1 = (point1 - m_center) / m_radius;
            distance1 = STVector3::Dot(point1 - origin, point1 - origin);
            //distance = t * t * STVector3::Dot(direction, direction);
            intersection.point = point1;
            intersection.normal = normal1;
            intersection.distanceSqu = distance1;
            intersection.surface = this;
            bFound = true;
        }
        else
        {
            t1 = (STVector3::Dot(-direction, Distance_EtoC) - sqrt(delta)) / STVector3::Dot(direction,direction) ;
         //  t2 = STVector3::Dot(-direction, Distance_EtoC) / STVector3::Dot(direction,direction) + sqrt(delta);
            point1 = origin + t1 * direction;
         // point2 = origin + t2 * direction;
            normal1 = (point1 - m_center) / m_radius;
         // normal2 = (point2 - m_center) / m_radius;
            distance1 = STVector3::Dot(point1 - origin, point1 - origin);
         // distance1 = STVector3::Dot(point1 - origin, point1 - origin);
            intersection.point = point1;
            intersection.normal = normal1;
            intersection.distanceSqu = distance1;
            intersection.surface = this;
            bFound = true;
        }
        m_intersections.push_back(intersection);
    }
   return(bFound);
}

