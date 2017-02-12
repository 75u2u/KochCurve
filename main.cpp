#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#define PI 3.14159265358979

using namespace cv;
void koch(int x1, int y1, int x2, int y2, int it);
Mat img = Mat::zeros(400, 500, CV_8UC3);

int main(int argc, char *argv[]) {
	
	int x1 = 100, y1 = 100, x2 = 400, y2 = 100;
	int count = 0;
	
	koch(x1, y1, x2, y2, count);
	koch(x2, y2, (x2 - x1) / 2 + x1, y2 * 2 * sqrt(3), count);
	koch((x2 - x1) / 2 + x1, y2 * 2 * sqrt(3), x1, y1, count);

	namedWindow("KochCurve", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	imshow("KochCurve", img);
	waitKey(0);
	return 0;
}

void koch(int x1, int y1, int x2, int y2, int it) {
	float angle = 60 * PI / 180;
	int x3 = (2 * x1 + x2) / 3;
	int y3 = (2 * y1 + y2) / 3;

	int x4 = (x1 + 2 * x2) / 3;
	int y4 = (y1 + 2 * y2) / 3;

	int x = x3 + (x4 - x3)*cos(angle) + (y4 - y3)*sin(angle);
	int y = y3 - (x4 - x3)*sin(angle) + (y4 - y3)*cos(angle);

	if (it > 0){
		koch(x1, y1, x3, y3, it - 1);
		koch(x3, y3, x, y, it - 1);
		koch(x, y, x4, y4, it - 1);
		koch(x4, y4, x2, y2, it - 1);
	}else{
		line(img, Point(x1, y1), Point(x3, y3), Scalar(0, 0, 250), 1, CV_AA);
		line(img, Point(x3, y3), Point(x, y), Scalar(0, 0, 250), 1, CV_AA);
		line(img, Point(x, y), Point(x4, y4), Scalar(0, 0, 250), 1, CV_AA);
		line(img, Point(x4, y4), Point(x2, y2), Scalar(0, 0, 250), 1, CV_AA);
	}
}
