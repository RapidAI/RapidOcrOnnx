@ECHO OFF
chcp 65001
cls
@SETLOCAL

IF "%1"=="" (
    echo input VS_VER none, use v142
	set VS_VER="v142"
)^
ELSE (
	echo input VS_VER:%1
    set VS_VER="%1"
)

mkdir win-BIN-CPU-x64
pushd win-BIN-CPU-x64
cmake -T "%VS_VER%,host=x64" -A "x64" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="BIN" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-BIN-CPU-Win32
pushd win-BIN-CPU-Win32
cmake -T "%VS_VER%,host=x64" -A "Win32" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="BIN" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-JNI-CPU-x64
pushd win-JNI-CPU-x64
cmake -T "%VS_VER%,host=x64" -A "x64" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="JNI" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-JNI-CPU-Win32
pushd win-JNI-CPU-Win32
cmake -T "%VS_VER%,host=x64" -A "Win32" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="JNI" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-CLIB-CPU-x64
pushd win-CLIB-CPU-x64
cmake -T "%VS_VER%,host=x64" -A "x64" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="CLIB" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-CLIB-CPU-Win32
pushd win-CLIB-CPU-Win32
cmake -T "%VS_VER%,host=x64" -A "Win32" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="CLIB" ^
  -DOCR_BUILD_CRT="True" -DOCR_ONNX="CPU" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

@ENDLOCAL
