#include "parser.h" 

namespace nemo {

RuleSet generic_noun(int index) {
  return {
      index,
      { // PRE_RULES
        FiberRule(DISINHIBIT, LEX, SUBJ, 0), 
        FiberRule(DISINHIBIT, LEX, OBJ, 0),
        FiberRule(DISINHIBIT, LEX, PREP_P, 0),
        FiberRule(DISINHIBIT, DET, SUBJ, 0),
        FiberRule(DISINHIBIT, DET, OBJ, 0),
        FiberRule(DISINHIBIT, DET, PREP_P, 0),
        FiberRule(DISINHIBIT, ADJ, SUBJ, 0),
        FiberRule(DISINHIBIT, ADJ, OBJ, 0),
        FiberRule(DISINHIBIT, ADJ, PREP_P, 0),
        FiberRule(DISINHIBIT, VERB, OBJ, 0),
        FiberRule(DISINHIBIT, PREP_P, PREP, 0),
        FiberRule(DISINHIBIT, PREP_P, SUBJ, 0),
        FiberRule(DISINHIBIT, PREP_P, OBJ, 0),
      },
      { // POST_RULES
        AreaRule(INHIBIT, DET, 0),
        AreaRule(INHIBIT, ADJ, 0),
        AreaRule(INHIBIT, PREP_P, 0),
        AreaRule(INHIBIT, PREP, 0),
        FiberRule(INHIBIT, LEX, SUBJ, 0),
        FiberRule(INHIBIT, LEX, OBJ, 0),
        FiberRule(INHIBIT, LEX, PREP_P, 0),
        FiberRule(INHIBIT, ADJ, SUBJ, 0),
        FiberRule(INHIBIT, ADJ, OBJ, 0),
        FiberRule(INHIBIT, ADJ, PREP_P, 0),
        FiberRule(INHIBIT, DET, SUBJ, 0),
        FiberRule(INHIBIT, DET, OBJ, 0),
        FiberRule(INHIBIT, DET, PREP_P, 0),
        FiberRule(INHIBIT, VERB, OBJ, 0),
        FiberRule(INHIBIT, PREP_P, PREP, 0),
        FiberRule(INHIBIT, PREP_P, VERB, 0),
        FiberRule(DISINHIBIT, LEX, SUBJ, 1),
        FiberRule(DISINHIBIT, LEX, OBJ, 1),
        FiberRule(DISINHIBIT, DET, SUBJ, 1),
        FiberRule(DISINHIBIT, DET, OBJ, 1),
        FiberRule(DISINHIBIT, ADJ, SUBJ, 1),
        FiberRule(DISINHIBIT, ADJ, OBJ, 1),
        FiberRule(INHIBIT, PREP_P, SUBJ, 0),
        FiberRule(INHIBIT, PREP_P, OBJ, 0),
        FiberRule(INHIBIT, VERB, ADJ, 0),
      }
  };
}

RuleSet generic_trans_verb(int index) {
  return {
      index,
      { // PRE_RULES
        FiberRule(DISINHIBIT, LEX, VERB, 0),
        FiberRule(DISINHIBIT, VERB, SUBJ, 0),
        FiberRule(DISINHIBIT, VERB, ADVERB, 0),
        AreaRule(DISINHIBIT, ADVERB, 1),
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, VERB, 0),
        AreaRule(DISINHIBIT, OBJ, 0),
        AreaRule(INHIBIT, SUBJ, 0),
        AreaRule(INHIBIT, ADVERB, 0),
        FiberRule(DISINHIBIT, PREP_P, VERB, 0),
      }
  };
}

RuleSet generic_intrans_verb(int index) {
  return {
      index,
      { // PRE_RULES
        FiberRule(DISINHIBIT, LEX, VERB, 0),
        FiberRule(DISINHIBIT, VERB, SUBJ, 0),
        FiberRule(DISINHIBIT, VERB, ADVERB, 0),
        AreaRule(DISINHIBIT, ADVERB, 1),
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, VERB, 0),
        AreaRule(INHIBIT, SUBJ, 0),
        AreaRule(INHIBIT, ADVERB, 0),
        FiberRule(DISINHIBIT, PREP_P, VERB, 0),
      }
  };
}

