#!/usr/bin/env bash

python3 calculate_digram_frequencies.py english_words.txt
sed -i 's/, }/},/g' english_words_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py plaintext_dictionary.txt
sed -i 's/, }/},/g' plaintext_dictionary_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py 1.txt sum
sed -i 's/, }/},/g' 1_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py 2.txt sum
sed -i 's/, }/},/g' 2_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py 3.txt sum
sed -i 's/, }/},/g' 3_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py 4.txt sum
sed -i 's/, }/},/g' 4_digram_frequency.txt

echo ''

python3 calculate_digram_frequencies.py 5.txt sum
sed -i 's/, }/},/g' 5_digram_frequency.txt
