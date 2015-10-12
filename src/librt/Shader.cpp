//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"



Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Camera *camera, Intersection &intersection, STVector3 &lightDirection)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(intersection, lightDirection);
            break;
        case PHONG:
            color = Phong(camera, intersection, lightDirection);
            break;
        default:
            color = Lambertian(intersection, lightDirection);
            break;
        }

    // TO DO: Proj2 raytracer
    // CAP5705 - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection &intersection, STVector3 &lightDirection)
{

    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
    //    normal and light direction
    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------
    STVector3 normal = intersection.normal;
    normal.Normalize();
    lightDirection.Normalize();
    float Kd = 0.7;
    float diffuse = Kd * std::max(0.0f, STVector3::Dot(normal, lightDirection));
    Surface *intersectSurface = intersection.surface;
    assert(intersectSurface);

    color = RGBR_f(intersectSurface->GetColor().r * diffuse,
                   intersectSurface->GetColor().g * diffuse,
                   intersectSurface->GetColor().b * diffuse,
                   intersectSurface->GetColor().a);
    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Camera *camera, Intersection &intersection, STVector3 &lightDirection)
{

    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------

    STVector3 normal = intersection.normal;
    normal.Normalize();
    lightDirection.Normalize();

    float Ka = 0.15;

    float Kd = 0.7;
    float diffuse = std::max(0.0f, STVector3::Dot(normal, lightDirection));

    STVector3 directionOfView = camera->Position() - intersection.point; //Eye direction
    directionOfView.Normalize();
    STVector3 halfVector = directionOfView + lightDirection;
    halfVector.Normalize();

    float Ks = 1.0;
    // if (STVector3::Dot(directionOfView, directionOfReflect) > 0)
    float specular= powf(std::max(0.0f, STVector3::Dot(normal, halfVector)), 30);

    Surface *intersectSurface = intersection.surface;
    assert(intersectSurface);

    float r = intersectSurface->GetColor().r * (Ka + Kd * diffuse + Ks * specular);
    float g = intersectSurface->GetColor().g * (Ka + Kd * diffuse + Ks * specular);
    float b = intersectSurface->GetColor().b * (Ka + Kd * diffuse + Ks * specular);
    color = RGBR_f(std::min(1.0f, r),
                   std::min(1.0f, g),
                   std::min(1.0f, b),
                   intersectSurface->GetColor().a);
    return(color);
}


Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
// CAP5705 - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