RuleSet generic_copula(int index) {
  return {
      index,
      { // PRE_RULES
        FiberRule(DISINHIBIT, LEX, VERB, 0),
		FiberRule(DISINHIBIT, VERB, SUBJ, 0),
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, VERB, 0),
        AreaRule(DISINHIBIT, OBJ, 0),
        AreaRule(INHIBIT, SUBJ, 0),
        FiberRule(DISINHIBIT, ADJ, VERB, 0)
      }
  };
}

RuleSet generic_adverb(int index) {
  return {
      index,
      { // PRE_RULES
        AreaRule(DISINHIBIT, ADVERB, 0),
		FiberRule(DISINHIBIT, LEX, ADVERB, 0)
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, ADVERB, 0),
		AreaRule(INHIBIT, ADVERB, 1),
      }
  };
}

RuleSet generic_determinant(int index) {
  return {
      index,
      { // PRE_RULES
        AreaRule(DISINHIBIT, DET, 0), 
        FiberRule(DISINHIBIT, LEX, DET, 0)
      },  
      { // POST_RULES
        FiberRule(INHIBIT, LEX, DET, 0),
        FiberRule(INHIBIT, VERB, ADJ, 0),
      }
  };
}

RuleSet generic_adjective(int index) {
  return {
      index,
      { // PRE_RULES
        AreaRule(DISINHIBIT, ADJ, 0),
		FiberRule(DISINHIBIT, LEX, ADJ, 0)
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, ADJ, 0),
		FiberRule(INHIBIT, VERB, ADJ, 0),
      }
  };
}

RuleSet generic_preposition(int index) {
  return {
      index,
      { // PRE_RULES
        AreaRule(DISINHIBIT, PREP, 0),
			  FiberRule(DISINHIBIT, LEX, PREP, 0),
      },
      { // POST_RULES
        FiberRule(INHIBIT, LEX, PREP, 0),
        AreaRule(DISINHIBIT, PREP_P, 0),
        FiberRule(INHIBIT, LEX, SUBJ, 1),
        FiberRule(INHIBIT, LEX, OBJ, 1),
        FiberRule(INHIBIT, DET, SUBJ, 1),
        FiberRule(INHIBIT, DET, OBJ, 1),
        FiberRule(INHIBIT, ADJ, SUBJ, 1),
        FiberRule(INHIBIT, ADJ, OBJ, 1),
      }
  };
}

std::unordered_map<std::string, RuleSet> generateLexemeDict() {
  std::unordered_map<std::string, RuleSet> lexemeDict;

  lexemeDict["the"] = generic_determinant(0);
  lexemeDict["a"] = generic_determinant(1);
  lexemeDict["dogs"] = generic_noun(2);
  lexemeDict["cats"] = generic_noun(3);
  lexemeDict["mice"] = generic_noun(4);
  lexemeDict["people"] = generic_noun(5);
  lexemeDict["chase"] = generic_trans_verb(6);
  lexemeDict["love"] = generic_trans_verb(7);
  lexemeDict["bite"] = generic_trans_verb(8);
  lexemeDict["of"] = generic_preposition(9);
  lexemeDict["big"] = generic_adjective(10);
  lexemeDict["bad"] = generic_adjective(11);
  lexemeDict["run"] = generic_intrans_verb(12);
  lexemeDict["fly"] = generic_intrans_verb(13);
  lexemeDict["quickly"] = generic_adverb(14);
  lexemeDict["in"] = generic_preposition(15);
  lexemeDict["are"] = generic_copula(16);
  lexemeDict["man"] = generic_noun(17);
  lexemeDict["woman"] = generic_noun(18);
  lexemeDict["saw"] = generic_trans_verb(19);

  return lexemeDict;
}

/*=================================TODO: ParserBrain=================================*/
/*对应 parser.py 的 ParserBrain 和 EnglishParserBrain */


ParserBrain::ParserBrain(float p, float beta, float max_weight, uint32_t seed,
    std::unordered_map<std::string, RuleSet> lexeme_dict, 
    std::vector<std::string> all_areas, 
    std::vector<std::string> recurrent_areas, 
    std::vector<std::string> initial_areas, 
    ProjectMap readout_rules)
    : Brain(p, beta, max_weight, seed), lexeme_dict(lexeme_dict), 
    all_areas(all_areas), recurrent_areas(recurrent_areas), 
    initial_areas(initial_areas), readout_rules(readout_rules) {
        initialize_states();
}

