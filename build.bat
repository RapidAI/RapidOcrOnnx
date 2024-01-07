@ECHO OFF
chcp 65001
cls
@SETLOCAL
echo "========请先参考README.md准备好编译环境========"
echo.

echo "========编译选项========"
echo "请注意：项目默认使用Release库，除非您自行编译Debug版的Onnxruntime和Opencv，否则请不要选择Debug编译"
echo "请输入编译选项并回车: 1)Release, 2)Debug"
set BUILD_TYPE=Release
set /p flag=
if %flag% == 1 (set BUILD_TYPE=Release)^
else if %flag% == 2 (set BUILD_TYPE=Debug)^
else (echo 输入错误！Input Error!)
echo.

echo "请注意：如果选择2)JNI动态库时，必须安装配置Oracle JDK"
echo "请选择编译输出类型并回车: 1)BIN可执行文件，2)JNI动态库，3)C动态库"
set /p flag=
if %flag% == 1 (set BUILD_OUTPUT="BIN")^
else if %flag% == 2 (set BUILD_OUTPUT="JNI")^
else if %flag% == 3 (set BUILD_OUTPUT="CLIB")^
else (echo 输入错误！Input Error!)
echo.

echo "引用库类型: 1)静态CRT(mt), 2)动态CRT(md)"
echo "注意：范例工程默认集成mt版库"
set /p flag=
if %flag% == 1 (
    set MT_ENABLED="True"
)^
else (set MT_ENABLED="False")
echo.

echo "onnxruntime: 1)CPU(默认), 2)GPU(cuda)"
echo "注意：范例工程默认集成CPU版，CUDA版仅支持x64且需下载"
set /p flag=
if %flag% == 1 (set ONNX_TYPE="CPU")^
else if %flag% == 2 (set ONNX_TYPE="CUDA")^
else (echo 输入错误！Input Error!)
echo.

echo "VS版本: 1)vs2019-x64, 2)vs2019-x86, 3)vs2022-x64, 4)vs2022-x86"
set BUILD_CMAKE_T="v142"
set BUILD_CMAKE_A="x64"
set /p flag=
if %flag% == 1 (
    set BUILD_CMAKE_T="v142"
    set BUILD_CMAKE_A="x64"
)^
else if %flag% == 2 (
    set BUILD_CMAKE_T="v142"
    set BUILD_CMAKE_A="Win32"
)^
else if %flag% == 3 (
    set BUILD_CMAKE_T="v143"
    set BUILD_CMAKE_A="x64"
)^
else if %flag% == 4 (
    set BUILD_CMAKE_T="v143"
    set BUILD_CMAKE_A="Win32"
)^
else (echo 输入错误！Input Error!)
echo.

mkdir win-%BUILD_OUTPUT%-%ONNX_TYPE%-%BUILD_CMAKE_A%
pushd win-%BUILD_OUTPUT%-%ONNX_TYPE%-%BUILD_CMAKE_A%

cmake -T "%BUILD_CMAKE_T%,host=x64" -A %BUILD_CMAKE_A% ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DOCR_OUTPUT=%BUILD_OUTPUT% ^
  -DOCR_BUILD_CRT=%MT_ENABLED% -DOCR_ONNX=%ONNX_TYPE% ..
cmake --build . --config %BUILD_TYPE% -j %NUMBER_OF_PROCESSORS%
cmake --build . --config %BUILD_TYPE% --target install

popd
GOTO:EOF

@ENDLOCAL
