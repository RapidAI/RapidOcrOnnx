# 编译说明

### onnxruntime gpu(cuda下载)

1. [下载地址](https://github.com/microsoft/onnxruntime/releases)

* 仅支持Linux和Windows，仅支持x64
* Windows包名: onnxruntime-win-x64-gpu-版本号.zip
* Linux包名: onnxruntime-linux-x64-gpu-版本号.tgz
* Windows平台：把压缩包内的lib文件夹解压到windows-x64文件夹里
* Linux平台：把压缩包内的lib文件夹解压到linux文件夹里
* 创建include/onnxruntime/core/session，把压缩包内的所有.h文件解压到session文件夹里
* 目录结构如下

```
onnxruntime-gpu
├── linux
│   ├── include
│   │   └── onnxruntime
│   │       └── core
│   │           └── session
│   │               ├── cpu_provider_factory.h
│   │               ├── onnxruntime_c_api.h
│   │               ├── onnxruntime_cxx_api.h
│   │               ├── onnxruntime_cxx_inline.h
│   │               ├── onnxruntime_run_options_config_keys.h
│   │               ├── onnxruntime_session_options_config_keys.h
│   │               ├── provider_options.h
│   │               └── tensorrt_provider_factory.h
│   ├── lib
│   │   ├── libonnxruntime_providers_cuda.so
│   │   ├── libonnxruntime_providers_shared.so
│   │   ├── libonnxruntime_providers_tensorrt.so
│   │   ├── libonnxruntime.so -> libonnxruntime.so.1.12.1
│   │   └── libonnxruntime.so.1.12.1
│   └── OnnxRuntimeConfig.cmake
└── windows-x64
    ├── include
    │   └── onnxruntime
    │       └── core
    │           └── session
    │               ├── cpu_provider_factory.h
    │               ├── onnxruntime_c_api.h
    │               ├── onnxruntime_cxx_api.h
    │               ├── onnxruntime_cxx_inline.h
    │               ├── onnxruntime_run_options_config_keys.h
    │               ├── onnxruntime_session_options_config_keys.h
    │               ├── provider_options.h
    │               └── tensorrt_provider_factory.h
    ├── lib
    │   ├── onnxruntime.dll
    │   ├── onnxruntime.lib
    │   ├── onnxruntime.pdb
    │   ├── onnxruntime_providers_cuda.dll
    │   ├── onnxruntime_providers_cuda.lib
    │   ├── onnxruntime_providers_cuda.pdb
    │   ├── onnxruntime_providers_shared.dll
    │   ├── onnxruntime_providers_shared.lib
    │   ├── onnxruntime_providers_shared.pdb
    │   ├── onnxruntime_providers_tensorrt.dll
    │   ├── onnxruntime_providers_tensorrt.lib
    │   └── onnxruntime_providers_tensorrt.pdb
    └── OnnxRuntimeConfig.cmake

```

2. CUDA和cuDNN

* [CUDA下载地址](https://developer.nvidia.com/downloads)
* 捷径 https://developer.download.nvidia.com/compute/cuda/11.4.0/local_installers/cuda_11.4.0_470.42.01_linux.run
* [cuDNN下载地址](https://developer.nvidia.com/rdp/cudnn-archive)
* 根据onnxruntime官方文档https://onnxruntime.ai/docs/execution-providers/CUDA-ExecutionProvider.html
* onnxruntime v1.12，需要CUDA 11.4和cuDNN 8.2.4 (Linux) 8.2.2.26 (Windows)