#ifndef ENCRYPTION_MATRIX_H
#define ENCRYPTION_MATRIX_H

#include "utils.hpp"

class DigramFreqMatrix {
	public:
		explicit DigramFreqMatrix(uint32_t, uint32_t);
		void swapRow(uint32_t, uint32_t);
		void swapColumn(uint32_t, uint32_t);
		std::vector<uint32_t> getRow(uint32_t);
		std::vector<uint32_t> getColumn(uint32_t);
		void clearRow(uint32_t);
		void clearColumn(uint32_t);
		void clearMatrix();
		void printMatrix();
		uint32_t size();

		std::vector<uint32_t>& operator[](const uint32_t index);

	protected:
		std::vector<std::vector<uint32_t>> matrix;
		uint32_t rows;
		uint32_t columns;

	private:
};

class EMatrix : public DigramFreqMatrix {
	public:
		explicit EMatrix(uint32_t, uint32_t);
};

class DCipherMatrix : public DigramFreqMatrix {
	public:
		explicit DCipherMatrix(uint32_t, uint32_t);
		void populateMatrix(const std::string&);
};

class DPlainMatrix : public DigramFreqMatrix {
	public:
		explicit DPlainMatrix(uint32_t, uint32_t);
		void updateMatrix(uint32_t, uint32_t);
		void updateKey(uint32_t, uint32_t);
		uint32_t computeScore();
		int getFrequencyForChar(char);
		void populateMatrix();
		void setKey(std::vector<char>*);
		void setFrequencyMap(std::map<char, uint32_t>*);
		void setCipherMatrix(DCipherMatrix*);
		void setExpectedMatrix(EMatrix*);

	private:
		std::vector<char>* key;
		std::map<char, uint32_t>* frequencyMap;
		std::map<char, uint32_t>* indexMap;
		DCipherMatrix* cipherMatrix;
		EMatrix* expectedMatrix;
};

#endif
