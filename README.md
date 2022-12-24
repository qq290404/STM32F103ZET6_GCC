# STM32F103ZET6
## 简介
本项目已集成`python 2.7`、`Make`和部分`Linux`命令，用户在`menuconfig`中，只需要配置openocd和编译工具链的路径即可。
## 开发环境
- 操作系统：win10
- 编译器：gcc-arm-none-eabi
- 烧录器：openocd + stlink
- 开发板：神舟III号
## 编译前的准备
使用`make menuconfig`命令，修改`STM32 Configuration  -> Path Settings`里对应的路径即可。

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
