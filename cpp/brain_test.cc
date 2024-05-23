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

Brain SetupOneStimulus(uint32_t n, uint32_t k, float p, float beta,
                       bool is_explicit = false) {
  Brain brain(p, beta, 10000.0, 7777);
  brain.AddStimulus("StimA", k);
  brain.AddArea("A", n, k, /*recurrent=*/true, is_explicit);
  brain.AddFiber("StimA", "A");
  brain.SetLogLevel(kLogLevel);
  return brain;
}

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

std::set<std::string> AllAreas(
    const std::map<std::string, std::vector<std::string>>& graph) {
  std::set<std::string> areas;
  for (const auto& [from, edges] : graph) {
    areas.insert(from);
    for (const auto& to : edges) {
      areas.insert(to);
    }
  }
  return areas;
}

void Project(Brain& brain, const ProjectMap& graph,
             int steps, float convergence = 1.0) {
  std::map<std::string, std::vector<uint32_t>> prev_activated;
  std::set<std::string> all_areas = AllAreas(graph);
  brain.Project(graph, steps - 1);
  for (const auto& area_name : all_areas) {
    prev_activated[area_name] = brain.GetArea(area_name).activated;
  }
  brain.SimulateOneStep();
  for (const auto& area_name : all_areas) {
    const Area& area = brain.GetArea(area_name);
    ASSERT_GE(NumCommon(area.activated, prev_activated[area_name]),
              convergence * area.k);
  }
}

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

  ASSERT_LE(NumCommon(proj_A, proj_B), 2);

  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimA", {"A"}}, {"StimB", {"B"}},
           {"A", {"A", "C"}}, {"B", {"B","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_AB = brain.GetArea("C").activated;

  ASSERT_GE(NumCommon(proj_A, proj_AB), 90);
  ASSERT_GE(NumCommon(proj_B, proj_AB), 90);

  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimB", {"B"}}, {"B", {"B","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_B_postassoc = brain.GetArea("C").activated;
  ASSERT_GE(NumCommon(proj_A, proj_B_postassoc), 30);
  ASSERT_GE(NumCommon(proj_AB, proj_B_postassoc), 200);

  Project(brain,
          {{"StimA", {"A"}}, {"A", {"A","C"}}}, 1, 0.0);
  Project(brain,
          {{"StimA", {"A"}}, {"A", {"A","C"}}, {"C", {"C"}}}, 9);
  std::vector<uint32_t> proj_A_postassoc = brain.GetArea("C").activated;

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
  ASSERT_GE(NumCommon(brain.GetArea("B").activated, assembly_B), 0.95 * k);
}

}  // namespace
}  // namespace nemo
