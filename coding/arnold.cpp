#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void shearing(int, void*);

int findIterations();

//Change the path of these two lines to modify input image
cv::Mat source = cv::imread("../images/input/cat-math.png", cv::IMREAD_COLOR);
cv::Mat catImage = cv::imread("../images/input/cat-math.png", cv::IMREAD_COLOR);

int tracker = 0, prevTracker = 0;
int lambdaH = 1, lambdaV = 1;

int main(){

    int iterations = findIterations();

    cv::imshow("Arnold's Cat", source);
    cv::namedWindow("Trackbars");
    cv::createTrackbar("Iterations", "Trackbars", &tracker, iterations, shearing);
    cv::createTrackbar("Horizontal Lambda", "Trackbars", &lambdaH, 10, shearing);
    cv::createTrackbar("Vertical Lambda", "Trackbars", &lambdaV, 10, shearing);
    cv::waitKey();
    cv::imwrite("../images/output/cat-output.png", catImage);
}

void shearing(int, void*){
    cv::Mat temp = catImage.clone();

    int height = catImage.rows;
    int width = catImage.cols;

    if(tracker > prevTracker){
        for(int i = prevTracker; i < tracker; i++){
            //Horizontal shearing:
            //T(x, y) = (x + lambda * y, y) mod width
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int newX = (x + lambdaH * y) % width;
                    int newY = y % height;
                    temp.at<cv::Vec3b>(newY, newX) = catImage.at<cv::Vec3b>(y, x);
                }
            }

            //Vertical shearing:
            //T(x, y) = (x, lambda * x + y) mod height
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int newX = x % width;
                    int newY = (y + lambdaV * x) % height;
                    catImage.at<cv::Vec3b>(newY, newX) = temp.at<cv::Vec3b>(y, x);
                }
            }
        }
    }
    else if(prevTracker > tracker){
        for(int i = tracker; i < prevTracker; i++){
            //Reverse vertical shearing:
            //T(x, y) = (x, -lambda * x + y) mod height
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int newX = x % width;
                    int newY = ((y - lambdaV * x) % height + height) % height;
                    temp.at<cv::Vec3b>(newY, newX) = catImage.at<cv::Vec3b>(y, x);
                }
            }

            //Reverse horizontal shearing:
            //T(x, y) = (x - lambda * y, y) mod width
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int newX = ((x - lambdaH * y) % width + width) % width;
                    int newY = y % height;
                    catImage.at<cv::Vec3b>(newY, newX) = temp.at<cv::Vec3b>(y, x);
                }
            }
        }
    }

    prevTracker = tracker;

    cv::imshow("Arnold's Cat", catImage);
}

int gcd(int a, int b){
    if(b != 0){
        return gcd(b, a % b);
    }
    return a;
}

int lcm(int a, int b){
    return a * b / gcd(a, b);
}

//LCM of movement cycle size of all pixels
//Known the size of the image, its contents can be ignored for this operation
int findIterations(){
    int result = 1;
    int height = catImage.rows;
    int width = catImage.cols;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int newX = x, newY = y, pathSize = 0;

            //Shear while pixel position is different from the original
            while((newX != x) || (newY != y) || (pathSize == 0)){
                //Horizontal shearing of a single pixel:
                newX = (newX + lambdaH * newY) % width;
                newY = newY % height;

                //Vertical shearing of a single pixel:
                newY = (newY + lambdaV * newX) % height;
                newX = newX % width;

                pathSize++;
            }
            result = lcm(result, pathSize);
            //std::cout << pathSize << " ";
        }
        //std::cout << "\n";
    }
    return result;
}