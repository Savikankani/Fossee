

//IMFILL FUNCTION IMPLEMENTATION
//INPUT -- img
//OUTPUT -- outputimfill
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

Mat img = imread ("C/Desktop/abc.JPG");    //image is read

Mat thresho; //threshold set

threshold(img , thresho , 190, 255 , THRESH_BINARY_INV); //below 190= 0 and 190 to 255= 1.
                                                          // binary image is inverted

Mat imfloodfill = thresho.clone();        //create a copy and floodFill
floodFill ( imfloodfill , cv::Point (0,0) , Scalar (255) );  //start from contour (0,0)

Mat iminvfloodfill;  //invert the floodFill image
bitwise_not(imfloodfill,iminvfloodfill );

Mat outputimfill; //output image
bitwise_or(thresho, iminvfloodfill, outputimfill); //bit wise or the threshold and floodFilled image


imshow("output1" , outputimfill); //display the output image
waitKey(0);

return(0);

}

