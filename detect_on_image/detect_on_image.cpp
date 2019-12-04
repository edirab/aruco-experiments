

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace cv;
using namespace std;




int main(int argc, char** argv)
{
	string window_input = "Input";
	string window_output = "Output";

	//namedWindow(window_input, WINDOW_AUTOSIZE);
	//namedWindow(window_output, WINDOW_AUTOSIZE);

	string path = "../../sources/";
	string dir = "1080p-m-blur_0/";
	string file = "m-3.jpg";
	string full_path = path + dir + file;


	Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_ARUCO_ORIGINAL);


	Mat image, image_copy;
	image = imread(full_path, IMREAD_COLOR);

	//GaussianBlur(image, image_copy, Size(13, 13), 0, 0);
	//image.copyTo(image_copy);

	vector<int> ids;
	vector<vector<Point2f> > corners;

	aruco::detectMarkers(image, dictionary, corners, ids);

	// if at least one marker detected
	if (ids.size() > 0)
		aruco::drawDetectedMarkers(image, corners, ids);

	imshow("Detected markers", image);
	waitKey(0);

	return 0;
}