// 356 add + discard
void ParserBrain::initialize_states() {
    for (const auto& from_area : all_areas) {
        fiber_states[from_area] = {};
        for (const auto& to_area : all_areas) {
            fiber_states[from_area][to_area].insert(0);
        }
    }

    for (const auto& area : all_areas) {
        area_states[area].insert(0);
    }

    for (const auto& area : initial_areas) {
        area_states[area].erase(0);
    }
}

// upper same
void ParserBrain::applyFiberRule(const FiberRule& rule) {
    if (rule.action == INHIBIT) {
        fiber_states[rule.area1][rule.area2].insert(rule.index);
        fiber_states[rule.area2][rule.area1].insert(rule.index);
    } else if (rule.action == DISINHIBIT) {
        fiber_states[rule.area1][rule.area2].erase(rule.index);
        fiber_states[rule.area2][rule.area1].erase(rule.index);
    }
}

// upper same
void ParserBrain::applyAreaRule(const AreaRule& rule) {
    if (rule.action == INHIBIT) {
        area_states[rule.area].insert(rule.index);
    } else if (rule.action == DISINHIBIT) {
        area_states[rule.area].erase(rule.index);
    }
}

bool ParserBrain::applyRule(const Rule& rule) {
    if (const FiberRule* fiberRule = std::get_if<FiberRule>(&rule)) {
        applyFiberRule(*fiberRule);
        return true;
    } else if (const AreaRule* areaRule = std::get_if<AreaRule>(&rule)) {
        applyAreaRule(*areaRule);
        return true;
    }
    return false;
}

// (s)void Project(const ProjectMap& graph, uint32_t num_steps, ...
void ParserBrain::parse_project() {
    auto project_map = getProjectMap();
    remember_fibers(project_map);
    Brain::Project(project_map, NUM_STEPS); // 超参数 NUM_STEPS
}


/*
// parser.py 395 update
用于 readout 部分的纤维束激活，该部分保存所有激活过的纤维束
*/
void ParserBrain::remember_fibers(const ProjectMap& project_map) {
    for (const auto& pair : project_map) {
        activated_fibers[pair.first].insert(pair.second.begin(), pair.second.end());
    }
}

// parser.py 397
bool ParserBrain::recurrent(const std::string& area) { 
    return (std::find(recurrent_areas.begin(), recurrent_areas.end(), area) != recurrent_areas.end());
}

// (s)std::map<std::string, uint32_t> area_by_name_;
ProjectMap ParserBrain::getProjectMap() {
    ProjectMap proj_map;
    for (const auto& area1 : all_areas) {
        if (area_states[area1].empty()) {
            for (const auto& area2 : all_areas) {
                if (area1 == LEX && area2 == LEX) {
                    continue;
                }
                if (area_states[area2].empty()) {
                    if (fiber_states[area1][area2].empty()) {
                        // (s)411 area_by_name winners? - Area::activated
                        // 是否是 (!)empty?
                        if (areas_[area_by_name_[area1]].activated.empty()) {
                            proj_map[area1].insert(area2);
                        }
                        if (areas_[area_by_name_[area2]].activated.empty()) {
                            proj_map[area2].insert(area2);
                        }
                    }
                }
            }
        }
    }
    return proj_map;
}


void ParserBrain::activateWord(const std::string& area_name, const std::string& word) {
    auto &area = GetArea(area_name);
    auto k = area.k;
    auto assembly_start = lexeme_dict[word].index * k; // (s)420 index
    for (int i = 0; i < k; ++i) {
        area.activated.push_back(assembly_start + i); // 421 1d or 2d matrix?
    }
    // brain.py 40 - 检查集合是否被冻结的参数
    // area.fix_assembly();
    size_t assembly_index, overlap;
    ReadAssembly(area_name, assembly_index, overlap);
    ActivateArea(area_name, assembly_index);
    // (s)assembly_start? 使用 ReadAssembly 读取 index？
}


void ParserBrain::activateIndex(const std::string& area_name, int index) {
    auto& area = GetArea(area_name);
    int k = area.k;
    int assembly_start = index * k;
    for (int i = 0; i < k; ++i) {
        area.activated.push_back(assembly_start + i);
    }
    // (s)assembly_start?
    size_t assembly_index, overlap;
    ReadAssembly(area_name, assembly_index, overlap);
    ActivateArea(area_name, assembly_index);
}


std::string ParserBrain::interpretAssemblyAsString(const std::string& area_name) {
    return getWord(area_name, 0.7);
}


