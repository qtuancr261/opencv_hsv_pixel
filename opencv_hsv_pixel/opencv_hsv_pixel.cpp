#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
using namespace cv;
using namespace std;
void calChannel(const vector<int>& colorValue, int totalNumPixels)
{
	for (int i{}; i < colorValue.size(); i++)
	{
		cout << left << setw(6) << "Value " << setw(5) << i << ": " << setw(6) << colorValue[i] << "/" << setw(8) << totalNumPixels << " | ";
		if (i % 6 == 0) cout << endl;
	}
	cout << endl;
}


int main(int argc, char *argv[])
{
	Mat input_RGB_img;
	input_RGB_img = imread(argv[1], IMREAD_COLOR);
	if (input_RGB_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	Mat output_HSV_img;
	cvtColor(input_RGB_img, output_HSV_img, COLOR_BGR2HSV); // convert RGB to HSV
	//--------------------------------------------------------------------------------------------
	vector<vector<Vec3b>> pixel(output_HSV_img.rows, vector<Vec3b>(output_HSV_img.cols));
	vector<int> HChannel(180, 0); //  H' <- H/2 (0 <= H <= 360) , For HSV, Hue range is [0,179], Saturation range is [0,255] and Value range is [0,255]
	vector<int> SChannel(256, 0);
	vector<int> VChannel(256, 0);
	int totalNumPixels{ input_RGB_img.rows*input_RGB_img.cols };
	for (int i{}; i < output_HSV_img.rows; i++)
		for (int j{}; j < output_HSV_img.cols; j++)
		{
			pixel[i][j] = output_HSV_img.at<Vec3b>(i, j);
			HChannel[(unsigned int)(pixel[i][j][0])]++;
			SChannel[(unsigned int)(pixel[i][j][1])]++;
			VChannel[(unsigned int)(pixel[i][j][2])]++;
		}
	//--------------------------------------------------------------------------------------------
	cout << "H Channel:-------------------------------------------------------------------- " << endl;
	calChannel(HChannel, totalNumPixels);
	cout << "S Channel:-------------------------------------------------------------------- " << endl;
	calChannel(SChannel, totalNumPixels);
	cout << "V Channel:--------------------------------------------------------------------" << endl;
	calChannel(VChannel, totalNumPixels);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], output_HSV_img);
	waitKey();
	system("cls");
	return 0;
}
