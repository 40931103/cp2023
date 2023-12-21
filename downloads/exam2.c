#include <stdio.h>
#include <gd.h>
#include <math.h>

void draw_roc_flag(gdImagePtr img);
void draw_white_sun(gdImagePtr img, int x, int y, int size, int color);

int main() {
    // width 3: height 2
    int width = 1200;
    // ???瑕祝瘥 3:2
    int height = (int)(width*2.0 / 3.0);

    gdImagePtr img = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(img, 0);

    draw_roc_flag(img);

    FILE *outputFile = fopen("roc_flag_in_gd.png", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        return 1;
    }
    gdImagePngEx(img, outputFile, 9);
    fclose(outputFile);
    gdImageDestroy(img);
    return 0;
}

void draw_roc_flag(gdImagePtr img) {
    int width = gdImageSX(img);
    int height = gdImageSY(img);
    int red, white, blue;
    int center_x = (int)(width/4);
    int center_y = (int)(height/4);
    int sun_radius = (int)(width/8);
    int white_circle_dia = sun_radius;
    int blue_circle_dia = white_circle_dia +  white_circle_dia*2/15;

    red = gdImageColorAllocate(img, 255, 0, 0); // 蝝
    white = gdImageColorAllocate(img, 255, 255, 255); // ?質
    blue = gdImageColorAllocate(img, 0, 0, 149); // ?

    gdImageFilledRectangle(img, 0, 0, width, height, red);
    gdImageFilledRectangle(img, 0, 0, (int)(width/2.0), (int)(height/2.0), blue);
    draw_white_sun(img, center_x, center_y, sun_radius, white);
    gdImageFilledEllipse(img, center_x, center_y, blue_circle_dia, blue_circle_dia, blue);
    gdImageFilledEllipse(img, center_x, center_y, white_circle_dia, white_circle_dia, white);
}

void draw_white_sun(gdImagePtr img, int center_x, int center_y, int sun_radius, int color) {
    float deg = M_PI/180;
    float sr = sun_radius/tan(75*deg);
    int bx, by, ex, ey, dx, dy;

    bx = center_x - sun_radius * tan(15 * deg);
    by = center_y;
    ex = center_x;
    ey = center_y + sun_radius;
    dx = center_x + sun_radius * tan(15 * deg);
    dy = center_y;

    // Draw lines connecting the second set of points with white color
    gdImageLine(img, bx, by, ex, ey, color); // Line BE
    gdImageLine(img, ex, ey, dx, dy, color); // Line ED
    gdImageLine(img, dx, dy, bx, by, color); // Line DB

    int ax, ay;
    printf("A coord: (%d,%d)\n", ax, ay);
    printf("B coord: (%d,%d)\n", bx, by);
    printf("E coord: (%d,%d)\n", ex, ey);
    printf("D coord: (%d,%d)\n\n", dx, dy);

    // A
    ax = center_x;
    ay = center_y - sun_radius;
    printf("A coord: (%d,%d)\n", ax, ay);
    // B
    bx = center_x - sun_radius*tan(15*deg);
    by = center_y;
    printf("B coord: (%d,%d)\n", bx, by);
    // E
    ex = center_x;
    ey = center_y + sun_radius;
    printf("E coord: (%d,%d)\n", ex, ey);
    // D
    dx = center_x + sun_radius*tan(15*deg);
    dy = center_y;
    printf("D coord: (%d,%d)\n\n", dx, dy);

    gdImageLine(img, ax, ay, bx, by, color);
    gdImageLine(img, bx, by, ex, ey, color);
    gdImageLine(img, ex, ey, dx, dy, color);
    gdImageLine(img, dx, dy, ax, ay, color);
}