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
    // std::cout << STVector3::Dot(normal, -directionOfLight) << std::endl;
    // std::cout << intersection.point.x << " " << intersection.point.y << " " << intersection.point.z << std::endl;
    // std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
    // std::cout << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << std::endl;
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
    STVector3 directionOfLight = lightDirection;
    directionOfLight.Normalize();
    double Kd = 0.3;
    double diffuse = STVector3::Dot(normal, directionOfLight);

    STVector3 directionOfView = camera->Position() - intersection.point; //Eye direction
    directionOfView.Normalize();
    STVector3 directionOfReflect = (STVector3::Dot(normal,(STVector3::Dot(normal, directionOfLight))) * 2.0f)
                                 - directionOfLight;                   //calculate reflect
    directionOfReflect.Normalize();

    double Ks = 0.7;
    double specular= pow(STVector3::Dot(directionOfView, directionOfReflect), 10);

    Surface *intersectSurface = intersection.surface;
    assert(intersectSurface);

    color = RGBR_f(intersectSurface->GetColor().r * (Kd * diffuse + Ks * specular),
                   intersectSurface->GetColor().g * (Kd * diffuse + Ks * specular),
                   intersectSurface->GetColor().b * (Kd * diffuse + Ks * specular),
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

