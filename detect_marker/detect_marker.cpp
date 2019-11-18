

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace cv;
using namespace std;




int main(int argc, char** argv)
{
	int wait_time = 10;
	VideoCapture in_video;
	in_video.open(0);
	//in_video.open("Video4.wmv", cv::CAP_FFMPEG);

	in_video.set(CAP_PROP_FRAME_WIDTH, 1600);
	in_video.set(CAP_PROP_FRAME_HEIGHT, 900);

	Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_ARUCO_ORIGINAL);

	while (in_video.grab())
	{
		Mat image, image_copy;

		in_video.retrieve(image);

		GaussianBlur(image,image_copy, Size(13, 13), 0, 0);
		//image.copyTo(image_copy);

		vector<int> ids;
		vector<vector<Point2f> > corners;

		aruco::detectMarkers(image, dictionary, corners, ids);

		// if at least one marker detected
		if (ids.size() > 0)
			aruco::drawDetectedMarkers(image_copy, corners, ids);

		imshow("Detected markers", image_copy);
		char key = (char)waitKey(wait_time);
		if (key == 27)
			break;
	}

	in_video.release();
}
