#include "parser.h"

namespace nemo {

std::unordered_map<std::string, RuleSet> generateLexemeDict() {
  std::unordered_map<std::string, RuleSet> lexemeDict;

  lexemeDict["delicious"] = generic_adjective(0);
  lexemeDict["happy"] = generic_adjective(1);
  lexemeDict["complex"] = generic_adjective(2);
  lexemeDict["environmental"] = generic_adjective(3);
  lexemeDict["calm"] = generic_adjective(4);
  lexemeDict["small"] = generic_adjective(5);
  lexemeDict["dear"] = generic_adjective(6);
  lexemeDict["big"] = generic_adjective(7);
  lexemeDict["blue"] = generic_adjective(8);
  lexemeDict["old"] = generic_adjective(9);
  lexemeDict["nearby"] = generic_adjective(10);
  lexemeDict["little"] = generic_adjective(11);
  lexemeDict["friendly"] = generic_adjective(12);
  lexemeDict["sunny"] = generic_adjective(13);
  lexemeDict["tall"] = generic_adjective(14);
  lexemeDict["very"] = generic_adverb(15);
  lexemeDict["quickly"] = generic_adverb(16);
  lexemeDict["beautifully"] = generic_adverb(17);
  lexemeDict["gently"] = generic_adverb(18);
  lexemeDict["slowly"] = generic_adverb(19);
  lexemeDict["skillfully"] = generic_adverb(20);
  lexemeDict["happily"] = generic_adverb(21);
  lexemeDict["smoothly"] = generic_adverb(22);
  lexemeDict["is"] = generic_copula(23);
  lexemeDict["was"] = generic_copula(24);
  lexemeDict["are"] = generic_copula(25);
  lexemeDict["the"] = generic_determinant(26);
  lexemeDict["a"] = generic_determinant(27);
  lexemeDict["an"] = generic_determinant(28);
  lexemeDict["runs"] = generic_intrans_verb(29);
  lexemeDict["rises"] = generic_intrans_verb(30);
  lexemeDict["jumps"] = generic_intrans_verb(31);
  lexemeDict["sway"] = generic_intrans_verb(32);
  lexemeDict["sails"] = generic_intrans_verb(33);
  lexemeDict["twinkles"] = generic_intrans_verb(34);
  lexemeDict["walks"] = generic_intrans_verb(35);
  lexemeDict["cat"] = generic_noun(36);
  lexemeDict["dog"] = generic_noun(37);
  lexemeDict["star"] = generic_noun(38);
  lexemeDict["night"] = generic_noun(39);
  lexemeDict["man"] = generic_noun(40);
  lexemeDict["book"] = generic_noun(41);
  lexemeDict["bird"] = generic_noun(42);
  lexemeDict["apple"] = generic_noun(43);
  lexemeDict["problem"] = generic_noun(44);
  lexemeDict["ancient"] = generic_noun(45);
  lexemeDict["artifact"] = generic_noun(46);
  lexemeDict["world"] = generic_noun(47);
  lexemeDict["sun"] = generic_noun(48);
  lexemeDict["sea"] = generic_noun(49);
  lexemeDict["fence"] = generic_noun(50);
  lexemeDict["boy"] = generic_noun(51);
  lexemeDict["letter"] = generic_noun(52);
  lexemeDict["friend"] = generic_noun(53);
  lexemeDict["chef"] = generic_noun(54);
  lexemeDict["yard"] = generic_noun(55);
  lexemeDict["boat"] = generic_noun(56);
  lexemeDict["market"] = generic_noun(57);
  lexemeDict["weather"] = generic_noun(58);
  lexemeDict["table"] = generic_noun(59);
  lexemeDict["breeze"] = generic_noun(60);
  lexemeDict["algorithm"] = generic_noun(61);
  lexemeDict["kitchen"] = generic_noun(62);
  lexemeDict["girl"] = generic_noun(63);
  lexemeDict["lake"] = generic_noun(64);
  lexemeDict["food"] = generic_noun(65);
  lexemeDict["song"] = generic_noun(66);
  lexemeDict["children"] = generic_noun(67);
  lexemeDict["challenges"] = generic_noun(68);
  lexemeDict["trees"] = generic_noun(69);
  lexemeDict["mouse"] = generic_noun(70);
  lexemeDict["secret"] = generic_noun(71);
  lexemeDict["in"] = generic_preposition(72);
  lexemeDict["outside"] = generic_preposition(73);
  lexemeDict["on"] = generic_preposition(74);
  lexemeDict["over"] = generic_preposition(75);
  lexemeDict["around"] = generic_preposition(76);
  lexemeDict["across"] = generic_preposition(77);
  lexemeDict["at"] = generic_preposition(78);
  lexemeDict["to"] = generic_preposition(79);
  lexemeDict["reads"] = generic_trans_verb(80);
  lexemeDict["writes"] = generic_trans_verb(81);
  lexemeDict["cooks"] = generic_trans_verb(82);
  lexemeDict["sings"] = generic_trans_verb(83);
  lexemeDict["solves"] = generic_trans_verb(84);
  lexemeDict["saw"] = generic_trans_verb(85);
  lexemeDict["chases"] = generic_trans_verb(86);
  lexemeDict["reveals"] = generic_trans_verb(87);
  lexemeDict["play"] = generic_trans_verb(88);
  lexemeDict["facing"] = generic_trans_verb(89);

  return lexemeDict;
}

}