std::string ParserBrain::getWord(const std::string& area_name, double min_overlap) {
    auto& area = GetArea(area_name);
    auto& activated = area.activated;
    if (activated.empty())
        throw std::runtime_error("Cannot get word because no assembly in " + area_name);
    int area_k = area.k;
    int threshold = min_overlap * area_k;
    for (const auto& pair : lexeme_dict) {
        const std::string& word = pair.first; // index
        int word_index = pair.second.index;
        int word_assembly_start = word_index * area_k;
        int word_assembly_end = word_assembly_start + area_k;
        int count = 0;
        for (int i = word_assembly_start; i < word_assembly_end; ++i) {
            if (std::find(activated.begin(), activated.end(), i) != activated.end()) {
                ++count;
            }
        }
        if (count >= threshold) { // len - 长度是否正确
            return word;
        }
    }
    return ""; // None
}


std::unordered_map<std::string, std::unordered_set<std::string>> ParserBrain::getActivatedFibers() {
    std::unordered_map<std::string, std::unordered_set<std::string>> pruned_activated_fibers;
    for (const auto& pair : activated_fibers) {
        for (const auto& to_area : pair.second) {
            if (readout_rules[pair.first].find(to_area) != readout_rules[pair.first].end()) {
                pruned_activated_fibers[pair.first].insert(to_area);
            }
        }
    }
    return pruned_activated_fibers;
}


EnglishParserBrain::EnglishParserBrain(float p, int non_LEX_n, 
    int non_LEX_k, int LEX_k, double default_beta, 
    double LEX_beta, double recurrent_beta, 
    double interarea_beta, bool verbose)
    : ParserBrain(p, default_beta, 10000.0, 0, // (s)max_weight and seed
    generateLexemeDict(), AREAS, RECURRENT_AREAS, 
    {LEX, SUBJ, VERB}, ENGLISH_READOUT_RULES),
    verbose(verbose) {
    int LEX_n = LEX_SIZE * LEX_k;
    // (s) parser.py 508 add_explicit_area 添加激活的脑区
    // AddArea(LEX, LEX_n, LEX_k, default_beta);
    AddStimulus(LEX, LEX_k);

    int DET_k = LEX_k;
    AddArea(SUBJ, non_LEX_n, non_LEX_k);
    AddArea(OBJ, non_LEX_n, non_LEX_k);
    AddArea(VERB, non_LEX_n, non_LEX_k);
    AddArea(ADJ, non_LEX_n, non_LEX_k);
    AddArea(PREP, non_LEX_n, non_LEX_k);
    AddArea(PREP_P, non_LEX_n, non_LEX_k);
    AddArea(DET, non_LEX_n, DET_k);
    AddArea(ADVERB, non_LEX_n, non_LEX_k);

    /*
    brain.py 250 - update_plasticities 的逻辑: (new_beta 是新的更新率)
    custom_plasticities consists of area1: list[ (area2, new_beta) ], 
    represents new plasticity FROM area2 INTO area1.

    Brain 的 UpdatePlasticity() 是 private 成员，与 python 的基本思路不同，
    而且 const float beta_ 更新率是不可变的，因此我好像不用实现这一部分？
    因此我按照 python 写法更新 beta
    */
    // std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> custom_plasticities;
    // for (const auto& area : RECURRENT_AREAS) { // 525 append
    //     custom_plasticities[LEX].emplace_back(area, LEX_beta);
    //     custom_plasticities[area].emplace_back(LEX, LEX_beta);
    //     custom_plasticities[area].emplace_back(area, recurrent_beta);
    //     for (const auto& other_area : RECURRENT_AREAS) {
    //         if (other_area == area) continue;
    //         custom_plasticities[area].emplace_back(other_area, interarea_beta);
    //     }
    // }

    // for (const auto& entry : custom_plasticities) {
    //     // entry - to_area, update_rules
    //     for (const auto& subentry : entry.second) {
    //         // subentry - from_area, new_beta
    //     }
    // }
}


ProjectMap EnglishParserBrain::getProjectMap() {
    auto proj_map = ParserBrain::getProjectMap();
    if (proj_map.find(LEX) != proj_map.end() && proj_map[LEX].size() > 2) {
        throw std::runtime_error("Got that LEX projecting into many areas: " + std::to_string(proj_map[LEX].size()));
    }
    return proj_map;
}


