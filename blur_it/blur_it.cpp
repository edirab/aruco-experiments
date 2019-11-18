// aruco-create-markers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/aruco.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {

	string window_input = "Input";
	string window_output = "Output";

	namedWindow(window_input, WINDOW_AUTOSIZE);
	namedWindow(window_output, WINDOW_AUTOSIZE);

	string path = "../../sources/pic2.jpg";
	//string path = "./pic1.jpg";
	Mat markerImg;
	Mat out;

	markerImg = imread(path, IMREAD_COLOR);
	imshow(window_input, markerImg);
	//waitKey(0);

	GaussianBlur(markerImg, out, Size(13, 13), 0, 0);

	imshow(window_output, out);
	waitKey(0);

	imwrite(path, out);
	return 0;
}

