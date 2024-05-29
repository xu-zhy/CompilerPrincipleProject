#ifndef NEMO_PARSER_H_
#define NEMO_PARSER_H_

#include "brain.h"
#include <vector>
#include <variant>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

// needed for namespace
#include <iostream>
#include <string>

namespace nemo {

// BrainAreas
const std::string LEX = "LEX";
const std::string DET = "DET";
const std::string SUBJ = "SUBJ";
const std::string OBJ = "OBJ";
const std::string VERB = "VERB";
const std::string PREP = "PREP";
const std::string PREP_P = "PREP_P";
const std::string ADJ = "ADJ";
const std::string ADVERB = "ADVERB";

// Fixed area stats for explicit areas
const int LEX_SIZE = 20;
const int LEX_SIZE = 2;

// Actions
const std::string DISINHIBIT = "DISINHIBIT";
const std::string INHIBIT = "INHIBIT";
const std::string ACTIVATE_ONLY = "ACTIVATE_ONLY";
const std::string CLEAR_DET = "CLEAR_DET";

const std::vector<std::string> AREAS = {LEX, DET, SUBJ, OBJ, VERB, ADJ, ADVERB, PREP, PREP_P};
const std::vector<std::string> EXPLICIT_AREAS = {LEX};
const std::vector<std::string> RECURRENT_AREAS = {SUBJ, OBJ, VERB, ADJ, ADVERB, PREP, PREP_P};

struct AreaRule {
  std::string action;
  std::string area;
  int index;

  AreaRule(std::string action, std::string area, int index)
        : action(action), area(area), index(index) {}
};

struct FiberRule {
  std::string action;
  std::string area1;
  std::string area2;
  int index;

  FiberRule(std::string action, std::string area1, std::string area2, int index)
        : action(action), area1(area1), area2(area2), index(index) {}
};

struct FiringRule {
  std::string action;
};

struct OtherRule {
  std::string action;
};

using Rule = std::variant<AreaRule, FiberRule>;

struct RuleSet {
    int index;
    std::vector<Rule> pre_rules;
    std::vector<Rule> post_rules;
};

RuleSet generic_noun(int index);
RuleSet generic_trans_verb(int index);
RuleSet generic_intrans_verb(int index);
RuleSet generic_copula(int index);
RuleSet generic_adverb(int index);
RuleSet generic_determinant(int index);
RuleSet generic_adjective(int index);
RuleSet generic_preposition(int index);
std::unordered_map<std::string, RuleSet> generateLexemeDict();

std::unordered_map<std::string, std::vector<std::string>> ENGLISH_READOUT_RULES = {
    {"VERB", {"LEX", "SUBJ", "OBJ", "PREP_P", "ADVERB", "ADJ"}},
    {"SUBJ", {"LEX", "DET", "ADJ", "PREP_P"}},
    {"OBJ", {"LEX", "DET", "ADJ", "PREP_P"}},
    {"PREP_P", {"LEX", "PREP", "ADJ", "DET"}},
    {"PREP", {"LEX"}},
    {"ADJ", {"LEX"}},
    {"DET", {"LEX"}},
    {"ADVERB", {"LEX"}},
    {"LEX", {}}
};

class ParserBrain : public Brain {
 public:
  std::unordered_map<std::string, RuleSet> lexeme_dict;
  std::vector<std::string> all_areas;
  std::vector<std::string> recurrent_areas;
  std::vector<std::string> initial_areas;
  std::unordered_map<std::string, std::vector<std::string>> readout_rules;
  std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<int>>> fiber_states;
  std::unordered_map<std::string, std::unordered_set<int>> area_states;
  // unchecked data type
  std::unordered_map<std::string, std::unordered_set<std::string>> activated_fibers;

  ParserBrain(float p, // float beta, float max_weight, uint32_t seed, 
              std::unordered_map<std::string, RuleSet> lexeme_dict = {}, 
              std::vector<std::string> all_areas = {}, 
              std::vector<std::string> recurrent_areas = {}, 
              std::vector<std::string> initial_areas = {}, 
              std::unordered_map<std::string, std::vector<std::string>> readout_rules = {});

  void initialize_states();

  void applyFiberRule(const FiberRule& rule);

  void applyAreaRule(const AreaRule& rule);

  void applyRule(const Rule& rule);

  void parse_project();

  void remember_fibers(const std::unordered_map<std::string, std::set<std::string>>& project_map);

  bool recurrent(const std::string& area);

  std::unordered_map<std::string, std::set<std::string>> getProjectMap();

  void activateWord(const std::string& area_name, const std::string& word);

  void activateIndex(const std::string& area_name, int index);

  std::string interpretAssemblyAsString(const std::string& area_name);

  std::string getWord(const std::string& area_name, double min_overlap = 0.7);

  std::unordered_map<std::string, std::set<std::string>> getActivatedFibers();
};

class ParserDebugger {
 public:
  ParserBrain& brain;
  std::vector<std::string> all_areas;
  std::vector<std::string> explicit_areas;

  ParserDebugger(ParserBrain& brain, 
                 const std::vector<std::string>& all_areas, 
                 const std::vector<std::string>& explicit_areas);

  void run();
  void peak();
};

void parse(std::string sentence="cats chase mice", float p=0.1, int LEX_k=20, 
	       int project_rounds=20, bool verbose=true, bool debug=false, int readout_method=2);

}  // namespace nemo

#endif // NEMO_BRAIN_H_