import nltk
from nltk.corpus import wordnet as wn

# Ensure nltk resources are downloaded
nltk.download('wordnet')
nltk.download('omw-1.4')

# Function to extract words based on POS
def get_words_by_pos(pos):
    pos_words = set()
    for synset in wn.all_synsets(pos):
        for lemma in synset.lemmas():
            pos_words.add(lemma.name())
            # Add past and present participle forms for verbs
            # if pos == wn.VERB:
            #     pos_words.add(lemma.name() + "ed")
            #     pos_words.add(lemma.name() + "ing")
    return list(pos_words)

# Extract words by POS
nouns = get_words_by_pos(wn.NOUN)
transitive_verbs = [word for word in get_words_by_pos(wn.VERB) if any(lv.frame_ids() for lv in wn.synset(word + '.v.01').lemmas())]
intransitive_verbs = [word for word in get_words_by_pos(wn.VERB) if not any(lv.frame_ids() for lv in wn.synset(word + '.v.01').lemmas())]
prepositions = [lemma.name() for synset in wn.all_synsets(wn.ADV) for lemma in synset.lemmas() if lemma.name() in ['on', 'in', 'at', 'by', 'for', 'with', 'about', 'against', 'between', 'into', 'through', 'during', 'before', 'after', 'above', 'below', 'to', 'from', 'up', 'down', 'in', 'out', 'on', 'off', 'over', 'under', 'again', 'further', 'then', 'once']]
determinants = ["the", "a", "an"]
adjectives = get_words_by_pos(wn.ADJ)
adverbs = get_words_by_pos(wn.ADV)

# Save to txt files
with open('nouns.txt', 'w') as f:
    f.write("\n".join(nouns))

with open('transitive_verbs.txt', 'w') as f:
    f.write("\n".join(transitive_verbs))

with open('intransitive_verbs.txt', 'w') as f:
    f.write("\n".join(intransitive_verbs))

with open('prepositions.txt', 'w') as f:
    f.write("\n".join(prepositions))

with open('determinants.txt', 'w') as f:
    f.write("\n".join(determinants))

with open('adjectives.txt', 'w') as f:
    f.write("\n".join(adjectives))

with open('adverbs.txt', 'w') as f:
    f.write("\n".join(adverbs))
