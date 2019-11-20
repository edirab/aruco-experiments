// aruco-create-markers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace cv;

void printToFile(Mat img, bool truncated = false, string filename = "data.txt") {
	ofstream out(filename);

	int rows = img.rows;
	int cols = img.cols;

	if (truncated) {
		rows = cols = 5;
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			//const Vec3b& v = img.at(r, c);
			out << "(";
			out << uppercase << setw(4) << setfill(' ') << float(img.at<Vec3b>(r, c)[0]);// int(v[0]);
			out << uppercase << setw(4) << setfill(' ') << float(img.at<Vec3b>(r, c)[1]);
			out << uppercase << setw(4) << setfill(' ') << float(img.at<Vec3b>(r, c)[2]);
			out << "), ";
		}
		out << endl;
	}
}


int main(int argc, char* argv[]) {
	
	//Mat image = imread("../../sources/pic1.jpg");
	Mat input = imread("F:/Университет/9sem/С++/code/aruco-create-markers/sources/pic1.jpg");
	imshow("Initial", input);

	Mat noise(input.size(), input.type());
	//cout << to_string(input.type());

	randn(noise, 0, 0.1); //mean and variance

	/*
	Mat3b img(3, 4, Vec3b(15, 14, 12));
	randu(img, Scalar(0, 0, 0), Scalar(256, 256, 256));

	// Save to Hex ASCII
	ofstream out("data.txt");
	for (int r = 0; r < img.rows; ++r) {
		for (int c = 0; c < img.cols; ++c) {
			const Vec3b& v = img(r, c);
			out << "(";
			out << uppercase << setw(4) << setfill(' ') << int(v[0]);
			out << uppercase << setw(4) << setfill(' ') << int(v[1]);
			out << uppercase << setw(4) << setfill(' ') << int(v[2]);
			out << "), ";
		}
		out << endl;
	}
	*/


	Mat noised = input.clone();
	noised += noise;

	printToFile(input, true, "input.txt");
	printToFile(noise, true, "noise.txt");
	printToFile(noised, true, "noised.txt");

	Mat  clamp_1 = Mat::ones(noised.size(), noised.type());
	Mat  clamp_0 = Mat::zeros(noised.size(), noised.type());
	noised = max(noised, 0);
	noised = min(noised, 1);

	imshow("Noised", noised);
	imwrite("F:/Университет/9sem/С++/code/aruco-create-markers/sources/pic1_noised.jpg", noised);

	imwrite("F:/Университет/9sem/С++/code/aruco-create-markers/sources/noise.jpg", noise);

	waitKey(0);

	return 0;
}

