#include<vector>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int algquantize(InputArray _img,OutputArray _dst,InputArray _levels,InputArray _values)  //input validation
{
    Mat img=_img.getMat();
    Mat levels=_levels.getMat();
    Mat values=_values.getMat();

    int channelsI=img.channels();
    int valuesType=values.type();


    img.convertTo(img,CV_64FC(channelsI));
    levels.convertTo(levels,CV_64FC1);
    values.convertTo(values,CV_64FC1);

    _dst.create(img.size(),values.type());
    Mat dst=_dst.getMat();

    int n=levels.cols;

    dst.setTo(values.at<double>(0));
    Mat term=Mat::zeros(img.size(),img.type());
    for(int i=0;i<n;i++)
    {
        compare(img,levels.at<double>(i),term,CMP_GT);

        //Make sure term is 1 for true and 0 for false.
        double min,max;
        minMaxLoc(term,&min,&max);
        term/=max;

        //result of compare is of the same type as "I" but "dst" should be of the same type as "values".
        term.convertTo(term,values.type());

        //the term is added in such a way that at every higher level, the previous value is removed
        //and the new value is added.
        term*=(values.at<double>(i+1)-values.at<double>(i));
        dst+=term;
    }

    //Convert "dst" back to the original type of "values"
    dst.convertTo(dst,valuesType);
    return 0;
}


int imquantize(InputArray _img,OutputArray _dst,InputArray _levels,InputArray _values)
{
    Mat img=_img.getMat();
    Mat levels=_levels.getMat();        //_levels - Levels based on which quantization should happen.
    Mat values=_values.getMat();   //_values - Values used to populate the output.

    if(img.type()!=levels.type())
    {
        cerr<<"Levels and input image should be of the same type.";
        return -1;
    }

    int n,n1;
    if(levels.rows==1)
    {
        n=levels.cols;
        cv::sort(levels,levels,CV_SORT_ASCENDING|CV_SORT_EVERY_ROW);
    }

    else if(levels.cols==1)
    {
        n=levels.rows;
        cv::sort(levels,levels,CV_SORT_ASCENDING|CV_SORT_EVERY_COLUMN);
        levels=levels.t();
    }

    else
    {
        cerr<<"Levels should be either row or column matrix or a vector.";
        return -1;
    }

    if(values.rows==1)
        n1=values.cols;                                         //if A(i)<=levels(0) then dst(i)=values(0)
                                                                //if levels(m-1)<A(i)<=levels(m) then dst(i)=values(m)
                                                                  //if A(i)>levels(n-1) then dst(i)=values(n)
    else if(values.cols==1)
{
        n1=values.rows;
        values=values.t();
    }

    else
    {
        cerr<<"Values should be either row or column matrix or a vector.";
        return -1;
    }

    if(n1!=(n+1))
    {
        cerr<<"Values and levels size mismatch.";
        return -1;
    }

    return algquantize(img,_dst,levels,values);
}

int main()
{
    //Read the image
    Mat img=imread(""C/Desktop/abc.JPG", IMREAD_GRAYSCALE");

    //Specify levels
    Mat levels(2,1,CV_8U);
    levels.at<uchar>(0)=90;
    levels.at<uchar>(1)=165;

    //Specify values
    Mat values(3,1,CV_8U);
    values.at<uchar>(0)=7;
    values.at<uchar>(1)=15;
    values.at<uchar>(2)=30;

    Mat ans;
    double minimum,maximum;

    imquantize(img,ans,levels);
    minMaxLoc(ans,&mininum,&maximum);
    ans-=minimum;
    ans.convertTo(ans,ans.type(),1/(maximum-minimum));

     imshow("Quantized",ans); //display output
    waitKey(0);
    destroyAllWindows();
}
