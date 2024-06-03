#include "parser.h"
#include "dependency.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

namespace nemo {



class SentenceArgs {
public:
    int index;
    std::string sentence;

    SentenceArgs(int index, std::string sentence) : index(index), sentence(sentence) {}
    int get_index() { return index; }
    std::string get_sentence() { return sentence; }
    friend std::ostream& operator<<(std::ostream& os, const SentenceArgs& args) {
        os << "Index: " << args.index << ", Sentence: ";
        for(int i = 0; i < args.sentence.size(); i++){
            if(args.sentence[i] == ' '){
                os << '_';
            }else{
                os << args.sentence[i];
            }
        }
        return os;
    }
};

const std::vector<SentenceArgs> sentences = {
    {0, "the apple is red"},
    {1, "the cat is very happy"},
    {2, "a dog runs quickly"},
    {3, "a star twinkles in the sky"},
    {4, "a man reads a book"},
    {5, "the bird sings a song"},
    {6, "the children play a game"},
    {7, "the cat chases the mouse"},
    {8, "an algorithm solves a complex problem"},
    {9, "the teacher has an idea"},
    {10, "a student asked a question"},
    {11, "tall trees sway gently in the breeze"},
    {12, "the sun rises over the calm sea"},
    {13, "the cat quickly jumps over the small fence"},
    {14, "a boy writes a letter to a dear friend"},
    {15, "the chef cooks food in the kitchen"},
    {16, "the dog happily runs around the big yard"},
    {17, "the boat sails smoothly across the blue lake"},
    {18, "the old man walks in the park"},
    {19, "the girl saw a cat"}
};

class STest: public ::testing::TestWithParam<SentenceArgs> {
};

TEST_P(STest, Handles) {
    auto args = GetParam();
    int index = args.get_index();
    std::string s = args.get_sentence();
    auto dependency_set = parse(s);
    std::cout << "Got dependencies: ";
    for(auto dependency : dependency_set) {
        std::cout << "{";
        for(auto word : dependency) {
            std::cout << word << " ";
        }
        std::cout << "} ";
    }
    std::cout << "\n";
    EXPECT_TRUE(CompareDependency(dependency_set, expected_dependency[index]));
}

INSTANTIATE_TEST_SUITE_P(
    ParserTest,
    STest,
    ::testing::ValuesIn(sentences)
);

} // namespace nemo