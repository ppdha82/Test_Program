#include <opencv2/opencv.hpp>
#include <getopt.h>
#include <sys/time.h>

using namespace cv;
using namespace std;

typedef struct _CV_OPTIONS{
	int view_mode;
	char* input_path;
} CV_OPTIONS;

struct option longopts[] = {
    { "input",          required_argument,  NULL,   'i' },
    { "mode",           required_argument,  NULL,   'm' },
    { "help",           no_argument,        NULL,   'H' },
    { 0, 0, 0, 0 }
};

void showImage(char* input)
{
	Mat srcImage = imread(input);
	if(srcImage.empty()) {
		printf("[%s:%d] srcImage is empty(%s)\n", __FILE__, __LINE__, input);
		return;
	}
	imshow("srcImage", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("grayImage", grayImage);
	cv::waitKey(0);

	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	imshow("hsvImage", hsvImage);
	cv::waitKey(0);

	Mat yCrCbImage;
	cvtColor(srcImage, yCrCbImage, COLOR_BGR2YCrCb);
	imshow("yCrCbImage", yCrCbImage);
	cv::waitKey(0);

	Mat luvImage;
	cvtColor(srcImage, luvImage, COLOR_BGR2Luv);
	imshow("luvImage", luvImage);
	cv::waitKey(0);
}

void showVideo(char* input)
{
	cv::VideoCapture cap(input);
	if(!cap.isOpened()) {
		printf("[%s:%d] cap is not opened(%s)\n", __FILE__, __LINE__, input);
		return;
	}

	printf("[%s:%d] Frame width: %d\n", __FILE__, __LINE__, cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)));
	printf("[%s:%d] Frame height: %d\n", __FILE__, __LINE__, cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)));
	printf("[%s:%d] Frame count: %d\n", __FILE__, __LINE__, cvRound(cap.get(cv::CAP_PROP_FRAME_COUNT)));

	double fps = cap.get(cv::CAP_PROP_FPS);
	printf("[%s:%d] FPS: %f\n", __FILE__, __LINE__, fps);

	int delay = cvRound(1000 / fps);
	int frames = 0;
	float total_time = 0;
	struct timeval time_check;
	struct timeval time_reference;

	cv::Mat frame;
	//cv::Mat inversed;
	
	gettimeofday(&time_reference, 0);
	while(1) {
		cap >> frame;
		if(frame.empty()) {
			break;
		}
		//inversed = ~frame;

		cv::imshow("frame", frame);
		//cv::imshow("inversed", inversed);

		gettimeofday(&time_check, 0);
		++frames;
		total_time = (float)((time_check.tv_sec - time_reference.tv_sec) + (time_check.tv_usec - time_reference.tv_usec) / 1000.0f / 1000.0f);
		if (total_time >= 1.0f) {
			int fps = (int)(frames / total_time);
			printf("[%s:%d] Inference FPS: %i\n", __FILE__, __LINE__, fps);
			frames = 0;
			total_time = 0;
			time_reference = time_check;
		}

		if(cv::waitKey(delay) == 27) {	// 27 == ESC
			break;
		}
	}
	cv::destroyAllWindows();
}

void run(CV_OPTIONS *options)
{
	printf("[%s:%d] view_mode(%d)\n", __FILE__, __LINE__, options->view_mode);
	if(options->view_mode == 0) {
		showImage(options->input_path);
	}
	else if(options->view_mode == 1) {
		showVideo(options->input_path);
	}
	else {
		printf("[%s:%d] Invalid mode(%d)\n", __FILE__, __LINE__, options->view_mode);
	}
}

int main(int argc, char** argv)
{
	int c = 0;
	int mode = 0;
	char* input = NULL;
	CV_OPTIONS options;

	while ((c = getopt_long(argc, argv, "i:m:H", longopts, NULL)) != -1) {
		switch (c) {
			case 'i':
				//input = optarg;
				options.input_path = optarg;
				printf("[%s:%d] input = %s\n", __FILE__, __LINE__, options.input_path);
				break;

			case 'm':
				//mode = atoi(optarg);
				options.view_mode = atoi(optarg);
				printf("[%s:%d] mode = %d\n", __FILE__, __LINE__, options.view_mode);
				break;

			default:
				printf("%s [-i input] [-H]\n", argv[0]);
				exit(1);
		}
	}

	run(&options);

	return 0;
}
