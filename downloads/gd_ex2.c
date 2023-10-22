// https://en.wikipedia.org/wiki/Flag_of_the_Republic_of_China
// cc roc_flag.c -lgd -lm to link with gd and math library
// https://www.rapidtables.com/web/color/RGB_Color.html
// 撟曆�訫耦����𡑒𠧧���鼓��𣇉毀蝧�
// 隞乩�� gd 蝜芸�𣇉�见�誩�𡑒岫�𧞄�枂 ROC ��𧢲��, 隢𧢲覔��帋�见�㛖�见�誩�批捆摰峕�𣂼�𣬚�𣬚���𧢲�㛖鼓���
#include <stdio.h>
#include <gd.h>
#include <math.h>

void draw_roc_flag(gdImagePtr img);
void draw_white_sun(gdImagePtr img, int x, int y, int size, int color);

int main() {
    // width 3: height 2
    int width = 1200;
    int height = (int)(width*2.0 / 3.0);

    gdImagePtr img = gdImageCreateTrueColor(width, height);
    gdImageAlphaBlending(img, 0);

    draw_roc_flag(img);

    FILE *outputFile = fopen("./../images/roc_flag1.png", "wb");
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
    // Colors for the flag
    red = gdImageColorAllocate(img, 242, 0, 0); // Red color
    white = gdImageColorAllocate(img, 255, 255, 255); // White stripes
    blue = gdImageColorAllocate(img, 0, 41, 204); // Blue
    // red rectangle area
    gdImageFilledRectangle(img, 0, 0, width, height, red);
    // blue rectangle area
    gdImageFilledRectangle(img, 0, 0, (int)(width/2.0), (int)(height/2.0), blue);
    // �𤌍��滚���𧞄�枂��鍦予�蒾�𠯫��頛芸�梶凒蝺�, 隢见�𡑒岫閮��埈�����暺𧼮漣璅坔�峕�𣂼�𧢲�㛖鼓���
    draw_white_sun(img, center_x, center_y, sun_radius, white);
}

void draw_white_sun(gdImagePtr img, int center_x, int center_y, int sun_radius, int color) {
    float angle = 0;
    int fromX, fromY;
    int toX, toY;
    for (int i=0; i<24; i++){
        angle += 5*M_PI*2/12;
        //printf("%.3f", angle);
        toX = center_x + cos(angle)*sun_radius;
        toY = center_y + sin(angle)*sun_radius;
        // �蘨��� i �� 0 ��蝘餃�訫� toX, toY, �園�㗛�賡�脰�𣬚凒蝺𡁶鼓���
        if (i!=0){
            gdImageLine(img, fromX, fromY, toX, toY, color);
        }
        fromX = toX;
        fromY = toY;
   }
}