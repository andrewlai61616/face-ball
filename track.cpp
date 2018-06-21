#ifndef OPENCV_HPP
#include <opencv2/opencv.hpp>
using namespace cv;
#define OPENCV_HPP
#endif

#include <wiringSerial.h>
#include <wiringPi.h>
#include "ball_detection.hpp"
#include <iostream>
using namespace std;

#define RESIZE_WIDTH 320
#define RESIZE_HEIGHT 240

void command_arduino( CENTER_PERI ball , int usb );
int main(int argc, char** argv){
  VideoCapture cap(0);
  if(!cap.isOpened()){
    printf("Cannot open webcam! Program shutting down QQ.\n");
    return -1;
  }
  if( argc != 2 ){
  	printf("Usage: ./out <color>\n");
  	return -1;
  }
//  int usb;
  int usb = serialOpen("/dev/ttyACM0" , 115200);
  if(usb == -1){
  	printf("Error opening USB Serial! Program is shutting down...\n");
  	return -1;
  }
  printf("Finished initialize!\n");

  Mat frame;

  RNG rng(12345);
  Scalar color;
	CENTER_PERI ball;

  while(cap.read(frame)){
    resize( frame, frame, Size(RESIZE_WIDTH, RESIZE_HEIGHT) );
		ball = get_center_and_peri(frame, argv[1], RESIZE_WIDTH, RESIZE_HEIGHT);
    if(ball.peri){
	    color = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), 255 );
			circle(frame, Point(ball.x, ball.y), int(ball.peri*0.5/PI), color, 2, 8);
		}
    cout << "(x,y) = (" << ball.x << ", " << ball.y << ")\tPeri: " << ball.peri << "";

		command_arduino( ball , usb );

//    imshow( "RGB", frame );
    waitKey(1);
  }

  return 0;
}

int prev_state = -1;
void command_arduino( CENTER_PERI ball , int usb ){
	// TARGET: x = width/2 , y = height/2 , peri = 100
	int target_peri = 170;
	if(!ball.peri){
		printf("\tNothing!\n");
		if(prev_state == 0)return;
		prev_state = 0;
		serialPutchar(usb, '0');
	}else{
		if(ball.peri > target_peri*1.2){ //move backwards
			printf("\tBACK\n");
			if(prev_state == 2)return;
			prev_state = 2;
			serialPutchar(usb, '2');
		}else if(ball.peri < target_peri*0.8){ // move forwards
			printf("\tFRONT\n");
			if(prev_state == 1)return;
			prev_state = 1;
			serialPutchar(usb, '1');
		}else{
			if( ball.x > RESIZE_WIDTH/2*1.03 ){ // move left
				printf("\tRIGHT\n");
				if(prev_state == 3)return;
				prev_state = 3;
				serialPutchar(usb, '3');
			}else if(ball.x < RESIZE_WIDTH/2*0.97){ // move right
				printf("\tLEFT\n");
				if(prev_state == 4)return;
				prev_state = 4;
				serialPutchar(usb, '4');
			}else{
				printf("\tSTOP!!!\n");
				if(prev_state == 0)return;
				prev_state = 0;
				serialPutchar(usb, '0');
			}
		}
	}
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
}
