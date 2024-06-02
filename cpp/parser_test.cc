// need c++17 and for linux -lstdc++fs
#include "parser.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include <gtest/gtest.h>

namespace nemo {

const std::vector<std::string> sentences = {
    // "the cat is very happy",
    // "a dog runs quickly",
    // "a star twinkles in the night",
    "a man reads a book",
    // "the bird sings a song",
    // "the children play a game",
    // "an apple is on the table",
    // "the cat chases the mouse",
    // "an algorithm solves a complex problem",
    // "an ancient artifact reveals a secret",
    // "the world is facing environmental challenges",
    // "tall trees sway gently in the breeze",
    // "the sun rises over the calm sea slowly",
    // "the cat quickly jumps over the small fence",
    // "a boy writes a letter to a dear friend",
    // "the chef cooks delicious food in the small kitchen",
    // "the dog happily runs around the big yard",
    // "the boat sails smoothly across the blue lake",
    // "the old man slowly walks to the nearby market",
    // "the little girl saw a friendly cat"
};

// class TestOneSentence: public ::testing::TestWithParam<std::string> {};

// TEST_P(TestOneSentence, HandlesSentence) {
//     // std::string s = GetParam();
//     parse();
//     // EXPECT_TRUE(CompareSet(dependency, expected));
// }

// INSTANTIATE_TEST_SUITE_P(
//     ParserTest,
//     TestOneSentence,
//     ::testing::ValuesIn(sentences)
// );

} // namespace nemo

int main(){
    nemo::parse();
}