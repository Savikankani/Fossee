//MULTITHRESH FUNCTION
//NAME :- SAVI KANKANI
//EMAIL-ID : savikankani@gmail.com
//INPUT - img (abc.JPG)
//OUTPUT - output



#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>
#include "gui.hpp"



using namespace std;
using namespace cv;


int main(void)

{

Mat img= imread ("C/Desktop/abc.JPG"); //image read
Mat output;
ThreshOpts thresh; //ThreshOpts is a class in the gui library in which various options are given for various levels
thresh.output();
output= thresh.threshold(img); //set threshold

    imshow("Thresholded", output); //display image after performing function

waitKey();
cvDestroyAllWindows();
return 0;

}
