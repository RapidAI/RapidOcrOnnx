#ifdef __CLIB__

#include "OcrLiteCApi.h"
#include "OcrLite.h"

extern "C"
{
typedef struct {
    OcrLite OcrObj;
    std::string strRes;
} OCR_OBJ;

_QM_OCR_API OCR_HANDLE
OcrInit(const char *szDetModel, const char *szClsModel, const char *szRecModel, const char *szKeyPath, int nThreads) {

    OCR_OBJ *pOcrObj = new OCR_OBJ;
    if (pOcrObj) {
        pOcrObj->OcrObj.setNumThread(nThreads);

        pOcrObj->OcrObj.initModels(szDetModel, szClsModel, szRecModel, szKeyPath);

        return pOcrObj;
    } else {
        return nullptr;
    }

}

_QM_OCR_API OCR_BOOL
OcrDetect(OCR_HANDLE handle, const char *imgPath, const char *imgName, OCR_PARAM *pParam) {

    OCR_OBJ *pOcrObj = (OCR_OBJ *) handle;
    if (!pOcrObj)
        return FALSE;

    OCR_PARAM Param = *pParam;
    if (Param.padding == 0)
        Param.padding = 50;

    if (Param.maxSideLen == 0)
        Param.maxSideLen = 1024;

    if (Param.boxScoreThresh == 0)
        Param.boxScoreThresh = 0.6;

    if (Param.boxThresh == 0)
        Param.boxThresh = 0.3f;

    if (Param.unClipRatio == 0)
        Param.unClipRatio = 2.0;

    if (Param.doAngle == 0)
        Param.doAngle = 1;

    if (Param.mostAngle == 0)
        Param.mostAngle = 1;

    OcrResult result = pOcrObj->OcrObj.detect(imgPath, imgName, Param.padding, Param.maxSideLen,
                                              Param.boxScoreThresh, Param.boxThresh, Param.unClipRatio,
                                              Param.doAngle != 0, Param.mostAngle != 0);
    if (result.strRes.length() > 0) {
        pOcrObj->strRes = result.strRes;
        return TRUE;
    } else
        return FALSE;
}

_QM_OCR_API OCR_BOOL
OcrDetectInput(OCR_HANDLE handle, OCR_INPUT *input, OCR_PARAM *pParam, OCR_RESULT *ocrResult) {

    OCR_OBJ *pOcrObj = (OCR_OBJ *) handle;
    if (!pOcrObj)
        return FALSE;

    OCR_PARAM Param = *pParam;
    if (Param.padding == 0)
        Param.padding = 50;

    if (Param.maxSideLen == 0)
        Param.maxSideLen = 1024;

    if (Param.boxScoreThresh == 0)
        Param.boxScoreThresh = 0.6;

    if (Param.boxThresh == 0)
        Param.boxThresh = 0.3f;

    if (Param.unClipRatio == 0)
        Param.unClipRatio = 2.0;

    if (Param.doAngle == 0)
        Param.doAngle = 1;

    if (Param.mostAngle == 0)
        Param.mostAngle = 1;
    OcrResult result;
    if(input->dataLength == 0) {
        return FALSE;
    }

    if(input->type == 0){
        if(input->channels == 0){
            return FALSE;
        }
        result = pOcrObj->OcrObj.detectBitmap(input->data,input->width,input->height, input->channels, Param.padding, Param.maxSideLen,
                                                        Param.boxScoreThresh, Param.boxThresh, Param.unClipRatio,
                                                        Param.doAngle != 0, Param.mostAngle != 0);
    }

    if(input->type == 1){
        result= pOcrObj->OcrObj.detectImageBytes(input->data,input->dataLength, input->channels >= 3 ? 0 : 1, Param.padding, Param.maxSideLen,
                                                 Param.boxScoreThresh, Param.boxThresh, Param.unClipRatio,
                                                 Param.doAngle != 0, Param.mostAngle != 0);
    }

    if (result.strRes.length() > 0) {
        ocrResult->dbNetTime = result.dbNetTime;
        ocrResult->detectTime = result.detectTime;
        ocrResult->textBlocksLength = result.textBlocks.size();
        // 计算所需内存大小
        size_t count = result.textBlocks.size();

       // 分配足够大的内存块
        auto *rawArray = static_cast<TEXT_BLOCK*>(calloc(count, sizeof(TEXT_BLOCK)));
        for (size_t i = 0; i < count; i++) {
            TextBlock textBlock = result.textBlocks[i];

            rawArray[i].boxScore = textBlock.boxScore;
            rawArray[i].angleIndex = textBlock.angleIndex;
            rawArray[i].angleScore = textBlock.angleScore;
            rawArray[i].angleTime = textBlock.angleTime;
            auto* charScore = static_cast<float*>(calloc(textBlock.charScores.size(), sizeof(float)));
            std::copy(textBlock.charScores.begin(), textBlock.charScores.end(), charScore);
            rawArray[i].charScores = charScore;
            rawArray[i].charScoresLength = textBlock.charScores.size();
            auto * boxPoint= static_cast<OCR_POINT*>(calloc(textBlock.boxPoint.size(), sizeof (OCR_POINT)));
            for(size_t boxPointIdx = 0; boxPointIdx < textBlock.boxPoint.size(); boxPointIdx++){
                boxPoint[boxPointIdx].x = textBlock.boxPoint[boxPointIdx].x;
                boxPoint[boxPointIdx].y = textBlock.boxPoint[boxPointIdx].y;
            }
            rawArray[i].boxPoint = boxPoint;
            rawArray[i].boxPointLength = textBlock.boxPoint.size();
            auto* text = static_cast<uint8_t*>(calloc(textBlock.text.size(), sizeof (uint8_t)));
            std::copy(textBlock.text.begin(), textBlock.text.end(), text);
            rawArray[i].text = text;
            rawArray[i].textLength = textBlock.text.size() + 1;
            rawArray[i].crnnTime = textBlock.crnnTime;
            rawArray[i].blockTime = textBlock.blockTime;
        }
        ocrResult->textBlocks = rawArray;
        return TRUE;
    } else
        return FALSE;
}

_QM_OCR_API int OcrGetLen(OCR_HANDLE handle) {
    OCR_OBJ *pOcrObj = (OCR_OBJ *) handle;
    if (!pOcrObj)
        return 0;
    return pOcrObj->strRes.size() + 1;
}

_QM_OCR_API OCR_BOOL OcrGetResult(OCR_HANDLE handle, char *szBuf, int nLen) {
    OCR_OBJ *pOcrObj = (OCR_OBJ *) handle;
    if (!pOcrObj)
        return FALSE;

    if (nLen > pOcrObj->strRes.size()) {
        strncpy(szBuf, pOcrObj->strRes.c_str(), pOcrObj->strRes.size());
        szBuf[pOcrObj->strRes.size() - 1] = 0;
    }

    return pOcrObj->strRes.size();
}

_QM_OCR_API void OcrDestroy(OCR_HANDLE handle) {
    OCR_OBJ *pOcrObj = (OCR_OBJ *) handle;
    if (pOcrObj)
        delete pOcrObj;
}

};
#endif

