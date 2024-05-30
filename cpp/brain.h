#ifndef NEMO_BRAIN_H_
#define NEMO_BRAIN_H_

#include <stdint.h>

#include <map>
#include <random>
#include <string>
#include <vector>

// needed for namespace
#include <iostream>
#include <unordered_set>
#include <unordered_map>

namespace nemo {

struct Synapse {
  uint32_t neuron;    // 神经元索引
  float weight;       // 突触权重
};

struct Area {
  Area(uint32_t index, uint32_t n, uint32_t k) : index(index), n(n), k(k) {}

  const uint32_t index;             // 脑区索引
  const uint32_t n;                 // 脑区的总神经元数量
  const uint32_t k;                 // 激活的最大神经元数量，n/k 为脑区的 assembly 数量
  uint32_t support = 0;             // 当前激活的神经元数量
  bool is_fixed = false;            // 是否具有固定数量的激活神经元
  std::vector<uint32_t> activated;  // 激活的神经元索引
};

struct Fiber {
  Fiber(uint32_t from, uint32_t to) : from_area(from), to_area(to) {}

  const uint32_t from_area; // 起始脑区索引
  const uint32_t to_area;   // 目标脑区索引
  bool is_active = true;    // 是否激活
  std::vector<std::vector<Synapse>> outgoing_synapses;  // 起始脑区每个神经元到目标脑区每个神经元的突触集合
};

typedef std::unordered_map<std::string, std::unordered_set<std::string>> ProjectMap;

class Brain {
 public:
  Brain(float p, float beta, float max_weight, uint32_t seed);

  Area& AddArea(const std::string& name, uint32_t n, uint32_t k,
                bool recurrent = true, bool is_explicit = false);
  void AddStimulus(const std::string& name, uint32_t k);
  void AddFiber(const std::string& from, const std::string& to,
                bool bidirectional = false);

  Area& GetArea(const std::string& name);
  const Area& GetArea(const std::string& name) const;
  Fiber& GetFiber(const std::string& from, const std::string& to);
  const Fiber& GetFiber(const std::string& from, const std::string& to) const;

  void InhibitAll();
  void InhibitFiber(const std::string& from, const std::string& to);
  void ActivateFiber(const std::string& from, const std::string& to);
  void InitProjection(const ProjectMap& graph);

  void ActivateArea(const std::string& name, uint32_t assembly_index);

  void SimulateOneStep(bool update_plasticity = true);
  void Project(const ProjectMap& graph, uint32_t num_steps,
               bool update_plasticity = true);

  void ReadAssembly(const std::string& name, size_t& index, size_t& overlap);

  void SetLogLevel(int log_level) { log_level_ = log_level; }
  void LogGraphStats();
  void LogActivated(const std::string& area_name);

 private:
  void ComputeKnownActivations(const Area& to_area,
                               std::vector<Synapse>& activations);
  void GenerateNewCandidates(const Area& to_area, uint32_t total_k,
                             std::vector<Synapse>& activations);
  void ConnectNewNeuron(Area& area,
                        uint32_t num_synapses_from_activated,
                        uint32_t& total_synapses_from_non_activated);
  void ChooseSynapsesFromActivated(const Area& area,
                                   uint32_t num_synapses);
  void ChooseSynapsesFromNonActivated(const Area& area,
                                      uint32_t& total_synapses);
  void ChooseOutgoingSynapses(const Area& area);
  void UpdatePlasticity(Area& to_area,
                        const std::vector<uint32_t>& new_activated);

 protected:
  std::mt19937 rng_;
  int log_level_ = 0;

  const float p_;                                           // 神经元激活概率
  const float beta_;                                        // 更新权重
  const float learn_rate_;                                  // 学习率：1+beta_
  const float max_weight_;                                  // 最大权重
  std::vector<Area> areas_;                                 // 脑区集合，下标为 Area::index
  std::vector<Fiber> fibers_;                               // 纤维束集合，下标从 incoming_fibers_ 和 outgoing_fibers_ 中获取
  std::vector<std::vector<uint32_t>> incoming_fibers_;      // areas_ 的每个脑区的输入纤维束，下标为 Area::index
  std::vector<std::vector<uint32_t>> outgoing_fibers_;      // areas_ 的每个脑区的输出纤维束，下标为 Area::index
  std::map<std::string, uint32_t> area_by_name_;            // 脑区名称到脑区索引的映射
  std::vector<std::string> area_name_;                      // areas_ 每个脑区的名称，下标为 Area::index
  uint32_t step_ = 0;                                       // 当前步数
};

}  // namespace nemo

#endif // NEMO_BRAIN_H_
