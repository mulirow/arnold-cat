#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(){
    cv::Mat catImage = cv::imread("../images/input/cat.png", cv::IMREAD_COLOR);
    cv::Mat temp, temp2;
    int lambdaH, lambdaV;

    catImage.copyTo(temp);
    catImage.copyTo(temp2);

    int height = catImage.rows;

    std::cin >> lambdaH >> lambdaV;

    //Horizontal shearing:
    //T(x, y) = (x + lambda * y, y) mod height
    for(int y = 0; y < height; y++){
        for(int x = 0; x < height; x++){
            int newX = (x + lambdaH * y) % height;
            int newY = y % height;
            temp.at<cv::Vec3b>(newY, newX) = catImage.at<cv::Vec3b>(y, x);
        }
    }

    //Vertical shearing:
    //T(x, y) = (x, lambda * x + y) mod height
    for(int y = 0; y < height; y++){
        for(int x = 0; x < height; x++){
            int newX = x % height;
            int newY = (lambdaV * x + y) % height;
            catImage.at<cv::Vec3b>(newY, newX) = temp.at<cv::Vec3b>(y, x);
        }
    }

    cv::imwrite("../images/output/test.png", catImage);
}