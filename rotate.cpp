#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat rotateTest(Mat src, double angle)
{
	Point2f center(src.cols / 2.0, src.rows / 2.0);
	Mat rotateMatric = getRotationMatrix2D(center, angle, 1.0);

	// determine bounding rectangle, center not relevant
	Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();
	// adjust transformation matrix
	rotateMatric.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
	rotateMatric.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

	Mat rotateImg;
	//Mat rotateImg(Size(src.size().height, src.size().width), src.type());
	//warpAffine(src, rotateImg, rotateMatric, src.size());
	warpAffine(src, rotateImg, rotateMatric, bbox.size());
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