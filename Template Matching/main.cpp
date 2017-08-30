
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;
int main()
{

	cv::Mat ref = cv::imread("c:\\jimmy\\my.bmp");
	cv::Mat tpl = cv::imread("C:\\jimmy\\bottom.bmp");

	cv::Mat gref, gtpl;
	cv::cvtColor(ref, gref, CV_BGR2GRAY);
	cv::cvtColor(tpl, gtpl, CV_BGR2GRAY);
	

	cv::Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);

	cv::matchTemplate(gref, gtpl, res, CV_TM_CCORR_NORMED);
	cv::threshold(res, res, 0.6, 1., CV_THRESH_TOZERO);

	//cv::imshow("reference1", res);

	while (true)
	{
		double minval, maxval, threshold = 0.3;
		cv::Point minloc, maxloc;
		cv::minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

		if (maxval >= threshold)
		{
			cv::rectangle(
				ref,
				maxloc,
				cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
				CV_RGB(0, 255, 0), 2
			);
			cv::floodFill(res, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
		}
		else
			break;
	}

	cv::imshow("reference", ref);
	cv::waitKey(0);
	return 0;
}

