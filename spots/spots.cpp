//https://docs.opencv.org/4.1.1/de/d62/tutorial_bounding_rotated_ellipses.html
//https://docs.opencv.org/4.1.1/d3/dbe/tutorial_opening_closing_hats.html

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace cv;
using namespace std;

int threshold_value = 245;
//int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

float treshold_area = 30 * 20;

string path = "../../sources/";
string dir = "";
string file = "led_blue.jpg";
string full_path = path + dir + file;

Mat image, image_gray, hough, tresh, tresh_opening, canny_output, drawing;

RNG rng(12345);

vector<Vec3f> circles;

void morphology_Operation(int morph_operator, Mat& src, Mat & dst)
{
	int morph_elem = MORPH_RECT;
	int morph_size = 5;

	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, dst, morph_operator, element);
	imshow("Morph operation", dst);
}

int main(int argc, char** argv)
{

	image = imread(full_path, IMREAD_COLOR);
	cvtColor(image, image_gray, COLOR_BGR2GRAY); // Convert the image to Gray
	//GaussianBlur(image, image_copy, Size(13, 13), 0, 0);
	image.copyTo(hough);

	
	HoughCircles(image_gray, circles, HOUGH_GRADIENT, 1,
		image_gray.rows / 32,  // change this value to detect circles with different distances to each other
		100, 30, 20, 50 // change the last two parameters
					   // (min_radius & max_radius) to detect larger circles
	);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		// circle center
		circle(hough, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(hough, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}

	threshold(image_gray, tresh, threshold_value, max_binary_value, THRESH_TOZERO);
	
	morphology_Operation(MORPH_OPEN, tresh ,tresh_opening);

	//Canny(image_gray, canny_output, threshold_value-30, 255);
	//Canny(tresh, canny_output, 0, 255);
	Canny(tresh_opening, canny_output, 0, 255);

	vector<vector<Point> > contours;

	findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> realRect;
	vector<RotatedRect> minEllipse;

	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(contours[i]);
		if (contours[i].size() > 5 && (float(minRect[i].size.width) * float(minRect[i].size.height) > treshold_area)) {
			realRect.push_back(minRect[i]);
			minEllipse.push_back(fitEllipse(contours[i]));
		}
	}

	drawing = Mat::zeros(canny_output.size(), CV_8UC3);

	for (size_t i = 0; i < realRect.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		// contour
		//drawContours(drawing, contours, (int)i, color);
		// ellipse
		ellipse(drawing, minEllipse[i], color, 2);
		// rotated rectangle
		Point2f rect_points[4];
		realRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
		{
			line(drawing, rect_points[j], rect_points[(j + 1) % 4], color);
		}
	}


	imshow("Original", image);
	imshow("Grayscale", image_gray);
	imshow("Treshold", tresh);
	imshow("Hough Detector", hough);
	imshow("Canny output", canny_output);
	imshow("Contours", drawing);

	waitKey(0);

	return 0;
}
