# Code for A Biologically Plausible Parser

基于论文 [A Biologically Plausible Parser](https://arxiv.org/abs/2108.02189) 伪代码及[论文仓库](https://github.com/dmitropolsky/assemblies) 实现自然语言的依赖解析。 

## Requirements
* c++17
* GCC 7.5
* cmake 3.14
* linux only

## Usage
* 正确性测试：
    ```shell
    cd test
    cmake -S . -B build
    cmake --build build
    cd build && ctest
    ```
    > 使用 `ctest -V` 可查看每个句子的依赖解析结果
* 性能测试
    ```shell
    cd performance
    cmake -S . -B build
    cmake --build build
    cd build && ./performance_test
    ```

## References
```
@article{mitropolsky2021biologically,
  title={A biologically plausible parser},
  author={Mitropolsky, Daniel and Collins, Michael J and Papadimitriou, Christos H},
  journal={Transactions of the Association for Computational Linguistics},
  year={2021},
}
```