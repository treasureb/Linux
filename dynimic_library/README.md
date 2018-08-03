## 动态连接库的使用

1. 编译.o文件时,加上-fPIC选项生成与位置无关的代码
2. 链接时,加上-shared选项,表示生成动态链接库

## linux下动态链接的过程

1. Linux下是通过/etc/ld.so.cache文件搜寻要链接的动态库
2. /etc/ld.so.cache是ldconfig程序读取/etc/ld.so.conf文件生成的
3. linxu下的动态间接库都在/etc/lib目录下

## 如何加载动态链接库

1. 将自己实现的.so文件路径加在/etc/ld.so.conf中,再以root权限运行ldconfig,更新/etc/ld.so.cache即可
2. 使用LD_LIBRARY_PATH制定环境变量
