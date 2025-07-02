::关闭所有命令会显 也就是不在控制台显示bat脚本中的命令
@echo off

:: 进入 build 目录（通常是编译输出目录）
cd .\build

:: 删除 build 目录下的所有文件（不包括文件夹）
del /q *.*

:: 删除 build 目录下的所有子目录及其内容
for /d %%i in (*) do rmdir /s /q "%%i"

:: 使用 CMake 生成 MinGW Makefiles（构建文件），以准备 make 编译
cmake .. -G "MinGW Makefiles"

:: 使用 MinGW 的 make 工具编译项目
minw32-make

:: 编译完成后进入 bin 目录，准备运行程序
cd ..\bin

:: 运行生成的 boost.exe 程序
::boost.exe
