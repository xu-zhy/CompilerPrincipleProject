# Usage
下载 google test: https://github.com/google/googletest/archive/v1.14.0.zip  
安装如下：
```shell
cd googletest-1.14.0
cmake CMakeLists.txt
make
sudo make install
# 使用 google test 样例测试
cd googletest/samples
g++ ../src/gtest_main.cc sample1.cc sample1_unittest.cc -o test -lgtest -lgmock -lpthread -std=c++14
./test
```
> googletest 安装具体参考：https://blog.csdn.net/wdcyf15/article/details/108855960  
  如果遇到 cmake 版本问题（>=3.13），升级 cmake 参考[文章](https://blog.csdn.net/Dontla/article/details/120537184)的后半部分，不需要删除原 cmake

编译运行程序
```shell
cmake CMakeLists.txt
```

# TODO