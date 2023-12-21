#include <stdio.h>
#include <gd.h>
#include <math.h>

void draw_roc_flag(gdImagePtr img);
void draw_white_sun(gdImagePtr img, int x, int y, int size, int color);

// Function to calculate the intersection point of a line with a circle
void calculate_intersection(int x1, int y1, int x2, int y2, int cx, int cy, int r);

int main() {
    int width = 1200;
    int height = (int)(width * 2.0 / 3.0);

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
    int white;  // Change to white color
    int center_x = (int)(width / 4);
    int center_y = (int)(height / 4);
    int sun_radius = (int)(width / 8);
    int white_circle_dia = sun_radius;
    int blue_circle_dia = white_circle_dia + white_circle_dia * 2 / 15;

    white = gdImageColorAllocate(img, 255, 255, 255);  // Set color to white

    gdImageFilledRectangle(img, 0, 0, width, height, white);  // Set background color to white
    gdImageFilledRectangle(img, 0, 0, (int)(width / 2.0), (int)(height / 2.0), white);
    draw_white_sun(img, center_x, center_y, sun_radius, white);
    gdImageFilledEllipse(img, center_x, center_y, blue_circle_dia, blue_circle_dia, white);  // Use white color
    gdImageFilledEllipse(img, center_x, center_y, white_circle_dia, white_circle_dia, white);

    // Connecting the second set of points with white color
    int x1 = center_x;
    int y1 = center_y - sun_radius;
    int x2 = center_x - sun_radius * tan(15 * M_PI / 180);
    int y2 = center_y;
    calculate_intersection(x1, y1, x2, y2, center_x, center_y, sun_radius);

    x1 = center_x - sun_radius * tan(15 * M_PI / 180);
    y1 = center_y;
    x2 = center_x;
    y2 = center_y + sun_radius;
    calculate_intersection(x1, y1, x2, y2, center_x, center_y, sun_radius);

    x1 = center_x;
    y1 = center_y + sun_radius;
    x2 = center_x + sun_radius * tan(15 * M_PI / 180);
    y2 = center_y;
    calculate_intersection(x1, y1, x2, y2, center_x, center_y, sun_radius);

    x1 = center_x + sun_radius * tan(15 * M_PI / 180);
    y1 = center_y;
    x2 = center_x;
    y2 = center_y - sun_radius;
    calculate_intersection(x1, y1, x2, y2, center_x, center_y, sun_radius);
}

void draw_white_sun(gdImagePtr img, int center_x, int center_y, int sun_radius, int color) {
    float deg = M_PI / 180;
    float sr = sun_radius / tan(75 * deg);
    int ax, ay, bx, by, dx, dy, ex, ey;
    gdPoint points[4];

    ax = center_x;
    ay = center_y - sun_radius;
    bx = center_x - sun_radius * tan(15 * deg);
    by = center_y;
    ex = center_x;
    ey = center_y + sun_radius;
    dx = center_x + sun_radius * tan(15 * deg);
    dy = center_y;

    for (int i = 1; i <= 6; i++) {
        points[0].x = ax + sun_radius * sin(30 * deg * i);
        points[0].y = ay + sun_radius - sun_radius * cos(30 * deg * i);
        points[1].x = bx + sr - sr * cos(30 * deg * i);
        points[1].y = by - sr * sin(30 * deg * i);
        points[2].x = ex - sun_radius * sin(30 * deg * i);
        points[2].y = ey - (sun_radius - sun_radius * cos(30 * deg * i));
        points[3].x = dx - (sr - sr * cos(30 * deg * i));
        points[3].y = dy + sr * sin(30 * deg * i);

        gdImageFilledPolygon(img, points, 4, color);
        gdImagePolygon(img, points, 4, color);
    }
}

void calculate_intersection(int x1, int y1, int x2, int y2, int cx, int cy, int r) {
    // Line equation: y = mx + b
    float m = (float)(y2 - y1) / (float)(x2 - x1);
    float b = y1 - m * x1;

    // Circle equation: (x - cx)^2 + (y - cy)^2 = r^2
    // Substitute y in the circle equation: (x - cx)^2 + (mx + b - cy)^2 = r^2
    // Simplify and solve for x
    float A = 1 + m * m;
    float B = 2 * (m * (b - cy) - cx);
    float C = cx * cx + (b - cy) * (b - cy) - r * r;

    // Use quadratic formula to find x values
    float discriminant = B * B - 4 * A * C;
    if (discriminant >= 0) {
        float x1_intersection = (-B + sqrt(discriminant)) / (2 * A);
        float x2_intersection = (-B - sqrt(discriminant)) / (2 * A);

        // Calculate corresponding y values
        float y1_intersection = m * x1_intersection + b;
        float y2_intersection = m * x2_intersection + b;
    }}    
    