set(OnnxRuntime_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include") 
include_directories(${OnnxRuntime_INCLUDE_DIRS}) 
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib) 
set(OnnxRuntime_LIBS onnxruntime onnxruntime_providers_cuda onnxruntime_providers_shared onnxruntime_providers_tensorrt) 
