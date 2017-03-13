#!/usr/bin/env bash

python3 calculate_digram_frequencies.py english_words.txt
sed -i 's/, }/},/g' english_words_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py plaintext_dictionary.txt
sed -i 's/, }/},/g' plaintext_dictionary_digram_frequency.txt
