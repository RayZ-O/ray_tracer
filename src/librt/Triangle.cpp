//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
//
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"
// contructor
Triangle::Triangle(void)
        : Surface()
{

}

Triangle::Triangle(STVector3 A, STVector3 B, STVector3 C, RGBR_f color)
        : m_a(A), m_b(B), m_c(C)
{
    m_color = color;
}


// clean up
Triangle::~Triangle()
{

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    bool bFoundSolution = false;
    // TO DO: Proj2 raytracer
    // CAP5705 - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------
    LinearSolver L;
    STVector3 origin = ray.Origin();
    STVector3 direction = ray.Direction();
    STVector3 distance_AtoB = A - B;
    STVector3 distance_AtoC = A - C;
    STVector3 distance_origintoA = origin - A;
    bFoundSolution = L.Run(distance_AtoB.x, distance_AtoC.x, direction.x, distance_origintoA.x,
                           distance_AtoB.y, distance_AtoC.y, direction.y, distance_origintoA.y,
                           distance_AtoB.z, distance_AtoC.z, direction.z, distance_origintoA.z,
                           u, v, w);
    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection &intersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    STVector3 origin = ray.Origin();
    STVector3 direction = ray.Direction();
    double u = 0.0;
    double v = 0.0;
    double w = 0.0;
    if (IntersectionSolver(ray, m_a, m_b, m_c, u, v, w))
    {
        // std::cout << u << " " << v << " " << w << std::endl;
        // if (v < EPSILON || v > 1)
        // {
        //     return bFound;
        // }
        // if (u < EPSILON || u > 1 - v)
        // {
        //     return bFound;
        // }
        // if (w < EPSILON)
        // {
        //     return bFound;
        // }
        // std::cout << u << " " << v << " " << w << std::endl;
        bFound = true;
        STVector3 point = origin + w * direction;
        STVector3 normal = STVector3::Cross(m_a - m_b, m_a - m_c);
        intersection.normal = normal;
        intersection.point = point;
        intersection.distanceSqu = STVector3::Dot(point - origin, point - origin);
        intersection.surface = this;
        m_intersections.push_back(intersection);
    }

    return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal;

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------

    //---------------------------------------------------
    STVector3 distance_AtoB = m_a - m_b;
    STVector3 distance_Atoc = m_a - m_c;
    normal = normal.Cross(distance_AtoB, distance_Atoc);
    return(normal);
}


// TO DO: Proj2 raytracer
// CAP5705 - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
//
//---------------------------------------------------------
//---------------------------------------------------------
