//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"


RayTracer::RayTracer(void)
    : m_maxLevel            (20),
     m_intensityThreshold   (0.001)
{
    pShader = new Shader();
}


RayTracer::~RayTracer()
{

}


//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------
void RayTracer::Run(Scene *pScene, std::string fName, RenderMode mode)
{
    // begin
    std::cout << "Running... " << std::endl;

    // the color redult from shading
    RGBR_f color;

    // set the shader's render mode
    pShader->SetMode(mode);


    int width = 320;
    int height = 400;
    RGBR_f bkground = pScene->GetBackgroundColor();
    STImage *pImg = new STImage(width, height, STImage::Pixel(bkground.r*255, bkground.g*255, bkground.b*255, bkground.a*255));

    // TO DO: Proj2 raytracer
    // CAP5705 - Implement the ray tracing algorithm.
    // 1. Cast a ray from the camera into the scene
    // 2. For every object in the scene compute intersections
    // 3. Compute shading for the closest intersections
    //       - no interection means shade to the background color
    //       - one intersection - great compute shading
    //       - otherwise implement any special handling resolve
    //         ambiguities (determine the best choice or throw an exception)
    // 4. Save the output image
    // NOTE: STImage stores colors in pixels in the range 0-255
    // If you compute color channels in a range 0-1 you must convert
    //------------------------------------------------
    STVector3 cameraPosition = pScene->GetCamera()->Position();
    Ray ray;
    ray.SetOrigin(cameraPosition);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Intersection intersection;
            ray.SetDirection(STVector3(i - width / 2, j - height / 2, -200) - cameraPosition);
            int numberOfIntersections = pScene->FindClosestIntersection(ray, intersection);
            // more than one intersection, throw an exception
            if (numberOfIntersections > 1)
            {
                throw MULTIPLE_INTERSECTION;
            }
            // one intersection - compute shading
            else if (numberOfIntersections == 1)
            {
                color = Shade(ray, pScene, intersection, 0);
                // if (!MinimumColor(color)) {
                    // color = bkground;
                // }
                pImg->SetPixel(i, j, ColorToPixel(color));
            }
            // no interection - shade to the background color
            else
            {
                pImg->SetPixel(i, j, ColorToPixel(bkground));
            }
        }
    }


    ///-----------------------------------------------


    // end
    std::cout << "DONE... " << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}

STColor4ub RayTracer::ColorToPixel(RGBR_f color) {
    return STColor4ub(floatToUchar(color.r),
                 floatToUchar(color.g),
                 floatToUchar(color.b),
                 floatToUchar(color.a)
                );
}

// This function computes all of the shading
// Recursively bounce the ray from object to object
// Use the Shader class to compute the final shading
RGBR_f RayTracer::Shade(Ray ray, Scene *pScene, Intersection &intersection, int depth)
{
    RGBR_f color;

    // TO DO: Proj2 raytracer
    // CAP5705 - Calculate the shading.
    // 1. Bounce the ray from object to object
    // 2. Compute the shading using the functions in the
    //    Shader class, attributes in pIntersection, and information
    //    about your scene
    // 3. Remember to stop the recursion
    //------------------------------------------------
    // std::cout << intersection.point.x << " " << intersection.point.y << " " << intersection.point.z << std::endl;
    STVector3 normal = intersection.normal;
    STVector3 directionOfReflect = (STVector3::Dot(normal,(STVector3::Dot(normal, -ray.Direction()))) * 2.0f) +
                                    ray.Direction();
    STVector3 directionOfLight = pScene->GetLightDirection(intersection);

    color = pShader->Run(pScene->GetCamera(), intersection, directionOfLight);

    if (depth < m_maxLevel)
    {
        Intersection ins;
        Ray reflectRay;
        reflectRay.SetOrigin(intersection.point + directionOfReflect);
        reflectRay.SetDirection(directionOfReflect);
        int numberOfIntersections = pScene->FindClosestIntersection(reflectRay, ins);
        if (numberOfIntersections == 1)
        {
            RGBR_f reColor = Shade(reflectRay, pScene, ins, depth + 1);
            float d = 0.1f;
            float new_r = std::min(1.0f, d * reColor.r + color.r);
            float new_g = std::min(1.0f, d * reColor.g + color.g);
            float new_b = std::min(1.0f, d * reColor.b + color.b);
            color = RGBR_f(new_r, new_g, new_b, color.a);
        }
    }
    //-----------------------------------------------

    return(color);
}


//------------------------------------------------------
// Always render with a minimum color so that the scene
// is not black
//------------------------------------------------------
bool RayTracer::MinimumColor(RGBR_f color)
{
    if((color.r  >= m_intensityThreshold) ||
       (color.g >= m_intensityThreshold) ||
       (color.b >= m_intensityThreshold)) {
        return(true);
    }


    return(false);
}

