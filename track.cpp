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

#define PREV_DIFF_RATIO 1.3

void stop_for_a_while(int usb);
void command_arduino( CENTER_PERI ball , int usb );
void close_claw(int usb);
void open_claw(int usb);
void wiggle(int usb);
void walk_straight_and_avoid(int usb);
int prev_state = -1, prev_peri = -1, ball_in_range = 0, closed_claw = 0;
int main(int argc, char** argv){
  VideoCapture cap(0);
  if(!cap.isOpened()){
  	printf("Cannot open webcam 0! Trying 1...\n");
  	cap.open(1);
  }
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

	cap.read(frame);
	open_claw(usb);

  while(cap.read(frame)){
    resize( frame, frame, Size(RESIZE_WIDTH, RESIZE_HEIGHT) );
		ball = get_center_and_peri(frame, argv[1], RESIZE_WIDTH, RESIZE_HEIGHT);
    if(ball.peri){
	    color = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), 255 );
			circle(frame, Point(ball.x, ball.y), int(ball.peri*0.5/PI), color, 2, 8);
			if(prev_peri == -1)prev_peri = ball.peri;
		}
    cout << "(x,y) = (" << ball.x << ", " << ball.y << ")\tPeri: " << ball.peri << "";

		if(closed_claw){
			printf("Finished task!!!\n");
			walk_straight_and_avoid(usb);
		}else{
			if(!ball_in_range){
  			if(prev_peri==-1 || (prev_peri > ball.peri/PREV_DIFF_RATIO && prev_peri < ball.peri*PREV_DIFF_RATIO)){
  				if(ball.peri)prev_peri = ball.peri;
					command_arduino( ball , usb );
					printf("Believe!\n");
   			}else{
					printf("Don't believe! prev %d now %d\n", prev_peri, ball.peri);
   				stop_for_a_while(usb);
   				if(prev_peri > 390){
   					ball_in_range = 1;
   					continue;
   				}else{
   					wiggle(usb);
   				}
   			}
			}else if(!closed_claw){
				close_claw(usb);
				closed_claw = 1;
			}
		}

    imshow( "RGB", frame );
    waitKey(1);
  }

  return 0;
}

void walk_straight_and_avoid(int usb){
	serialPutchar(usb , '3');
	prev_state = 3;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(100);
	stop_for_a_while(usb);
	delay(50);
}

void wiggle(int usb){
	serialPutchar(usb , '1');
	prev_state = 1;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(30);
	serialPutchar(usb , '3');
	prev_state = 3;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(30);
	serialPutchar(usb , '2');
	prev_state = 2;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(40);
	stop_for_a_while(usb);
}

void stop_for_a_while(int usb){
	if(prev_state == 0)return;
	serialPutchar(usb , '0');
	prev_state = 0;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
}

void close_claw(int usb){
	printf("I'm closing my claw!\n");
	serialPutchar(usb, '3');
	prev_state = 3;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(2000);
	stop_for_a_while(usb);
	serialPutchar(usb, '5');
	prev_state = 5;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(2000);
	stop_for_a_while(usb);
	/*while(1){
		serialPutchar(usb, '3');
		prev_state = 3;
		while(!serialDataAvail(usb));
		while(serialDataAvail(usb)){
			printf("%c\n",serialGetchar(usb));
		}
		delay(100);
		stop_for_a_while(usb);
		delay(50);
	}*/
}

void open_claw(int usb){
	printf("I'm opening my claw.\n");
	serialPutchar(usb, '6');
	prev_state = 6;
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	delay(1000);
	stop_for_a_while(usb);
}

void command_arduino( CENTER_PERI ball , int usb ){
	// TARGET: x = width/2 , y = height/2 , peri = 100
	int target_peri = 420;
	if(!ball.peri){
		printf("\tNothing!\n");
		if(prev_state == 0)return;
		prev_state = 0;
		serialPutchar(usb, '0');
	}else{
/*		if(ball.peri > target_peri*1.2){ //move backwards
			printf("\tBACK\n");
			if(prev_state == 4)return;
			prev_state = 4;
			serialPutchar(usb, '4');
		}else if(ball.peri < target_peri*0.8){ // move forwards
		}else{*/
			if( ball.x > RESIZE_WIDTH/2*1.1 ){ // move left
				printf("\tRIGHT\n");
				if(prev_state == 2)return;
				prev_state = 2;
				serialPutchar(usb, '2');
				delay(50);
			}else if(ball.x < RESIZE_WIDTH/2*0.9){ // move right
				printf("\tLEFT\n");
				if(prev_state == 1)return;
				prev_state = 1;
				serialPutchar(usb, '1');
				delay(50);
			}else{
				if( ball.peri < target_peri ){ // move forwards
					printf("\tFRONT\n");
					if(prev_state == 3)return;
					prev_state = 3;
					serialPutchar(usb, '3');
					delay(150);
				}else{
					ball_in_range = 1;
					printf("\tSTOP!!!\n");
					if(prev_state == 0)return;
					prev_state = 0;
					serialPutchar(usb, '0');
					delay(150);
				}
			}
//		}
	}
	while(!serialDataAvail(usb));
	while(serialDataAvail(usb)){
		printf("%c\n",serialGetchar(usb));
	}
	stop_for_a_while(usb);
}
