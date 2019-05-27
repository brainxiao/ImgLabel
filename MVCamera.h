#pragma once
#include <CameraApi.h>
#include <opencv2/opencv.hpp>
class MVCamera
{
public:
	MVCamera(const char *cameraName = nullptr);
	~MVCamera();

	bool setExposeTime(double expTime);
	bool getFrame(cv::OutputArray &img); 
	void genLinearTable(float Rk, float Gk, float Bk, float Rb, float Gb, float Bb);

	cv::Size resolution;
private:
	static int sdkInitStatus;
	int cameraId  = -1;
	bool isOpen = false;
	bool mIsLUT = false;
	unsigned char *mTableR;
	unsigned char *mTableG;
	unsigned char *mTableB;
	unsigned char *mTableGray;
	tSdkFrameHead           msFrameInfo;
	tSdkCameraCapbility     mtCapability;
};

