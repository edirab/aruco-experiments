// aruco-create-markers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace cv;

/*
Debug purposes only.
Prints a part of a matrix to scecified text file.
*/
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

/*
Adding gaussian noize to given image
Returns its copy.
*/
Mat addNoize(Mat input, int mean, int std) {

	Mat output = input.clone();
	Mat noize(input.size(), input.type());

	Scalar Mean(mean, mean, mean);
	Scalar Std(std, std, std);

	randn(noize, Mean, Std);

	imshow("Noize", noize);
	printToFile(noize, true, "noize.txt");

	output += noize;

	return output;
}


int main(int argc, char* argv[]) {
	
	//Mat image = imread("../../sources/pic1.jpg");
	Mat input = imread("F:/Университет/9sem/С++/code/aruco-create-markers/sources/pic1.jpg");
	imshow("Initial", input);

	Mat noised = addNoize(input, 0, 60);
	//noised += noise;

	printToFile(input, true, "input.txt");
	printToFile(noised, true, "noised.txt");

	imshow("Noised", noised);
	imwrite("F:/Университет/9sem/С++/code/aruco-create-markers/sources/pic1_noised.jpg", noised);

	waitKey(0);

	return 0;
}

