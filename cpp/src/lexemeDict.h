#include "parser.h"

namespace nemo {

const int LEX_SIZE = 87;
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
  lexemeDict["small"] = generic_adjective(12);
  lexemeDict["very"] = generic_adverb(13);
  lexemeDict["quickly"] = generic_adverb(14);
  lexemeDict["beautifully"] = generic_adverb(15);
  lexemeDict["gently"] = generic_adverb(16);
  lexemeDict["skillfully"] = generic_adverb(17);
  lexemeDict["happily"] = generic_adverb(18);
  lexemeDict["smoothly"] = generic_adverb(19);
  lexemeDict["is"] = generic_copula(20);
  lexemeDict["was"] = generic_copula(21);
  lexemeDict["are"] = generic_copula(22);
  lexemeDict["the"] = generic_determinant(23);
  lexemeDict["a"] = generic_determinant(24);
  lexemeDict["an"] = generic_determinant(25);
  lexemeDict["runs"] = generic_intrans_verb(26);
  lexemeDict["rises"] = generic_intrans_verb(27);
  lexemeDict["jumps"] = generic_intrans_verb(28);
  lexemeDict["sway"] = generic_intrans_verb(29);
  lexemeDict["sails"] = generic_intrans_verb(30);
  lexemeDict["twinkles"] = generic_intrans_verb(31);
  lexemeDict["walks"] = generic_intrans_verb(32);
  lexemeDict["cat"] = generic_noun(33);
  lexemeDict["dog"] = generic_noun(34);
  lexemeDict["star"] = generic_noun(35);
  lexemeDict["night"] = generic_noun(36);
  lexemeDict["man"] = generic_noun(37);
  lexemeDict["book"] = generic_noun(38);
  lexemeDict["bird"] = generic_noun(39);
  lexemeDict["apple"] = generic_noun(40);
  lexemeDict["problem"] = generic_noun(41);
  lexemeDict["sun"] = generic_noun(42);
  lexemeDict["sea"] = generic_noun(43);
  lexemeDict["fence"] = generic_noun(44);
  lexemeDict["boy"] = generic_noun(45);
  lexemeDict["letter"] = generic_noun(46);
  lexemeDict["friend"] = generic_noun(47);
  lexemeDict["chef"] = generic_noun(48);
  lexemeDict["yard"] = generic_noun(49);
  lexemeDict["boat"] = generic_noun(50);
  lexemeDict["market"] = generic_noun(51);
  lexemeDict["weather"] = generic_noun(52);
  lexemeDict["breeze"] = generic_noun(53);
  lexemeDict["algorithm"] = generic_noun(54);
  lexemeDict["kitchen"] = generic_noun(55);
  lexemeDict["girl"] = generic_noun(56);
  lexemeDict["lake"] = generic_noun(57);
  lexemeDict["food"] = generic_noun(58);
  lexemeDict["song"] = generic_noun(59);
  lexemeDict["children"] = generic_noun(60);
  lexemeDict["trees"] = generic_noun(61);
  lexemeDict["mouse"] = generic_noun(62);
  lexemeDict["idea"] = generic_noun(63);
  lexemeDict["teacher"] = generic_noun(64);
  lexemeDict["question"] = generic_noun(65);
  lexemeDict["student"] = generic_noun(66);
  lexemeDict["park"] = generic_noun(67);
  lexemeDict["game"] = generic_noun(68);
  lexemeDict["sky"] = generic_noun(69);
  lexemeDict["in"] = generic_preposition(70);
  lexemeDict["outside"] = generic_preposition(71);
  lexemeDict["over"] = generic_preposition(72);
  lexemeDict["around"] = generic_preposition(73);
  lexemeDict["across"] = generic_preposition(74);
  lexemeDict["at"] = generic_preposition(75);
  lexemeDict["to"] = generic_preposition(76);
  lexemeDict["reads"] = generic_trans_verb(77);
  lexemeDict["writes"] = generic_trans_verb(78);
  lexemeDict["cooks"] = generic_trans_verb(79);
  lexemeDict["sings"] = generic_trans_verb(80);
  lexemeDict["solves"] = generic_trans_verb(81);
  lexemeDict["saw"] = generic_trans_verb(82);
  lexemeDict["chases"] = generic_trans_verb(83);
  lexemeDict["play"] = generic_trans_verb(84);
  lexemeDict["has"] = generic_trans_verb(85);
  lexemeDict["asked"] = generic_trans_verb(86);

  return lexemeDict;
}

}
