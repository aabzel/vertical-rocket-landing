#include "draw_rocket.h"

#include "coordinate_transformation.h"
#include "graphics.h"
#include "rocket_params.h"
#include "screen.h"
#include "utils.h"

#include <math.h>

void draw_roket (float cX, float cY, float alfaRad, float len, float fjet, float fCorrect) {
    cleardevice ();
    setlinestyle (SOLID_LINE, 0, 2);
    float diameter = len / 7;
    float TopY = cY + cos (alfaRad) * len / 2;
    float TopX = cX - sin (alfaRad) * len / 2;
    float bottomX = cX + sin (alfaRad) * len / 2;
    float bottomY = cY - cos (alfaRad) * len / 2;
    float bottomFireX = cX + sin (alfaRad) * (len + diameter) / 2;
    float bottomFireY = cY - cos (alfaRad) * (len + diameter) / 2;
    float outTopX = 0;
    float outTopY = 0;
    float outBottomX = 0;
    float outBottomY = 0;
    float outbottomFireX = 0;
    float outbottomFireY = 0;
    Vector_t fJetVector = {fjet*sin(alfaRad)*MAX_FCORRECT_PIX/MAX_F_JET, -fjet*cos(alfaRad)*MAX_FCORRECT_PIX/MAX_F_JET, 0};
    Vector_t fJetEndDot = {bottomX+fJetVector.x, bottomY+fJetVector.y, 0};
    Vector_t fJetEndDotRender = { 0,0,0 };

    Vector_t fCottectVector = {-fCorrect*cos(alfaRad)*MAX_FCORRECT_PIX/ MAX_F_CORRECT,-fCorrect*sin(alfaRad)* MAX_FCORRECT_PIX / MAX_F_CORRECT,0};
    Vector_t fCottectEndDot = { TopX+ fCottectVector.x,TopY+ fCottectVector.y,0 };
    Vector_t fCottectEndDotRender = { 0,0,0 };

    convert_coordinates (TopX, TopY, WIDTH, HEIGHT, &outTopX, &outTopY);
    convert_coordinates (bottomX, bottomY, WIDTH, HEIGHT, &outBottomX, &outBottomY);
    setcolor(WHITE);
    setlinestyle (SOLID_LINE, 0, 2);
    line (outBottomX, outBottomY, outBottomX, outBottomY);
    convert_coordinates (fCottectEndDot.x, fCottectEndDot.y, WIDTH, HEIGHT, &fCottectEndDotRender.x, &fCottectEndDotRender.y);
    convert_coordinates (fJetEndDot.x, fJetEndDot.y, WIDTH, HEIGHT, &fJetEndDotRender.x, &fJetEndDotRender.y);

    convert_coordinates (bottomFireX, bottomFireY, WIDTH, HEIGHT, &outbottomFireX, &outbottomFireY);
    //setcolor(RED);
    //setlinestyle(SOLID_LINE, 0, 1);
    line (outTopX, outTopY, fCottectEndDotRender.x, fCottectEndDotRender.y);
    //setcolor(RED);
    //
    //setlinestyle(SOLID_LINE, 0, 1);
    line (outTopX, outTopY, fJetEndDotRender.x, fJetEndDotRender.y);
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 2);

    if (1 < fjet) {
        setcolor (WHITE);
        setfillstyle (SOLID_FILL, YELLOW);
    } else {
    }
    circle (outbottomFireX, outbottomFireY, diameter);
    if (1 < fjet) {
        //floodfill(outbottomFireX, outbottomFireY, RED);
        floodfill (outbottomFireX, outbottomFireY, WHITE);
    } else {
    }
    //circle(outbottomFireX, outbottomFireY, diameter);
}

void draw_axis (int width, int heigh) {
    //convert_coordinates(TopX, TopY, WIDTH, HEIGHT, &outTopX, &outTopY);
    //convert_coordinates(TopX, TopY, WIDTH, HEIGHT, &outTopX, &outTopY);
    //line(0, heigh / 2, width, heigh / 2);     // vetical
    //line(width / 2, 0, width / 2, heigh);   // horisontal

    line (0, 3*heigh / 4, width, 3*heigh / 4);     // vetical
    line (width / 2, 0, width / 2, heigh);   // vetical
}

