#include <vector>
#include <set>
#include <string>

// 使用 python 代码运行的结果
std::vector<std::set<std::vector<std::string>>> expected_dependency = {
    {{"is", "red", "ADJ"}, {"is", "apple", "SUBJ"}, {"apple", "the", "DET"}},
    {{"is", "happy", "ADJ"}, {"is", "cat", "SUBJ"}, {"cat", "the", "DET"}},
    {{"runs", "quickly", "ADVERB"}, {"runs", "dog", "SUBJ"}, {"dog", "a", "DET"}},
    {{"twinkles", "sky", "PREP_P"}, {"twinkles", "star", "SUBJ"}, {"sky", "in", "PREP"}, {"sky", "the", "DET"}, {"star", "a", "DET"}},
    {{"reads", "book", "OBJ"}, {"reads", "man", "SUBJ"}, {"book", "a", "DET"}, {"man", "a", "DET"}},
    {{"sings", "song", "OBJ"}, {"sings", "bird", "SUBJ"}, {"song", "a", "DET"}, {"bird", "the", "DET"}},
    {{"play", "game", "OBJ"}, {"play", "children", "SUBJ"}, {"game", "a", "DET"}, {"children", "the", "DET"}},
    {{"chases", "mouse", "OBJ"}, {"chases", "cat", "SUBJ"}, {"mouse", "the", "DET"}, {"cat", "the", "DET"}},
    {{"solves", "problem", "OBJ"}, {"solves", "algorithm", "SUBJ"}, {"problem", "complex", "ADJ"}, {"problem", "a", "DET"}, {"algorithm", "an", "DET"}},
    {{"has", "idea", "OBJ"}, {"has", "teacher", "SUBJ"}, {"idea", "an", "DET"}, {"teacher", "the", "DET"}},
    {{"asked", "question", "OBJ"}, {"asked", "student", "SUBJ"}, {"question", "a", "DET"}, {"student", "a", "DET"}},
    {{"sway", "gently", "ADVERB"}, {"sway", "trees", "SUBJ"}, {"sway", "breeze", "PREP_P"}, {"trees", "tall", "ADJ"}, {"breeze", "the", "DET"}, {"breeze", "in", "PREP"}},
    {{"rises", "sun", "SUBJ"}, {"rises", "sea", "PREP_P"}, {"sun", "the", "DET"}, {"sea", "calm", "ADJ"}, {"sea", "the", "DET"}, {"sea", "over", "PREP"}},
    {{"jumps", "quickly", "ADVERB"}, {"jumps", "cat", "SUBJ"}, {"jumps", "fence", "PREP_P"}, {"cat", "the", "DET"}, {"fence", "small", "ADJ"}, {"fence", "the", "DET"}, {"fence", "over", "PREP"}},
    {{"writes", "letter", "OBJ"}, {"writes", "boy", "SUBJ"}, {"letter", "a", "DET"}, {"letter", "friend", "PREP_P"}, {"friend", "dear", "ADJ"}, {"friend", "a", "DET"}, {"friend", "to", "PREP"}, {"boy", "a", "DET"}},
    {{"cooks", "chef", "SUBJ"}, {"cooks", "food", "OBJ"}, {"chef", "the", "DET"}, {"food", "kitchen", "PREP_P"}, {"kitchen", "in", "PREP"}, {"kitchen", "the", "DET"}},
    {{"runs", "dog", "SUBJ"}, {"runs", "happily", "ADVERB"}, {"runs", "yard", "PREP_P"}, {"dog", "the", "DET"}, {"yard", "around", "PREP"}, {"yard", "big", "ADJ"}, {"yard", "the", "DET"}},
    {{"sails", "boat", "SUBJ"}, {"sails", "smoothly", "ADVERB"}, {"sails", "lake", "PREP_P"}, {"boat", "the", "DET"}, {"lake", "across", "PREP"}, {"lake", "blue", "ADJ"}, {"lake", "the", "DET"}},
    {{"walks", "man", "SUBJ"}, {"walks", "park", "PREP_P"}, {"man", "old", "ADJ"}, {"man", "the", "DET"}, {"park", "in", "PREP"}, {"park", "the", "DET"}},
    {{"saw", "girl", "SUBJ"}, {"saw", "cat", "OBJ"}, {"girl", "the", "DET"}, {"cat", "a", "DET"}}
};