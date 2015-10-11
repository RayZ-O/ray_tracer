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
RGBR_f Shader::Run(Camera *camera, Intersection *pIntersection, STVector3 *lightDirection)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
            color = Phong(camera, pIntersection, lightDirection);
            break;
        default:
            color = Lambertian(pIntersection, lightDirection);
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
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection)
{
    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color(0.5f, 0.5f, 0.0f, 0.7f);

    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
    //    normal and light direction
    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------
    STVector3 normal = pIntersection->normal;
    normal.Normalize();
    STVector3 directionOfLight = *lightDirection;
    directionOfLight.Normalize();
    double Kd = 0.3;
    double factor = Kd * STVector3::Dot(normal, directionOfLight);
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Camera *camera, Intersection *pIntersection, STVector3 *lightDirection)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color(0.5f, 0.5f, 0.0f, 0.7f);

    // TO DO: Proj2 raytracer
    // CAP5705 - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------
    STVector3 normal = pIntersection->normal;
    normal.Normalize();
    STVector3 directionOfLight = *lightDirection;
    directionOfLight.Normalize();
    double Kd = 0.3;
    double diffuse = Kd * STVector3::Dot(normal, directionOfLight);

    STVector3 directionOfView = camera->Position() - pIntersection->point; //Eye direction
    directionOfView.Normalize();
    STVector3 directionOfReflect = (STVector3::Dot(normal,(STVector3::Dot(normal, directionOfLight))) * 2.0f)
                                 - directionOfLight;                   //calculate reflect
    directionOfReflect.Normalize();

    double Ks = 0.7;
    double specular= Ks * pow(STVector3::Dot(directionOfView, directionOfReflect), 10);

    color.r *= diffuse * specular;
    color.g *= diffuse * specular;
    color.b *= diffuse * specular;

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

