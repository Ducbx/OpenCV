#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat rotateTest(Mat src, double angle)
{
	Mat rotateImg;
	Point2f center(src.cols / 2.0, src.rows / 2.0);
	Mat rotateMatric = getRotationMatrix2D(center, angle, 0.5);
	warpAffine(src, rotateImg, rotateMatric, Size(src.cols, src.rows));
	return rotateImg;
}

int main()
{
	Mat src = imread("ducbx.png");

	Mat dst;
	dst = rotateTest(src, 10);
	//rotate(src, dst,ROTATE_90_CLOCKWISE);


	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}