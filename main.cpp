

//IMFILL FUNCTION IMPLEMENTATION
//NAME :- SAVI KANKANI
// EMAIL ID- savikankani@gmail.com
// Number-9920151071

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\cv.h>


using namespace std;
using namespace cv;


int main(void)

{

Mat img= imread ("C/Desktop/abc.JPG");    //image is read

Mat thresho; //threshold set

threshold(img , thresho , 180, 255 , THRESH_BINARY_INV); //below 180= 0 and 180 to 255= 1.
                                                          // binary image is inverted

Mat imfloodfill = thresho.clone();        //create a copy and floodFill
floodFill ( imfloodfill , cv::Point (0,0) , Scalar (255) );  //start from contour (0,0)

Mat outputimfill; //output image
bitwise_or(thresho, imfloodfill, outputimfill); //bit wise or the threshold and floodFilled image


imshow("output1" , outputimfill); //display the output image
waitKey(0);

return(0);

}

