#ifndef OPENCV_HPP
#include <opencv2/opencv.hpp>
using namespace cv;
#define OPENCV_HPP
#endif


#define MIN_CIRCLE_PERI_SCREEN_SIZE_RATIO 0.0006
#define PI 3.1415926536
#define PERI_TO_AREA(x) x*x*0.25/PI
#define PERI_RATIO 0.4

// RED -->  180-amp/2 ~ 180 AND 0 ~ amp/2
#define AMPLITUDE 9
#define GREEN_SHIFT_MIN_SAT 50
#define BLUE_SHIFT_MIN_SAT 50
#define YELLOW_SHIFT_MAX_VAL 3
#define YELLOW_SHIFT_AMP 2
#define YELLOW_SHIFT_MIN_SAT 0
#define YELLOW_SHIFT_MIN_VAL 20
#define GREEN_SHIFT_AMP 5
#define BLUE_SHIFT_AMP 12
#define MIN_SAT 70
#define MAX_SAT 253
#define MIN_VAL 50
#define BLUE_SHIFT_MIN_VAL 50
#define MAX_VAL 240
const char color_table[][7] = { "red","purple","yellow","green","blue" };
const int color_h[] = 				{     0,     155,      30,     60,   120 };

Point getCentroid( InputArray Points );
void inRangeColor(Mat* in, Mat* out ,char* argv){
	int i;
	for(i=0;i<5;i++){
		if(strcmp(argv, color_table[i]))continue;
		break;
	}
	if(i==5){
		printf("Warning! Specific color not set. Setting as GREEN.\n");
		i = 3;
	}
	if(strcmp(argv, "red")){ // not red
		inRange(*in, Scalar(color_h[i]-AMPLITUDE - (i==3?GREEN_SHIFT_AMP:0) - (i==4?BLUE_SHIFT_AMP:0) - (i==2?YELLOW_SHIFT_AMP:0),
			MIN_SAT - (i==3?GREEN_SHIFT_MIN_SAT:0) - (i==4?BLUE_SHIFT_MIN_SAT:0) - (i==2?YELLOW_SHIFT_MIN_SAT:0),
			MIN_VAL - (i==4?BLUE_SHIFT_MIN_VAL:0) - (i==2?YELLOW_SHIFT_MIN_VAL:0)),
			Scalar(color_h[i]+AMPLITUDE + (i==3?GREEN_SHIFT_AMP:0) + (i==4?BLUE_SHIFT_AMP:0) + (i==2?YELLOW_SHIFT_AMP:0),
			MAX_SAT, MAX_VAL + (i==2?YELLOW_SHIFT_MAX_VAL:0)), *out);
	}else{ // red
		Mat combine;
		inRange(*in, Scalar(180-AMPLITUDE, MIN_SAT, MIN_VAL), Scalar(180, MAX_SAT, MAX_VAL), combine);
		inRange(*in, Scalar(0, MIN_SAT, MIN_VAL), Scalar(AMPLITUDE, MAX_SAT, MAX_VAL), *out);
		*out |= combine;
	}
}

struct CENTER_PERI{
  int x,y,peri;
  CENTER_PERI(){}
  CENTER_PERI(int xi, int yi, int perii){x=xi;y=yi;peri=perii;}
};

CENTER_PERI get_center_and_peri(Mat frame, char* argv, int width, int height){
		Mat hsv_frame, cut_frame, canny_frame;
	  vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Point circle_center;
    int found_circles;
    double peri, circle_peri;
    CENTER_PERI ret(0,0,0);

    GaussianBlur(frame, hsv_frame, Size(7,7), 0, 0);
    cvtColor( hsv_frame, hsv_frame, CV_BGR2HSV );

		inRangeColor(&hsv_frame, &cut_frame, argv);
//		imshow("CUT", cut_frame);

    Canny(cut_frame, canny_frame, 50, 150, 5);
    findContours(canny_frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    found_circles = circle_peri = 0;
    circle_center = Point(0,0);

		for(int i=0;i<contours.size();i++){
      peri = arcLength(contours[i],1);
      if(peri < MIN_CIRCLE_PERI_SCREEN_SIZE_RATIO * width * height)continue;
      if(contourArea(contours[i]) < PERI_TO_AREA(peri)*PERI_RATIO)continue;
      found_circles ++ ;
      if(circle_peri < peri){
        circle_peri = peri;
        circle_center = getCentroid(contours[i]);
      }
    }
		if(!found_circles)return ret;
		ret.x = circle_center.x;
		ret.y = circle_center.y;
		ret.peri = int(circle_peri);
		return ret;
}

Point getCentroid( InputArray Points )
{
    Point Coord;
    Moments mm = moments( Points, false );
    double moment10 = mm.m10;
    double moment01 = mm.m01;
    double moment00 = mm.m00;
    Coord.x = int(moment10 / moment00);
    Coord.y = int(moment01 / moment00);
    return Coord;
}
