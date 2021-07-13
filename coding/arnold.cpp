#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void shearing(int, void*);

int tracker = 0;
int lambdaH = 1, lambdaV = 1;

int main(){
    cv::Mat source = cv::imread("../images/input/cat-math.png", cv::IMREAD_COLOR);

    int iterations;

    std::cin >> iterations;

    cv::imshow("Arnold's Cat", source);
    cv::createTrackbar("Iterations", "Arnold's Cat", &tracker, iterations, shearing);
    cv::createTrackbar("Horizontal Lambda", "Arnold's Cat", &lambdaH, iterations, shearing);
    cv::createTrackbar("Vertical Lambda", "Arnold's Cat", &lambdaV, iterations, shearing);
    cv::waitKey();

    cv::imwrite("../images/output/cat-output.png", source);
}

void shearing(int, void*){
    cv::Mat catImage = cv::imread("../images/input/cat-math.png", cv::IMREAD_COLOR);
    cv::Mat temp = catImage.clone();

    //Tranformation works for squared images only, so width = height 
    int height = catImage.rows;

    for(int i = 1; i <= tracker; i++){
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
    }

    cv::imshow("Arnold's Cat", catImage);
}