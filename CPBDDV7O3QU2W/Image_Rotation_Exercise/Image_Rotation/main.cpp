#include <iostream>
#include <opencv2\opencv.hpp>

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle) {
	if (angle < 0) {
		while (angle < -360.0f) {
			angle = angle + 360.f;
		}
		angle += 360;
	}
	if (angle >= 360.0f) {
		while (angle > 360.f) {
			angle = angle - 360.0f;
		}
	}
	double seta = angle * CV_PI / 180.0;

	int height = img.rows;
	int width = img.cols;
	double new_width = abs((img.cols) * cos(seta)) + abs((img.rows) * sin(seta));
	double new_height = abs((img.cols) * sin(seta)) + abs((img.rows) * cos(seta));

	cv::Mat output = cv::Mat::zeros(new_height+1, new_width+1, img.type());
	
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			int rotate_x = (cos(seta) * i) + (-sin(seta) * j);
			int rotate_y = (sin(seta) * i) + (cos(seta) * j);

			if (seta <= CV_PI / 2) {
				rotate_x += width * sin(seta);
			}
			else if (seta <= CV_PI) {
				rotate_x += (height * sin(seta - (CV_PI / 2))) + (width * cos(seta - (CV_PI / 2)));
				rotate_y += width * sin(seta - (CV_PI / 2));
			}
			else if (seta <= (CV_PI * 3 / 2)) {
				rotate_x += height * cos(seta - CV_PI);
				rotate_y += (height * sin(seta - CV_PI)) + (width * cos(seta - CV_PI));
			}
			else {
				rotate_y += height * cos(seta - (CV_PI * 3/ 2));
			}
//			printf("%d %d %d %d\n", rotate_x, rotate_y,i,j);
			output.at<cv::Vec3b>(rotate_x, rotate_y) = img.at<cv::Vec3b>(i, j);
		}
	}


	cv::imshow("a_output", output);
	cv::waitKey(0);

	return output;
}



cv::Mat problem_b_rotate_backward(cv::Mat img, double angle) {
	if (angle < 0) {
		while (angle < -360.0f) {
			angle = angle + 360.f;
		}
		angle += 360;
	}
	if (angle >= 360.0f) {
		while (angle > 360.f) {
			angle = angle - 360.0f;
		}
	}
	double seta = angle * CV_PI / 180.0;
	int height = img.rows;
	int width = img.cols;
	double new_width = abs((img.cols) * cos(seta)) + abs((img.rows) * sin(seta));
	double new_height = abs((img.cols) * sin(seta)) + abs((img.rows) * cos(seta));
	cv::Mat output = cv::Mat::zeros(new_height + 1, new_width + 1, img.type());

	for (int i = 0; i < new_height; i++)
	{
		for (int j = 0; j < new_width; j++)
		{
			double before_x, before_y;
			before_x = i; before_y = j;

			if (seta <= CV_PI / 2) {
				before_x -= width * sin(seta);
			}
			else if (seta <= CV_PI) {
				before_x -= (height * sin(seta - (CV_PI / 2))) + (width * cos(seta - (CV_PI / 2)));
				before_y -= width * sin(seta - (CV_PI / 2));
			}
			else if (seta <= (CV_PI * 3 / 2)) {
				before_x -= height * cos(seta - CV_PI);
				before_y -= (height * sin(seta - CV_PI)) + (width * cos(seta - CV_PI));
			}
			else {
				before_y -= height * cos(seta - (CV_PI * 3 / 2));
			}
			
			int reverse_x, reverse_y;

			reverse_x = cos(seta) * before_x + sin(seta) * before_y;
			reverse_y = -sin(seta) * before_x + cos(seta) * before_y;
//			printf("%d %d\n", reverse_x, reverse_y);
			if (reverse_x > 0 && reverse_y > 0 && reverse_x < height && reverse_y < width) {
				output.at<cv::Vec3b>(i, j) = img.at<cv::Vec3b>(reverse_x, reverse_y);
			}
		}
	}
	cv::imshow("b_output", output);
	cv::waitKey(0);
	return output;
}



cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle) {
	if (angle < 0) {
		while (angle < -360.0f) {
			angle = angle + 360.f;
		}
		angle += 360;
	}
	if (angle >= 360.0f) {
		while (angle > 360.f) {
			angle = angle - 360.0f;
		}
	}
	double seta = angle * CV_PI / 180.0;
	int height = img.rows;
	int width = img.cols;
	double new_width = abs((img.cols) * cos(seta)) + abs((img.rows) * sin(seta));
	double new_height = abs((img.cols) * sin(seta)) + abs((img.rows) * cos(seta));
	cv::Mat output = cv::Mat::zeros(new_height + 1, new_width + 1, img.type());
//	printf("mother %f %f\n", new_height, new_width);
	for (int i = 0; i < new_height; i++)
	{
		for (int j = 0; j < new_width; j++)
		{
			double before_x, before_y;
			before_x = i; before_y = j;

			if (seta <= CV_PI / 2) {
				before_x -= width * sin(seta);
			}
			else if (seta <= CV_PI) {
				before_x -= (height * sin(seta - (CV_PI / 2))) + (width * cos(seta - (CV_PI / 2)));
				before_y -= width * sin(seta - (CV_PI / 2));
			}
			else if (seta <= (CV_PI * 3 / 2)) {
				before_x -= height * cos(seta - CV_PI);
				before_y -= (height * sin(seta - CV_PI)) + (width * cos(seta - CV_PI));
			}
			else {
				before_y -= height * cos(seta - (CV_PI * 3 / 2));
			}
			
			float reverse_x, reverse_y;

			reverse_x = cos(seta) * before_x + sin(seta) * before_y;
			reverse_y = -sin(seta) * before_x + cos(seta) * before_y;
//			printf("%d %d\n", reverse_x, reverse_y);
			if (reverse_x > 0 && reverse_y > 0 && reverse_x < height-1 && reverse_y < width-1) {
				cv::Point2f B(floor(reverse_x), floor(reverse_y));
				cv::Point2f C(floor(reverse_x), floor(reverse_y) + 1);
				cv::Point2f A(floor(reverse_x)+1, floor(reverse_y));
				cv::Point2f D(floor(reverse_x)+1, floor(reverse_y) + 1);
			
				float alpha = floor(reverse_x)+1 - reverse_x;
				float beta = reverse_x - floor(reverse_x);
				float p = reverse_y - floor(reverse_y);  float q = floor(reverse_y) + 1 - reverse_y;
				float w1 = reverse_y - floor(reverse_y); float w2 = floor(reverse_y) + 1 - reverse_y;
				float h1 = floor(reverse_x)+1 - reverse_x; float h2 = reverse_x - floor(reverse_x);
				int rgb_arr[4][3];
				
				for (int k = 0; k < 3; k++)
				{
					rgb_arr[0][k] = img.at<cv::Vec3b>(floor(reverse_x)+1, floor(reverse_y))[k]; //a
					rgb_arr[1][k] = img.at<cv::Vec3b>(floor(reverse_x), floor(reverse_y))[k]; //b
					rgb_arr[2][k] = img.at<cv::Vec3b>(floor(reverse_x), floor(reverse_y) + 1)[k]; //c
					rgb_arr[3][k] = img.at<cv::Vec3b>(floor(reverse_x)+1, floor(reverse_y) + 1)[k]; //d
				}
				
				float final_b = (q * beta * rgb_arr[0][0]) + (q * alpha * rgb_arr[1][0]) + (p * beta * rgb_arr[3][0]) + (p * alpha * rgb_arr[2][0]);
				float final_g = (q * beta * rgb_arr[0][1]) + (q * alpha * rgb_arr[1][1]) + (p * beta * rgb_arr[3][1]) + (p * alpha * rgb_arr[2][1]);
				float final_r = (q * beta * rgb_arr[0][2]) + (q * alpha * rgb_arr[1][2]) + (p * beta * rgb_arr[3][2]) + (p * alpha * rgb_arr[2][2]);
				
				output.at<cv::Vec3b>(i, j)[0] = final_b;
				output.at<cv::Vec3b>(i, j)[1] = final_g;
				output.at<cv::Vec3b>(i, j)[2] = final_r;
				
			}
		}
	}
	cv::imshow("c_output", output);
	cv::waitKey(0);
	return output;
}





cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {

	cv::Mat output = img.clone();

	int size = 200;
	int height = img.cols;
	int width = img.rows;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}
	}

	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	
	return output;
}



int main(void) {

	double angle = 45.0f;
	cv::Mat input = cv::imread("lena.jpg");

	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	 
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);

	//Example how to access pixel value, change params if you want
	//Example_change_brightness(input, 100, 0, 0);

}

