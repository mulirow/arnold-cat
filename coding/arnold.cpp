#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(){
    cv::Mat catImage = cv::imread("../images/input/cat.png", cv::IMREAD_COLOR);
    cv::Mat temp = catImage.clone(), temp2 = catImage.clone();

    int lambdaH, lambdaV, iterations;


    //Tranformation works for squared images only, so width = height 
    int height = catImage.rows;

    std::cin >> lambdaH >> lambdaV >> iterations;

    while(iterations > 0){
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

        iterations--;
    }

    cv::imwrite("../images/output/test.png", catImage);
}