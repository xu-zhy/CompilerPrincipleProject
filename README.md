# Updates
> 如果进行了重要更改，需要在此写清时间线和内容，例如对非 parser 代码的更改
---

+ 5.30
1. 修改了 brain.h 的 ```typedef std::unordered_map<std::string, std::unordered_set<std::string>> ProjectMap;``` 部分的定义，将原先的 map 和 vector 改成 un_map/set 来符合 python 写法。
2. 修改了 brain_test.cc 的 AllAreas 和 Project 函数，将 map/set 转化成对应的 unordered 形式

# TODO
> 目前的任务和未来的计划
---

### XZY
1. [DONE] 阅读 AC 代码并添加注释
2. [DONE] 定义 parser 代码框架
3. [TODO] 使用 GoogleTest 编写测试文件

### KJX

0. ~~补全 parser.cc 基础框架~~ 5.28
1. ~~ParserBrain 基础定义~~ 5.29
2. ~~EnglishParserBrain 基础定义~~
3. 两个类参数数据类型的确定 ProjectMap
4. ~~两个不同rule的判断和转化~~ 5.29
5. ~~parse_project 函数和 ProjectMap 模块类型~~ 5.30
6. ~~area_by_name Brain类~~ 5.30
7. activateWord 的 ActivateArea
8. EnglishParserBrain 构造函数的 update_plasticities 

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

### 2 DET_SIZE - [FIXED]
written by KJX

python parser.py 代码在 551 行出现了一个未定义常量 DET_SIZE，暂时没找到定义

### 3 Namespace - [FIXED]
需要在 brain.h 基础路径下加上：
```c++
// needed for namespace
#include <iostream>
```
这样就不会报错无法使用限定名或 std::vector 未定义的情况

### 4 pptree
parser.py 使用 conda 安装 pptree 可见：
https://github.com/conda-forge/pptree-feedstock

### 5 fix_assembly
在 brain.py 40 行，是检查集合是否被冻结的参数
但是 cc 里面没有定义，使用位置在 activateWord 里，因此目前暂时不考虑

# Devotion
> 总结自己的全部贡献，包括论文环节和代码环节，方便实验报告汇总
---

### XZY

### KJX

### XJW


# AC Usage
> AC 模块的基础用法，仅仅用于底层的过程展示
```shell
cd cpp
cmake -S . -B build
cmake --build build
cd build && ctest
```