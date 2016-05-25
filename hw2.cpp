#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/legacy/legacy.hpp>

#include <cstdio>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	Mat image = imread("origin.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int cols = image.cols;//width
	int rows = image.rows;//height
	int i, j, m, l;
	char mask[9] = { 1, 2, 2, 3, 1, 2, 1, 0, 3 };
	int s = 0;
	int max, min;
	//printf("rows=%d\n", rows);
	//printf("cols=%d\n", cols);
	Mat dilation_image = Mat(rows, cols, CV_8UC1);
	Mat erosion_image = Mat(rows, cols, CV_8UC1);
	Mat output_image = Mat(rows, cols, CV_8UC1);
	for (j = 0; j<cols; j++)
	{
		for (i = 0; i<rows; i++)
		{
			s = 0;
			max = 0;
			min = 1000;
			for (l = -1; l < 2;l++)//迴積
			{
				for (m = -1; m < 2; m++)
				{
					if ((j == 0 && l == -1) || (i == 0 && m == -1) || (j == (cols-1) && l == 1) || (i == (rows-1) && m == 1))//圖像邊邊複製處理
					{
						if (max < image.at<unsigned char>(i, j) + mask[s])//找最大值
						{
							max = image.at<unsigned char>(i, j) + mask[s];
						}
						if (min > image.at<unsigned char>(i, j) - mask[s])//找最小值
						{
							min = image.at<unsigned char>(i, j) - mask[s];
						}
					}
					else
					{
						if (max < image.at<unsigned char>(i + m, j + l) + mask[s])//找最大值
						{
							max = image.at<unsigned char>(i + m, j + l) + mask[s];
						}
						if (min > image.at<unsigned char>(i + m, j + l) - mask[s])//找最小值
						{
							min = image.at<unsigned char>(i + m, j + l) - mask[s];
						}
					}
					s++;
				}
				dilation_image.at<unsigned char>(i, j ) = max;
				erosion_image.at<unsigned char>(i, j) = min;
				output_image.at<unsigned char>(i, j) = max - min;
			}
		}
	}

	imshow("original", image);
	imshow("output", output_image);
	imshow("dilation_image", dilation_image);
	imshow("erosion_image", erosion_image);
	imwrite("gray_image.jpg", image);
	imwrite("dilation_image.jpg", dilation_image);
	imwrite("erosion_image.jpg", erosion_image);
	imwrite("output.jpg", output_image);
	waitKey(0);
	return 0;
}