std::string EnglishParserBrain::getWord(const std::string& area_name, double min_overlap) {
    auto word = ParserBrain::getWord(area_name, min_overlap);
    if (!word.empty()) {
        return word;
    }
    if (word.empty() && area_name == DET) {
        auto& activated = GetArea(area_name).activated;
        auto area_k = GetArea(area_name).k;
        double threshold = min_overlap * area_k;
        int nodet_index = DET_SIZE - 1;
        int nodet_assembly_start = nodet_index * area_k;
        std::unordered_set<int> nodet_assembly; // 553 int
        for (int i = nodet_assembly_start; i < nodet_assembly_start + area_k; ++i) {
            nodet_assembly.insert(i);
        }
        if (activated.size() > threshold && std::includes(activated.begin(), activated.end(), nodet_assembly.begin(), nodet_assembly.end())) {
            return "<null-det>";
        }
    }
    return "<NON-WORD>";
}


/*=================================TODO: ParserDebugger=================================*/
/*对应 parser.py 的 ParserDebugger 和 parser 函数（parserHelp） */

std::vector<std::string> split(std::string sentence){
    using namespace std;
    string temp;
    vector<string> ans;
    for (int i = 0; i < sentence.size();i++){
        if(sentence[i]==' '){
            ans.emplace_back(temp);
            temp.clear();
        }
        else temp += sentence[i];
    }
    ans.emplace_back(temp);
    return ans;
}

// python下Area::winners 到 c++下Area::activated 可参考 Brain::ComputeKnownActivations
void read_out(std::string area, ProjectMap mapping, EnglishParserBrain &b,
              std::vector<std::vector<std::string>> &dependencies){
    using namespace std;
    auto to_areas = mapping[area];
    ProjectMap temp1;
    temp1[area] = to_areas;
    b.Project(temp1, NUM_STEPS, false);
    auto this_word = b.getWord(LEX);
    for(auto to_area : to_areas){
        if(to_area==LEX) continue;
        ProjectMap temp2;
        temp2[to_area] = {LEX};
        auto other_word = b.getWord(LEX);
        vector<string> temp3 = {this_word, other_word, to_area};
        dependencies.emplace_back(temp3);
    }
    for(auto to_area : to_areas){
        if(to_area!=LEX) read_out(to_area, mapping, b, dependencies);
    }
}

void parse(std::string sentence, float p, int LEX_k, 
	       int project_rounds, bool verbose, bool debug, int readout_method){
    using namespace std;
    EnglishParserBrain b(p, LEX_k = LEX_k, verbose = verbose);
    unordered_map<string, RuleSet> lexeme_dict = generateLexemeDict();
    vector<string> all_areas = AREAS;
    vector<string> explicit_areas = EXPLICIT_AREAS;
    ProjectMap readout_rules = ENGLISH_READOUT_RULES;
    
    {   //parserHelper
        vector<string> words = split(sentence);
        bool extreme_debug = false;
        for(string word : words){
            RuleSet lexeme = lexeme_dict[word];
            b.activateWord(LEX, word);
            if(verbose){
                cout << "Activated word: " << word << endl;
                // cout<<b.GetArea(LEX)
            }
            
            for(Rule rule : lexeme.pre_rules){
                b.applyRule(rule);
            }

            ProjectMap proj_map = b.getProjectMap();
            for(const auto area : proj_map){
                if(!proj_map[LEX].count(area.first)){
                    b.GetArea(area.first).is_fixed = true;
                    if(verbose) cout << "FIXED assembly bc not LEX->this area in: " << area.first;
                }
                else if(area.first!=LEX){
                    b.GetArea(area.first).is_fixed = false;
                    b.GetArea(area.first).activated.clear();
                    if(verbose) cout << "ERASED assembly because LEX->this area in " << area.first;
                }
            }

            proj_map = b.getProjectMap();
            if(verbose){}

            for (int i = 0; i < project_rounds;i++){
                b.parse_project();
            }

            for(auto rule : lexeme.post_rules){
                b.applyRule(rule);
            }

            if(debug){}
        }

        for(auto area : all_areas){
            b.GetArea(area).is_fixed = false;
        }

        vector<vector<string>> dependencies;
        if(readout_method==1){}
        else if(readout_method==2){
            auto activated_fibers = b.getActivatedFibers();
            if(verbose){}
            read_out(VERB, activated_fibers, b, dependencies);
            cout << "Got dependencies: \n";
            for (int i = 0; i < dependencies.size();i++){
                cout << '[' << dependencies[i][0] << ',' << dependencies[i][1] << ',' << dependencies[i][2] << "] ";
            }
        }
    }
}

}  // namespace nemo