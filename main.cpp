//MULTITHRESH FUNCTION
//NAME :- SAVI KANKANI
//EMAIL-ID : savikankani@gmail.com
//INPUT - img (abc.JPG)
//OUTPUT - output



#include <opencv\cv.h>
#include <opencv\highgui.h>


using namespace std;
using namespace cv;


int main(void)

{

Mat img= imread ("C/Desktop/abc.JPG"); //image read
Mat output;
ThreshOpts thresh;
thresh.output();
output= thresh.threshold(img); //set threshold

    imshow("Thresholded", output); //display image after performing function

waitKey();
cvDestroyAllWindows();
return 0;

}
