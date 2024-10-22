#include "OcrLite.h"
#include "OcrLiteImpl.h"

OcrLite::OcrLite() {
    pImpl = new OcrLiteImpl();
}

OcrLite::~OcrLite() {
    delete pImpl;
}

void OcrLite::setNumThread(int numOfThread) {
    pImpl->setNumThread(numOfThread);
}

void OcrLite::initLogger(bool isConsole, bool isPartImg, bool isResultImg) {
    pImpl->initLogger(isConsole, isPartImg, isResultImg);
}

void OcrLite::enableResultTxt(const char *path, const char *imgName) {
    pImpl->enableResultTxt(path, imgName);
}

void OcrLite::setGpuIndex(int gpuIndex) {
    pImpl->setGpuIndex(gpuIndex);
}

bool OcrLite::initModels(const std::string &detPath, const std::string &clsPath,
                         const std::string &recPath, const std::string &keysPath) {
    return pImpl->initModels(detPath, clsPath, recPath, keysPath);
}

void OcrLite::Logger(const char *format, ...) {
    if (!(pImpl->isOutputConsole || pImpl->isOutputResultTxt)) return;
    char *buffer = (char *) malloc(8192);
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    if (pImpl->isOutputConsole) printf("%s", buffer);
    if (pImpl->isOutputResultTxt) fprintf(pImpl->resultTxt, "%s", buffer);
    free(buffer);
}

OcrResult OcrLite::detect(const char *path, const char *imgName,
                          int padding, int maxSideLen,
                          float boxScoreThresh, float boxThresh, float unClipRatio, bool doAngle, bool mostAngle) {
    return pImpl->detect(path, imgName, padding, maxSideLen, boxScoreThresh, boxThresh, unClipRatio, doAngle, mostAngle);
}

OcrResult OcrLite::detect(const cv::Mat &mat,
                          int padding, int maxSideLen,
                          float boxScoreThresh, float boxThresh, float unClipRatio, bool doAngle, bool mostAngle) {
    return pImpl->detect(mat, padding, maxSideLen, boxScoreThresh, boxThresh, unClipRatio, doAngle, mostAngle);
}
