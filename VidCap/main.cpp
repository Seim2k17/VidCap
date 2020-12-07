#include <iostream>
#include <string>

#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

static void help()
{
	cout
		<< "------------------------------------------------" << endl
		<< "This program reads a video stream and output it" << endl
		<< "------------------------------------------------" << endl
		<< endl;
}

int main(int argc, char* argv[])
{
	help();
	if (argc != 2)
	{
		cout << "Not enough parameter, please specify input" << endl;
		return -1;
	}

	/* stream from http protocoll does not work out of the box, but rtsp is | but bad quality due compression (h264)
	, tested with Ip Webcam (Android) */
	//const string sourceReference = "http://192.168.123.33:8080";//argv[1];
	const string sourceReference = "rtsp://192.168.123.33:8080/h264_ulaw.sdp";
	//const string sourceReference = "rtsp://192.168.123.33:8080/h264_pcm.sdp";

	int frameNum = -1;          // Frame counter

	VideoCapture vidCap(sourceReference);
	if (!vidCap.isOpened())
	{
		cout << "Open VideoStream " << sourceReference << " failed" << endl;
		return -1;
	}
	
	Size vidSize = Size((int)vidCap.get(CAP_PROP_FRAME_WIDTH), (int)vidCap.get(CAP_PROP_FRAME_HEIGHT));

	const char* WIN_VID = "StreamPreview";

	namedWindow(WIN_VID, WINDOW_AUTOSIZE);
	moveWindow(WIN_VID, 400, 0);

	Mat videoFrame;

	for (;;)
	{
		vidCap >> videoFrame;

		if (videoFrame.empty())
		{
			cout << " ENDE ";
			break;
		}
		++frameNum;
		cout << "Frame: " << frameNum << endl;
		imshow(WIN_VID, videoFrame);
		char c = (char)waitKey(10);
		if (c == 27) break; // ESC
	}

	return 0;
}