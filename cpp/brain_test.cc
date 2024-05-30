#include "brain.h"

#include <stdint.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include "brain_util.h"

namespace nemo {
namespace {

constexpr int kLogLevel = 0;

/**
 * @brief 从激活的神经元中随机抽样
 * 
 * @param activated: 激活的神经元索引
 * @param alpha: 抽样比例 
 * @param seed: 随机数种子 
 */
void Subsample(std::vector<uint32_t>& activated, float alpha, uint32_t seed) {
  std::mt19937 rng(seed);
  uint32_t new_k = alpha * activated.size();
  std::vector<uint32_t> new_activated(new_k);
  std::vector<uint8_t> selected(activated.size());
  std::uniform_int_distribution<> u(0, activated.size() - 1);
  for (uint32_t i = 0; i < new_k; ++i) {
    uint32_t next;
    while (selected[next = u(rng)]) {}
    selected[next] = 1;
    new_activated[i] = activated[next];
  }
  std::swap(activated, new_activated);
}

/**
 * @brief 设置一个刺激（无法翻译，大致就是只有一个 fix 的脑区和一个待更新的脑区）
 * 
 * @param n: 神经元数量
 * @param k: 激活的最大神经元数量 
 * @param p: 激活概率 
 * @param beta: 赫布可塑性参数 
 * @param is_explicit: 是否显式 
 * @return Brain: 设置的大脑对象 
 */
Brain SetupOneStimulus(uint32_t n, uint32_t k, float p, float beta,
                       bool is_explicit = false) {
  Brain brain(p, beta, 10000.0, 7777);
  brain.AddStimulus("StimA", k);
  brain.AddArea("A", n, k, /*recurrent=*/true, is_explicit);
  brain.AddFiber("StimA", "A");
  brain.SetLogLevel(kLogLevel);
  return brain;
}

/**
 * @brief 设置两个刺激（无法翻译，大致就是两个 fix 的脑区和两个待更新的脑区）
 * 
 * @param n: 神经元数量 
 * @param k: 激活的最大神经元数量 
 * @param p: 激活概率 
 * @param beta: 赫布可塑性参数 
 * @param is_explicit: 是否显式 
 * @return Brain: 设置的大脑对象 
 */
Brain SetupTwoStimuli(uint32_t n, uint32_t k, float p, float beta,
                      bool is_explicit = false) {
  Brain brain(p, beta, 10000.0, 7777);
  brain.AddStimulus("StimA", k);
  brain.AddStimulus("StimB", k);
  brain.AddArea("A", n, k, /*recurrent=*/true, is_explicit);
  brain.AddArea("B", n, k, /*recurrent=*/true, is_explicit);
  brain.AddFiber("StimA", "A");
  brain.AddFiber("StimB", "B");
  brain.SetLogLevel(kLogLevel);
  return brain;
}

/**
 * @brief 计算所有脑区的集合
 * 
 * @param graph: 脑区图
 * @return std::set<std::string>: 脑区集合
 */
std::unordered_set<std::string> AllAreas(
    const ProjectMap& graph) {
  std::unordered_set<std::string> areas;
  for (const auto& [from, edges] : graph) {
    areas.insert(from);
    for (const auto& to : edges) {
      areas.insert(to);
    }
  }
  return areas;
}

/**
 * @brief 模拟脑区的投影
 * 
 * @param brain: 大脑对象
 * @param graph: 脑区图
 * @param steps: 模拟步数 
 * @param convergence: 收敛率 
 */
void Project(Brain& brain, const ProjectMap& graph,
             int steps, float convergence = 1.0) {
  std::unordered_map<std::string, std::vector<uint32_t>> prev_activated;
  std::unordered_set<std::string> all_areas = AllAreas(graph);
  // 先模拟 steps-1 步，然后记录激活神经元
  brain.Project(graph, steps - 1);
  for (const auto& area_name : all_areas) {
    prev_activated[area_name] = brain.GetArea(area_name).activated;
  }
  // 再模拟最后一步，检查激活脑区是否收敛
  brain.SimulateOneStep();
  for (const auto& area_name : all_areas) {
    const Area& area = brain.GetArea(area_name);
    ASSERT_GE(NumCommon(area.activated, prev_activated[area_name]),
              convergence * area.k);
  }
}

/*
  下面是使用 google test 框架进行测试
  分别测试了投影、显式投影、完成、关联、合并等操作
  关于这些操作的意思，见论文:
  Papadimitriou et al.-2020-Brain computation by assemblies of neurons
  info.md 有部分总结
  不过似乎不重要
*/
TEST(BrainTest, TestProjection) {
  Brain brain = SetupOneStimulus(1000000, 1000, 0.001, 0.05);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A"}}}, 25, 0.999);
}

TEST(BrainTest, TestExplicitProjection) {
  Brain brain = SetupOneStimulus(250000, 500, 0.01, 0.05,
                                 /*is_explicit=*/true);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A"}}}, 25);
}

TEST(BrainTest, TestCompletion) {
  Brain brain = SetupOneStimulus(100000, 317, 0.05, 0.05);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A"}}}, 25);
  std::vector<uint32_t> prev_assembly = brain.GetArea("A").activated;
  // Recude A's assembly by half.
  Subsample(brain.GetArea("A").activated, 0.5, 1777);
  // Check that A recovers most of its previous assembly after 5 steps.
  Project(brain, {{"A", {"A"}}}, 5);
  EXPECT_GE(NumCommon(prev_assembly, brain.GetArea("A").activated), 310);
}

TEST(BrainTest, TestAssociation) {
  const int n = 100000;
  const int k = 317;
  Brain brain = SetupTwoStimuli(n, k, 0.05, 0.1);
  brain.AddArea("C", n, k);
  brain.AddFiber("A", "C");
  brain.AddFiber("B", "C");

  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}}, {"A", {"A"}}, {"B", {"B"}}}, 10);
  Project(brain,
          {{"StimA", {"A"}}, {"A", {"A","C"}}, {"C", {"C"}}}, 10);
  std::vector<uint32_t> proj_A = brain.GetArea("C").activated;

  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_B = brain.GetArea("C").activated;

  // 在没有关联的情况下，两个不同刺激源形成的神经元集合是相互独立的
  ASSERT_LE(NumCommon(proj_A, proj_B), 2);

  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_AB = brain.GetArea("C").activated;

  // 在关联的情况下，两个不同刺激源形成的神经元集合是相互重叠的
  ASSERT_GE(NumCommon(proj_A, proj_AB), 90);
  ASSERT_GE(NumCommon(proj_B, proj_AB), 90);

  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_B_postassoc = brain.GetArea("C").activated;

  // 关联操作在后续投射中保持了部分共同神经元
  ASSERT_GE(NumCommon(proj_A, proj_B_postassoc), 30);
  ASSERT_GE(NumCommon(proj_AB, proj_B_postassoc), 200);

  Project(brain,
          {{"StimA", {"A"}}, {"A", {"A","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimA", {"A"}}, {"A", {"A","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_A_postassoc = brain.GetArea("C").activated;

  // 关联操作在后续投射中保持了部分共同神经元
  ASSERT_GE(NumCommon(proj_B, proj_A_postassoc), 30);
  ASSERT_GE(NumCommon(proj_AB, proj_A_postassoc), 200);
}

TEST(BrainTest, TestMerge) {
  const int n = 100000;
  const int k = 317;
  Brain brain = SetupTwoStimuli(n, k, 0.01, 0.05);
  brain.AddArea("C", n, k);
  brain.AddFiber("A", "C", /*bidirectional=*/true);
  brain.AddFiber("B", "C", /*bidirectional=*/true);

  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B", "C"}}}, 1, 0.0);
  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B", "C"}}, {"C", {"A", "B", "C"}}}, 50);
  ASSERT_LE(brain.GetArea("A").support, 10 * k);
  ASSERT_LE(brain.GetArea("B").support, 10 * k);
  ASSERT_LE(brain.GetArea("C").support, 20 * k);
  std::vector<uint32_t> assembly_B = brain.GetArea("B").activated;

  Project(brain, {{"StimA", {"A"}}}, 1, 0.0);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A", "C"}}}, 1, 0.0);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A", "C"}}, {"C", {"B", "C"}}},
          1, 0.0);
  Project(brain, {{"StimA", {"A"}}, {"A", {"A", "C"}}, {"C", {"B", "C"}},
                  {"B", {"B"}}}, 50);

  // 在合并操作后，B 区的激活神经元集合应该与之前的集合有很大重叠
  ASSERT_GE(NumCommon(brain.GetArea("B").activated, assembly_B), 0.95 * k);
}

}  // namespace
}  // namespace nemo