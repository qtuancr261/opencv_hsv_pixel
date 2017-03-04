#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
void calChannel(const vector<int>& colorValue, int& count)
{
	for (int i{}; i < colorValue.size(); i++)
	{
		cout << left << setw(6) << "Value" << setw(3) << i << ": " << setw(6) << colorValue[i] << "| ";
		count += colorValue[i];
		if (i % 8 == 0) cout << endl;
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
		return -1;
	}
	Mat output_HSV_img;
	cvtColor(input_RGB_img, output_HSV_img, COLOR_BGR2HSV);
	//--------------------------------------------------------------------------------------------
	vector<vector<Vec3b>> pixel(output_HSV_img.rows, vector<Vec3b>(output_HSV_img.cols));
	vector<int> HChannel(181, 0); //  H' <- H/2 (0 <= H <= 360)
	vector<int> SChannel(256, 0);
	vector<int> VChannel(256, 0);
	int count{};
	for (int i{}; i < output_HSV_img.rows; i++)
		for (int j{}; j < output_HSV_img.cols; j++)
		{
			pixel[i][j] = output_HSV_img.at<Vec3b>(i, j);
			HChannel[(unsigned int)(pixel[i][j][0])]++;
			SChannel[(unsigned int)(pixel[i][j][1])]++;
			VChannel[(unsigned int)(pixel[i][j][2])]++;
		}
	cout << "H Channel: " << endl;
	calChannel(HChannel,count);
	cout << "S Channel: " << endl;
	calChannel(SChannel, count);
	cout << "V Channel" << endl;
	calChannel(VChannel, count);
	cout << "Pixels: " << output_HSV_img.rows * output_HSV_img.cols << " = " << count/3 <<endl;
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], output_HSV_img);
	waitKey();
	return 0;
}
