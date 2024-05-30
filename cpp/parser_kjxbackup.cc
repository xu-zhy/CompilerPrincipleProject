class ParserBrain : public Brain {
public:
    std::unordered_map<std::string, int> lexeme_dict;
    std::vector<std::string> all_areas;
    std::vector<std::string> recurrent_areas;
    std::vector<std::string> initial_areas;

    std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<int>>> fiber_states;
    std::unordered_map<std::string, std::unordered_set<int>> area_states;
    std::unordered_map<std::string, std::unordered_set<std::string>> activated_fibers;
    std::unordered_map<std::string, std::unordered_set<std::string>> readout_rules;

    ParserBrain(Parser& p, // deepcopy
    std::unordered_map<std::string, int> lexeme_dict = {}, 
    std::vector<std::string> all_areas = {}, 
    std::vector<std::string> recurrent_areas = {}, 
    std::vector<std::string> initial_areas = {}, 
    std::unordered_map<std::string, 
    std::unordered_set<std::string>> readout_rules = {})
        : Brain(p), lexeme_dict(lexeme_dict), 
        all_areas(all_areas), recurrent_areas(recurrent_areas), 
        initial_areas(initial_areas), readout_rules(readout_rules) {
            initialize_states();
    }

    void initialize_states() {
        for (const auto& from_area : all_areas) {
            fiber_states[from_area] = {};
            for (const auto& to_area : all_areas) {
                fiber_states[from_area][to_area].insert(0); // 356 add + discard
            }
        }

        for (const auto& area : all_areas) {
            area_states[area].insert(0);
        }

        for (const auto& area : initial_areas) {
            area_states[area].erase(0);
        }
    }

    void applyFiberRule(const FiberRule& rule) {
        if (rule.action == INHIBIT) {
            fiber_states[rule.area1][rule.area2].insert(rule.index);
            fiber_states[rule.area2][rule.area1].insert(rule.index);
        } else if (rule.action == DISINHIBIT) {
            fiber_states[rule.area1][rule.area2].erase(rule.index);
            fiber_states[rule.area2][rule.area1].erase(rule.index);
        }
    }

    void applyAreaRule(const AreaRule& rule) {
        if (rule.action == INHIBIT) {
            area_states[rule.area].insert(rule.index);
        } else if (rule.action == DISINHIBIT) {
            area_states[rule.area].erase(rule.index);
        }
    }

    bool applyRule(const Rule& rule) {
        if (typeid(rule) == typeid(FiberRule)) { // 379 isinstance
            applyFiberRule(static_cast<const FiberRule&>(rule));
            return true;
        }
        if (typeid(rule) == typeid(AreaRule)) {
            applyAreaRule(static_cast<const AreaRule&>(rule));
            return true;
        }
        return false;
    }

    void parse_project() {
        auto project_map = getProjectMap();
        remember_fibers(project_map);
        project({}, project_map);
    }

    void remember_fibers(const std::unordered_map<std::string, 
    std::unordered_set<std::string>>& project_map) {
        for (const auto& pair : project_map) { // 395 update
            activated_fibers[pair.first].insert(pair.second.begin(), pair.second.end());
        }
    }

    bool recurrent(const std::string& area) { // 397
        return (std::find(recurrent_areas.begin(), recurrent_areas.end(), area) != recurrent_areas.end());
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getProjectMap() {
        std::unordered_map<std::string, std::unordered_set<std::string>> proj_map;
        for (const auto& area1 : all_areas) {
            if (area_states[area1].empty()) {
                for (const auto& area2 : all_areas) {
                    if (area1 == LEX && area2 == LEX) {
                        continue;
                    }
                    if (area_states[area2].empty()) {
                        if (fiber_states[area1][area2].empty()) {
                            if (!area_by_name[area1].winners.empty()) { // 411 area_by_name winners?
                                proj_map[area1].insert(area2);
                            }
                            if (!area_by_name[area2].winners.empty()) {
                                proj_map[area2].insert(area2);
                            }
                        }
                    }
                }
            }
        }
        return proj_map;
    }

    void activateWord(const std::string& area_name, const std::string& word) {
        auto& area = area_by_name[area_name]; // 418 &
        int k = area.k;
        int assembly_start = lexeme_dict[word] * k; // 420 index
        for (int i = 0; i < k; ++i) {
            area.winners.push_back(assembly_start + i); // 421 1d or 2d matrix?
        }
        area.fix_assembly();
    }

    void activateIndex(const std::string& area_name, int index) {
        auto& area = area_by_name[area_name];
        int k = area.k;
        int assembly_start = index * k;
        for (int i = 0; i < k; ++i) {
            area.winners.push_back(assembly_start + i);
        }
        area.fix_assembly();
    }

    std::string interpretAssemblyAsString(const std::string& area_name) {
        return getWord(area_name, 0.7);
    }

    std::string getWord(const std::string& area_name, double min_overlap = 0.7) {
        auto& winners = area_by_name[area_name].winners;
        // 435 empty == not 吗？
        if (winners.empty())
          throw std::runtime_error("Cannot get word because no assembly in " + area_name);
        int area_k = area_by_name[area_name].k;
        int threshold = min_overlap * area_k;
        for (const auto& pair : lexeme_dict) {
            const std::string& word = pair.first; // index
            int word_index = pair.second;
            int word_assembly_start = word_index * area_k;
            int word_assembly_end = word_assembly_start + area_k;
            int count = 0;
            for (int i = word_assembly_start; i < word_assembly_end; ++i) {
                if (std::find(winners.begin(), winners.end(), i) != winners.end()) {
                    ++count;
                }
            }
            if (count >= threshold) { // len - 长度是否正确
                return word;
            }
        }
        return ""; // None
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getActivatedFibers() {
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
};


class EnglishParserBrain : public ParserBrain {
public:
    EnglishParserBrain(float p, int non_LEX_n = 10000, 
    int non_LEX_k = 100, int LEX_k = 20, double default_beta = 0.2, 
    double LEX_beta = 1.0, double recurrent_beta = 0.05, 
    double interarea_beta = 0.5, bool verbose = false)
        : ParserBrain(p, LEXEME_DICT, AREAS, RECURRENT_AREAS, 
        {LEX, SUBJ, VERB}, ENGLISH_READOUT_RULES),
          verbose(verbose) {
        int LEX_n = LEX_SIZE * LEX_k;
        add_explicit_area(LEX, LEX_n, LEX_k, default_beta);

        int DET_k = LEX_k;
        add_area(SUBJ, non_LEX_n, non_LEX_k, default_beta);
        add_area(OBJ, non_LEX_n, non_LEX_k, default_beta);
        add_area(VERB, non_LEX_n, non_LEX_k, default_beta);
        add_area(ADJ, non_LEX_n, non_LEX_k, default_beta);
        add_area(PREP, non_LEX_n, non_LEX_k, default_beta);
        add_area(PREP_P, non_LEX_n, non_LEX_k, default_beta);
        add_area(DET, non_LEX_n, DET_k, default_beta);
        add_area(ADVERB, non_LEX_n, non_LEX_k, default_beta);

        std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> custom_plasticities;
        for (const auto& area : RECURRENT_AREAS) { // 525 append
            custom_plasticities[LEX].emplace_back(area, LEX_beta);
            custom_plasticities[area].emplace_back(LEX, LEX_beta);
            custom_plasticities[area].emplace_back(area, recurrent_beta);
            for (const auto& other_area : RECURRENT_AREAS) {
                if (other_area == area) continue;
                custom_plasticities[area].emplace_back(other_area, interarea_beta);
            }
        }
        update_plasticities(custom_plasticities);
    }

    std::unordered_map<std::string, std::vector<std::string>> getProjectMap() override {
        auto proj_map = ParserBrain::getProjectMap();
        if (proj_map.find(LEX) != proj_map.end() && proj_map[LEX].size() > 2) {
            throw std::runtime_error("Got that LEX projecting into many areas: " + std::to_string(proj_map[LEX].size()));
        }
        return proj_map;
    }

    std::string getWord(const std::string& area_name, double min_overlap = 0.7) override {
        auto word = ParserBrain::getWord(area_name, min_overlap);
        if (!word.empty()) {
            return word;
        }
        if (word.empty() && area_name == DET) {
            std::unordered_set<int> winners = area_by_name[area_name].winners;
            int area_k = area_by_name[area_name].k;
            double threshold = min_overlap * area_k;
            int nodet_index = DET_SIZE - 1;
            int nodet_assembly_start = nodet_index * area_k;
            std::unordered_set<int> nodet_assembly; // 553 int
            for (int i = nodet_assembly_start; i < nodet_assembly_start + area_k; ++i) {
                nodet_assembly.insert(i);
            }
            if (winners.size() > threshold && std::includes(winners.begin(), winners.end(), nodet_assembly.begin(), nodet_assembly.end())) {
                return "<null-det>";
            }
        }
        return "<NON-WORD>";
    }

private:
    bool verbose;
    """
    变量重定义问题
    不同命名空间的变量，使用的到底是谁？
    """
    std::unordered_map<std::string, int> LEXEME_DICT; 
    std::vector<std::string> AREAS;
    std::vector<std::string> RECURRENT_AREAS;
    std::vector<std::string> ENGLISH_READOUT_RULES;
    std::unordered_map<std::string, Area> area_by_name;

    struct Area {
        std::unordered_set<int> winners;
        int k;
    };
};