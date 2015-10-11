//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// RGBR_f.h
// Color data
//------------------------------------------------------------------------------------------------


#ifndef _RGBR_F_H
#define _RGBR_F_H



class RGBR_f {

public:

    RGBR_f(void);
    RGBR_f(float red, float green, float blue, float alpha);
    ~RGBR_f(void);
    RGBR_f operator += (const RGBR_f& rhs)
    {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }

    float r;
    float g;
    float b;
    float a;
};

#endif //_RGBRF_H
