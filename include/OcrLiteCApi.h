#ifdef __cplusplus
#ifndef __OCR_LITE_C_API_H__
#define __OCR_LITE_C_API_H__
#include "stdint.h"
extern "C"
{

#ifdef WIN32
#ifdef __CLIB__
#define _QM_OCR_API __declspec(dllexport)
#else
#define _QM_OCR_API __declspec(dllimport)
#endif
#else
#define _QM_OCR_API
#endif

typedef void *OCR_HANDLE;
typedef char OCR_BOOL;

#ifndef NULL
#define NULL 0
#endif
#define TRUE 1
#define FALSE 0

typedef struct __ocr_param {
    int padding;
    int maxSideLen;
    float boxScoreThresh;
    float boxThresh;
    float unClipRatio;
    int doAngle; // 1 means do
    int mostAngle; // 1 means true
} OCR_PARAM;
typedef struct {
    double x;
    double y;
} OCR_POINT;
typedef struct {
    uint8_t *data;
    int type;
    int channels;
    int width;
    int height;
    long dataLength;
} OCR_INPUT;
typedef struct {
    OCR_POINT* boxPoint;
    float boxScore;
    int angleIndex;
    float angleScore;
    double angleTime;
    uint8_t *text;
    float *charScores;
    unsigned long long charScoresLength;
    unsigned long long boxPointLength;
    unsigned long long textLength;
    double crnnTime;
    double blockTime;
} TEXT_BLOCK;
typedef struct {
    double dbNetTime;
    TEXT_BLOCK *textBlocks;
    unsigned long long textBlocksLength;
    double detectTime;
} OCR_RESULT;

/*
By default, nThreads should be the number of threads
*/
_QM_OCR_API OCR_HANDLE
OcrInit(const char *szDetModel, const char *szClsModel, const char *szRecModel, const char *szKeyPath, int nThreads);

_QM_OCR_API OCR_BOOL
OcrDetect(OCR_HANDLE handle, const char *imgPath, const char *imgName, OCR_PARAM *pParam);

_QM_OCR_API OCR_BOOL
OcrDetectInput(OCR_HANDLE handle, OCR_INPUT *input, OCR_PARAM *pParam, OCR_RESULT *ocrResult);

_QM_OCR_API int OcrGetLen(OCR_HANDLE handle);

_QM_OCR_API OCR_BOOL OcrGetResult(OCR_HANDLE handle, char *szBuf, int nLen);

_QM_OCR_API void OcrDestroy(OCR_HANDLE handle);

};
#endif //__OCR_LITE_C_API_H__
#endif //__cplusplus
