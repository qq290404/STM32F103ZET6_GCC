# STM32F103ZET6
## 开发环境
- 操作系统：win10
- 编译器：gcc-arm-none-eabi
- 烧录器：openocd + stlink
- 开发板：神舟III号
## 编译前的准备
### 配置开发环境路径
需要添加`python2.7`,`openocd`,`toolchain`,`make`,`linux command`路径。
新建`evn.bat`文件，添加如下内容，对应的路径需要根据实际来修改
```bat
set PYTHON_PATH=D:\Python 2.7;D:\Python 2.7\Scripts
set LINUX_PATH=F:\code\stm32\STM32F103ZET6\tools\linux\bin
set MAKE_PATH=F:\code\stm32\STM32F103ZET6\tools\Make
set TOOLCHAIN_PATH=F:\code\stm32\STM32F103ZET6\tools\toolchain\gcc-arm-none-eabi\bin
set OPENOCD_PATH=F:\code\stm32\STM32F103ZET6\tools\OpenOCD\bin
set Project_Dependence_Path=%PYTHON_PATH%;%LINUX_PATH%;%MAKE_PATH%;%TOOLCHAIN_PATH%;%OPENOCD_PATH%
```
## 开发流程
运行根目录下的`gccl2.bat`, 输入对应的指令。
### 编译
```bash
    make all
```
### 清除
```bash
    make clean
```
### 下载
```bash
    make download
```
### 全编译
```bash
    make rebuild
```
### menuconfig
```bash
    make menuconfig
```
