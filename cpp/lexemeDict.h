#include "parser.h"

namespace nemo {

const int LEX_SIZE = 84;
const int DET_SIZE = 3;

std::unordered_map<std::string, RuleSet> generateLexemeDict() {
  std::unordered_map<std::string, RuleSet> lexemeDict;

  lexemeDict["happy"] = generic_adjective(0);
  lexemeDict["complex"] = generic_adjective(1);
  lexemeDict["calm"] = generic_adjective(2);
  lexemeDict["dear"] = generic_adjective(3);
  lexemeDict["big"] = generic_adjective(4);
  lexemeDict["blue"] = generic_adjective(5);
  lexemeDict["old"] = generic_adjective(6);
  lexemeDict["little"] = generic_adjective(7);
  lexemeDict["friendly"] = generic_adjective(8);
  lexemeDict["sunny"] = generic_adjective(9);
  lexemeDict["tall"] = generic_adjective(10);
  lexemeDict["red"] = generic_adjective(11);
  lexemeDict["very"] = generic_adverb(12);
  lexemeDict["quickly"] = generic_adverb(13);
  lexemeDict["beautifully"] = generic_adverb(14);
  lexemeDict["gently"] = generic_adverb(15);
  lexemeDict["skillfully"] = generic_adverb(16);
  lexemeDict["happily"] = generic_adverb(17);
  lexemeDict["smoothly"] = generic_adverb(18);
  lexemeDict["is"] = generic_copula(19);
  lexemeDict["was"] = generic_copula(20);
  lexemeDict["are"] = generic_copula(21);
  lexemeDict["the"] = generic_determinant(22);
  lexemeDict["a"] = generic_determinant(23);
  lexemeDict["an"] = generic_determinant(24);
  lexemeDict["runs"] = generic_intrans_verb(25);
  lexemeDict["rises"] = generic_intrans_verb(26);
  lexemeDict["jumps"] = generic_intrans_verb(27);
  lexemeDict["sway"] = generic_intrans_verb(28);
  lexemeDict["sails"] = generic_intrans_verb(29);
  lexemeDict["twinkles"] = generic_intrans_verb(30);
  lexemeDict["walks"] = generic_intrans_verb(31);
  lexemeDict["cat"] = generic_noun(32);
  lexemeDict["dog"] = generic_noun(33);
  lexemeDict["star"] = generic_noun(34);
  lexemeDict["night"] = generic_noun(35);
  lexemeDict["man"] = generic_noun(36);
  lexemeDict["book"] = generic_noun(37);
  lexemeDict["bird"] = generic_noun(38);
  lexemeDict["apple"] = generic_noun(39);
  lexemeDict["problem"] = generic_noun(40);
  lexemeDict["sun"] = generic_noun(41);
  lexemeDict["sea"] = generic_noun(42);
  lexemeDict["fence"] = generic_noun(43);
  lexemeDict["boy"] = generic_noun(44);
  lexemeDict["letter"] = generic_noun(45);
  lexemeDict["friend"] = generic_noun(46);
  lexemeDict["chef"] = generic_noun(47);
  lexemeDict["yard"] = generic_noun(48);
  lexemeDict["boat"] = generic_noun(49);
  lexemeDict["market"] = generic_noun(50);
  lexemeDict["weather"] = generic_noun(51);
  lexemeDict["breeze"] = generic_noun(52);
  lexemeDict["algorithm"] = generic_noun(53);
  lexemeDict["kitchen"] = generic_noun(54);
  lexemeDict["girl"] = generic_noun(55);
  lexemeDict["lake"] = generic_noun(56);
  lexemeDict["food"] = generic_noun(57);
  lexemeDict["song"] = generic_noun(58);
  lexemeDict["children"] = generic_noun(59);
  lexemeDict["trees"] = generic_noun(60);
  lexemeDict["mouse"] = generic_noun(61);
  lexemeDict["idea"] = generic_noun(62);
  lexemeDict["teacher"] = generic_noun(63);
  lexemeDict["question"] = generic_noun(64);
  lexemeDict["student"] = generic_noun(65);
  lexemeDict["park"] = generic_noun(66);
  lexemeDict["in"] = generic_preposition(67);
  lexemeDict["outside"] = generic_preposition(68);
  lexemeDict["over"] = generic_preposition(69);
  lexemeDict["around"] = generic_preposition(70);
  lexemeDict["across"] = generic_preposition(71);
  lexemeDict["at"] = generic_preposition(72);
  lexemeDict["to"] = generic_preposition(73);
  lexemeDict["reads"] = generic_trans_verb(74);
  lexemeDict["writes"] = generic_trans_verb(75);
  lexemeDict["cooks"] = generic_trans_verb(76);
  lexemeDict["sings"] = generic_trans_verb(77);
  lexemeDict["solves"] = generic_trans_verb(78);
  lexemeDict["saw"] = generic_trans_verb(79);
  lexemeDict["chases"] = generic_trans_verb(80);
  lexemeDict["play"] = generic_trans_verb(81);
  lexemeDict["has"] = generic_trans_verb(82);
  lexemeDict["asked"] = generic_trans_verb(83);

  return lexemeDict;
}

}
