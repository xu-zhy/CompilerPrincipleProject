'''
用于生成 lexemeDict.h 文件的脚本
- 测试句子定义于 sentences.txt 
- 测试单词定义于其它 *.txt 文件中
'''
import os

this_dir = os.path.dirname(os.path.realpath(__file__))
cpp_dir = os.path.join(this_dir, '..', 'cpp')
# print(cpp_dir)

def get_lexeme_dict():
    lexemeDict = {}
    for filename in os.listdir(this_dir):
        if filename == 'sentences.txt' or filename == 'dependency.txt':
            continue
        if filename.endswith('.txt'):
            with open(os.path.join(this_dir, filename), 'r') as f:
                for line in f:
                    line = line.strip()
                    if line:
                        lexemeDict[line] = "generic_" + filename[:-4] + '(' + str(len(lexemeDict)) + ')'
    return lexemeDict

def generate_pos_code():
    lexemeDict = get_lexeme_dict()
    for lexeme in lexemeDict:
        print('"' + lexeme + '": ' + lexemeDict[lexeme] + ',')
        

if __name__ == '__main__':
    lexemeDict = get_lexeme_dict()
    lex_size=len(lexemeDict)
    with open(os.path.join(cpp_dir, 'lexemeDict.h'), 'w') as f:
        f.write('#include \"parser.h\"\n\n')
        f.write('namespace nemo {\n\n')
        f.write(f'const int LEX_SIZE = {lex_size};\n')
        f.write('const int DET_SIZE = 3;\n\n')
        f.write('std::unordered_map<std::string, RuleSet> generateLexemeDict() {\n')
        f.write('  std::unordered_map<std::string, RuleSet> lexemeDict;\n\n')    
        for lexeme in lexemeDict:
            f.write('  lexemeDict["' + lexeme + '"] = ' + lexemeDict[lexeme] + ';\n')
        f.write('\n  return lexemeDict;\n}\n')
        f.write('\n}\n')
    # generate_pos_code()
        