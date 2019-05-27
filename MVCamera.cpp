#include <stdio.h>
#include <CameraApi.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "MVCamera.h"
using namespace cv;
#define mErrorHandler(FUN) do{int mErrorNum_sdfdg = FUN;\
	if (mErrorNum_sdfdg != 0){ \
		printf("Error ret %d, on %s, ", mErrorNum_sdfdg, #FUN); \
		return mErrorNum_sdfdg;}}while(0)
#define mErrorHandler_NotRet(FUN) do{int mErrorNum_sdfdg = FUN;\
	if (mErrorNum_sdfdg != 0){ \
		printf("Error ret %d, on %s, ", mErrorNum_sdfdg, #FUN);return;}}while(0)

int MVCamera::sdkInitStatus = -1;
using namespace std;
MVCamera::MVCamera(const char * cameraName)
{
	if (sdkInitStatus != 0)
	{
		mErrorHandler_NotRet(CameraSdkInit(1));
	}
	tSdkCameraDevInfo camInfo[4];
	int cameraNum = 4;
	mErrorHandler_NotRet(CameraEnumerateDevice(camInfo, &cameraNum));
	if (!cameraNum)
	{
		cout << "can't find any camera!" << endl;
		return;
	}
	tSdkCameraDevInfo *targetCamera = nullptr;
	if (cameraName != nullptr)
	{
		for (size_t i = 0; i < cameraNum; i++)
		{
			cout << "find camera " << camInfo[i].acFriendlyName << endl;
			if (!strcmp(camInfo[i].acFriendlyName, cameraName))
			{
				int isOpen_m;
				mErrorHandler_NotRet(CameraIsOpened(&(camInfo[i]), &isOpen_m));
				if (isOpen)
				{
					cout << cameraName << "was opened" << endl;
					return;
				}
				mErrorHandler_NotRet(CameraInit(&(camInfo[i]), -1, -1, &cameraId));
				targetCamera = &camInfo[i];
				break;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < cameraNum; i++)
		{
			int isOpen_m = 0;
			mErrorHandler_NotRet(CameraIsOpened(&(camInfo[i]), &isOpen_m));
			if (isOpen_m == false)
			{
				mErrorHandler_NotRet(CameraInit(&(camInfo[i]), -1, -1, &cameraId));
				targetCamera = &camInfo[i];
				break;
			}
		}
	}
	if (cameraId == -1)
	{
		cout << "Can't find any useable camera" << endl;
		return;
	}
	CameraInit(targetCamera, -1, -1, &cameraId); //��ʼ��ָ������
	// setting camera
	CameraSetAeState(cameraId, false);
	CameraSetTriggerMode(cameraId, 1);
	CameraGetCapability(cameraId, &mtCapability); // ��ȡ������Ϣ
	for (int i = 0; i < mtCapability.iImageSizeDesc; i++)
	{
		if (mtCapability.pImageSizeDesc[i].iHeight == mtCapability.sResolutionRange.iHeightMax &&
			mtCapability.pImageSizeDesc[i].iWidth == mtCapability.sResolutionRange.iWidthMax)
		{
			resolution.width = mtCapability.pImageSizeDesc[i].iWidth;
			resolution.height = mtCapability.pImageSizeDesc[i].iHeight;
			mErrorHandler_NotRet(CameraSetImageResolution(cameraId, &mtCapability.pImageSizeDesc[i]));
			break;
		}
	}
	mErrorHandler_NotRet(CameraPlay(cameraId));
	isOpen = true;
	return;
}

MVCamera::~MVCamera()
{
	if (cameraId != -1)
	{
		CameraUnInit(cameraId);
	}
}

bool MVCamera::setExposeTime(double expTime)
{
	CameraSetExposureTime(cameraId, expTime);
	return false;
}

bool MVCamera::getFrame(cv::OutputArray & _dst)
{
	mErrorHandler(CameraSoftTrigger(cameraId));
	uchar *mpbyBuffer;
	auto capRet = CameraGetImageBuffer(cameraId, &msFrameInfo, &mpbyBuffer, 5000);
		if (capRet != 0)
		{
			printf("�������մ��󣬷��� %d \n", capRet);
			return capRet;
		}
		if (mtCapability.pMediaTypeDesc[0].iMediaType == CAMERA_MEDIA_TYPE_MONO8) {
			_dst.create(resolution, CV_8UC1);
			cv::Mat dst = _dst.getMat();
			auto sptr = mpbyBuffer + (dst.rows - 1) * dst.cols;
			auto dptr = dst.data;
			if (mIsLUT)
			{
				for (int i = 0; i < dst.rows; i++)
				{
					for (int j = 0; j < dst.cols; j++)
					{
						*(dptr++) = mTableGray[sptr[j]];
					}
					sptr -= dst.cols;
				}
			}
			else
			{
				for (int i = 0; i < dst.rows; i++)
				{
					memcpy(dptr, sptr, dst.cols);
					sptr -= dst.cols;
					dptr += dst.cols;
				}
			}
			//threshold(dst, dst, 128, 255, CV_THRESH_BINARY);
		}
		else
		{
			_dst.create(resolution, CV_8UC3);
			cv::Mat dst = _dst.getMat();
			cv::Mat tdst(resolution, CV_8UC1);
			memcpy(tdst.data, mpbyBuffer, tdst.cols * tdst.rows);
            cvtColor(tdst, dst, COLOR_BayerBG2BGR);
			if (mIsLUT)
			{
				for (int i = 0; i < dst.rows; i++)
				{
					uchar *rptr = dst.ptr(i);
					for (int j = 0; j < dst.cols; j++)
					{
						*rptr = mTableB[*rptr];
						rptr++;
						*rptr = mTableG[*rptr];
						rptr++;
						*rptr = mTableR[*rptr];
						rptr++;
					}
				}
			}
		}
		mErrorHandler(CameraReleaseImageBuffer(cameraId, mpbyBuffer));

return false;
}
void MVCamera::genLinearTable(float Rk, float Gk, float Bk, float Rb, float Gb, float Bb)
{
	if (mTableR == nullptr)
	{
		mTableR = (unsigned char *)malloc(255);
		mTableB = (unsigned char *)malloc(255);
		mTableG = (unsigned char *)malloc(255);
	}
	int t;
	for (size_t i = 0; i < 256; i++)
	{
		t = (int)(i * Rk + Rb);
		mTableR[i] = t > 255 ? 255 : t;
		t = (int)(i * Gk + Gb);
		mTableG[i] = t > 255 ? 255 : t;
		t = (int)(i * Bk + Bb);
		mTableB[i] = t > 255 ? 255 : t;
	}
	mIsLUT = true;
}

