# AC Usage
> AC 模块的基础用法，仅仅用于底层的过程展示
```shell
cd cpp
cmake -S . -B build
cmake --build build
cd build && ctest
```

# TODO
> 目前的任务和未来的计划
---

### XZY
1. [DONE] 阅读 AC 代码并添加注释
2. [DONE] 定义 parser 代码框架
3. [TODO] 使用 GoogleTest 编写测试文件
### KJX

1. 转换 python 代码中
2. 尝试使用 parse 模块和 google 目标网站来检查 C++ 代码可能存在的问题

### XJW



# Notes
> 代码过程存在的问题和一些提醒，或者一些值得注意的地方
---

### 1 Exception
@XJW

written by KJX

由于我实现时使用了:
```c++
getWord 函数 | throw std::runtime_error("Cannot get word because no assembly in " + area_name);
```
的异常语句来和 python 的实现对齐:
```py
436 | raise Exception("Cannot get word because no assembly in " + area_name)
```
因此主函数 parse 调用时可能需要写成这样:
```c++
try {
        parse();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
```

### 2 DET_SIZE-[FIXED]
written by KJX

python parser.py 代码在 551 行出现了一个未定义常量 DET_SIZE，暂时没找到定义

# Devotion
> 总结自己的全部贡献，包括论文环节和代码环节，方便实验报告汇总
---

### XZY

### KJX

### XJW

