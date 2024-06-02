import nltk
import spacy
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import string

# 下载nltk必要的资源
nltk.download('punkt')
nltk.download('averaged_perceptron_tagger')

# 加载spacy的模型
nlp = spacy.load('data2/en_core_web_sm')

# 定义标点符号及停用词
stop_words = set(stopwords.words('english'))
punctuation = string.punctuation

def preprocess_text(text):
    # 将文本转换为小写
    text = text.lower()
    # 去除标点符号
    text = ''.join([char for char in text if char not in punctuation])
    # 分词
    words = word_tokenize(text)
    return words

# 词性分类文件名映射
pos_files = {
    'DT': 'determinant.txt',
    'NN': 'noun.txt',
    'VB_transitive': 'transitive_verb.txt',
    'VB_intransitive': 'non_transitive_verb.txt',
    'IN': 'preposition.txt',
    'JJ': 'adjective.txt',
    'RB': 'adverb.txt',
    'VB_copula': 'copula.txt'
}

# 初始化文件内容
pos_contents = {key: [] for key in pos_files.values()}

def save_words_by_pos(words):
    tagged_words = nltk.pos_tag(words)
    for word, tag in tagged_words:
        if tag == 'DT':
            pos_contents[pos_files['DT']].append(word)
        elif tag.startswith('NN'):
            pos_contents[pos_files['NN']].append(word)
        elif tag.startswith('VB'):
            doc = nlp(word)
            for token in doc:
                if token.dep_ == 'ROOT':
                    if token.lemma_ == 'be':
                        pos_contents[pos_files['VB_copula']].append(word)
                    else:
                        if any(child.dep_ == 'dobj' for child in token.children):
                            pos_contents[pos_files['VB_transitive']].append(word)
                        else:
                            pos_contents[pos_files['VB_intransitive']].append(word)
        elif tag.startswith('IN'):
            pos_contents[pos_files['IN']].append(word)
        elif tag.startswith('JJ'):
            pos_contents[pos_files['JJ']].append(word)
        elif tag.startswith('RB'):
            pos_contents[pos_files['RB']].append(word)

def write_to_files():
    for file, words in pos_contents.items():
        with open(file, 'w') as f:
            f.write('\n'.join(words))

text = "The quick brown fox jumps over the lazy dog. They are running. The cat chased the mouse. She swims fast."
words = preprocess_text(text)
save_words_by_pos(words)
write_to_files()
