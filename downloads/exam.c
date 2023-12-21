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
    // ?賣雿?予?Ｙ?甇?葉憭? ?迨銝剖?暺漣璅?瑕祝??1/4 ??
    int center_x = (int)(width/4);
    int center_y = (int)(height/4);
    // gdImageFilledEllipse ?隞仿撖祆?? diameter 雿?
    // ?望銝剖亢?賣?耦??敺?予撖砍漲??1/8
    // ?迨銝剖亢?賣?耦?敺?予撖砍漲??1/4, 銋停?臬??祝摨衣? 1/8
    // ???賣??????憭??耦?嗅?敺??臬??祝摨衣?1/8
    int sun_radius = (int)(width/8);
    // 銝剖亢?賣?耦?敺??澆?鈭???憭??耦??敺?
    int white_circle_dia = sun_radius;
    // 銝剖亢??耦???箔葉憭桃?亦? 1??2/15
    int blue_circle_dia = white_circle_dia +  white_circle_dia*2/15;
    // ?寞? https://www.moi.gov.tw/cp.aspx?n=10621 閮???銝車憿??
    red = gdImageColorAllocate(img, 255, 0, 0); // 蝝
    white = gdImageColorAllocate(img, 255, 255, 255); // ?質
    blue = gdImageColorAllocate(img, 0, 0, 149); // ?
    // ?寞??怠?憭批?憛?蝝?瑟敶Ｗ???
    gdImageFilledRectangle(img, 0, 0, width, height, red);
    // ?予?Ｙ??箸?Ｗ??? 1/4, 銋?∠?瑟敶Ｗ???
    gdImageFilledRectangle(img, 0, 0, (int)(width/2.0), (int)(height/2.0), blue);
    // ?身瘜誑憛怨?怠?剖?脣??敶?
    draw_white_sun(img, center_x, center_y, sun_radius, white);
    // ?拍銝???脣之???質撠??怠??啁?
    gdImageFilledEllipse(img, center_x, center_y, blue_circle_dia, blue_circle_dia, blue);
    gdImageFilledEllipse(img, center_x, center_y, white_circle_dia, white_circle_dia, white);

}

void draw_white_sun(gdImagePtr img, int center_x, int center_y, int sun_radius, int color) {
    // M_PI 憭批?摰儔??math.h 璅瑼葉, ?銝??賣銝剜?典?摨衣閫漲?桐?
    // ?迨摰儔撠?摨西??箏?摨衣?頧?霈??deg, 閫漲?潔?銝?deg 撠勗頧敺漲
    float deg = M_PI/180;
    // ?寞???????瘥?撠???摨衣 15 摨? 瘙?嗅??閫?閫耦?銝閫漲??75 摨?
    // 瘙?????葉隞颱??勗耦??small radius, 銋停?航敶Ｙ??虫?????????憭批?
    float sr = sun_radius/tan(75*deg);
    int ax, ay, bx, by, dx, dy, ex, ey;
    gdPoint points[4];
    /* ?典?銝?鈭???銝剔??桐??勗耦????? ?誑摨扳?暺蝺葫閰行?行迤蝣?
    ax = center_x;
    ay = center_y - sun_radius;
    bx = center_x - sun_radius*tan(15*deg);
    by = center_y;
    ex = center_x;
    ey = center_y + sun_radius;
    dx = center_x + sun_radius*tan(15*deg);
    dy = center_y;
    // AB
    gdImageLine(img, ax, ay, bx, by, color);
    // BE
    gdImageLine(img, bx, by, ex, ey, color);
    // ED
    gdImageLine(img, ex, ey, dx, dy, color);
    // DA
    gdImageLine(img, dx, dy, ax, ay, color);
    */
    ax = center_x;
    ay = center_y - sun_radius;
    printf("%d,%d\n",ax, ay);
    bx = center_x - sun_radius*tan(15*deg);
    by = center_y;
    ex = center_x;
    ey = center_y + sun_radius;
    dx = center_x + sun_radius*tan(15*deg);
    dy = center_y;
    // 蝣箏??桐??勗耦???憛甇?Ⅱ敺? ?拍餈游?瘥活頧? 30 摨? 蝮賢頧甈∪?臬?銝?鈭??????
    for (int i=1;i<=6;i++){
    // A
    points[0].x = ax+sun_radius*sin(30*deg*i);
    points[0].y = ay+sun_radius-sun_radius*cos(30*deg*i);
    printf("A coord: (%d,%d)\n", points[0].x, points[0].y);
    // B
    points[1].x = bx+sr-sr*cos(30*deg*i);
    points[1].y = by-sr*sin(30*deg*i);
    printf("B coord: (%d,%d)\n", points[1].x, points[1].y);
    // E
    points[2].x = ex-sun_radius*sin(30*deg*i);
    points[2].y = ey-(sun_radius-sun_radius*cos(30*deg*i));
    printf("E coord: (%d,%d)\n", points[2].x, points[2].y);
    // D
    points[3].x = dx-(sr-sr*cos(30*deg*i));
    points[3].y = dy+sr*sin(30*deg*i);
    printf("D coord: (%d,%d)\n\n", points[2].x, points[2].y);
    // 撠敶Ｗ???????
    gdImageFilledPolygon(img, points, 4, color);
    // ?刻敶Ｗ????蝺? ?Ⅱ???勗耦蝭?
    gdImagePolygon(img, points, 4, color);
    }
}