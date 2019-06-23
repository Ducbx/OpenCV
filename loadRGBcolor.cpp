#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("RGB.png", 1);
	namedWindow("Original Image", 1);
	imshow("Original Image", image);

	// Split the image into different channels
	vector<Mat> rgbChannels(3);
	split(image, rgbChannels);

	// Show individual channels
	Mat g, fin_img;
	g = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);

	// Showing Red Channel
	// G and B channels are kept as zero matrix for visual perception
	{
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(rgbChannels[2]);

		/// Merge the three channels
		merge(channels, fin_img);
		namedWindow("Red", 1);
		imshow("Red", fin_img);
	}

	// Showing Green Channel
	{
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(rgbChannels[1]);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("Green", 1);
		imshow("Green", fin_img);
	}

	// Showing Blue Channel
	{
		vector<Mat> channels;
		channels.push_back(rgbChannels[0]);
		channels.push_back(g);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("Blue", 1);
		imshow("Blue", fin_img);
	}

	waitKey(0);
	return 0;
}