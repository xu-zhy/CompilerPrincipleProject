#include "parser.h" 

namespace nemo {

RuleSet generic_noun(int index) {
  return {
      
  };
}

RuleSet generic_trans_verb(int index) {
  return {
      
  };
}

RuleSet generic_intrans_verb(int index) {
  return {
      
  };
}

RuleSet generic_copula(int index) {
  return {
      
  };
}

RuleSet generic_adverb(int index) {
  return {
      
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
      
  };
}

RuleSet generic_preposition(int index) {
  return {
      
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




/*=================================TODO: ParserDebugger=================================*/
/*对应 parser.py 的 ParserDebugger 和 parser 函数（parserHelp） */

}  // namespace nemo