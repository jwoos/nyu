#include "matrix.hpp"

// BEGIN: DIGRAM_FREQ_MATRIX
DigramFreqMatrix::DigramFreqMatrix(uint32_t rowCount, uint32_t columnCount) : matrix(rowCount, std::vector<uint32_t>(columnCount, 0)), rows(rowCount), columns(columnCount) {
	clearMatrix();
}

void DigramFreqMatrix::swapRow(uint32_t a, uint32_t b) {
	matrix[a].swap(matrix[b]);
}

void DigramFreqMatrix::swapColumn(uint32_t a, uint32_t b) {
	for (std::vector<std::vector<uint32_t>>::iterator outer = matrix.begin(); outer != matrix.end(); outer++) {
		std::vector<uint32_t>::iterator aIter = outer -> begin() + a;
		std::vector<uint32_t>::iterator bIter = outer -> begin() + b;

		std::iter_swap(aIter, bIter);
	}
}

std::vector<uint32_t> DigramFreqMatrix::getRow(uint32_t index) {
	return matrix[index];
}

std::vector<uint32_t> DigramFreqMatrix::getColumn(uint32_t index) {
	std::vector<uint32_t> v;

	for (std::vector<std::vector<uint32_t>>::iterator outer = matrix.begin(); outer != matrix.end(); outer++) {
		v.push_back((*outer)[index]);
	}

	return v;
}

void DigramFreqMatrix::printMatrix() {
	for (std::vector<std::vector<uint32_t>>::iterator outer = matrix.begin(); outer != matrix.end(); outer++) {
		for (std::vector<uint32_t>::iterator inner = outer -> begin(); inner != outer -> end(); inner++) {
			std::cout << *inner << ' ';
		}
		std::cout << std::endl;
	}
}

void DigramFreqMatrix::printDifferences(DigramFreqMatrix& other) {
	for (uint32_t outer = 0; outer != matrix.size(); outer++) {
		for (uint32_t inner = 0; inner != matrix.size(); inner++) {
			int diff = matrix[inner][outer] - other.matrix[inner][outer];
			if(diff == 0) {
				std::cout << " . ";
			} else if(diff < 0) {
				std::cout << diff << " ";
			} else {
				std::cout << " " << diff;
				if(diff < 10) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}
}

uint32_t DigramFreqMatrix::countDifferences(DigramFreqMatrix& other) {
	uint32_t totalDifferences = 0;
	for (uint32_t outer = 0; outer != matrix.size(); outer++) {
		for (uint32_t inner = 0; inner != matrix.size(); inner++) {
			int diff = matrix[inner][outer] - other.matrix[inner][outer];
			if(diff < 0) {
				totalDifferences -= diff;
			} else {
				totalDifferences += diff;
			}
		}
	}
	return totalDifferences;
}

std::vector<uint32_t>& DigramFreqMatrix::operator[](const uint32_t index) {
	return matrix[index];
}

uint32_t DigramFreqMatrix::size() {
	return rows == columns ? rows : 0;
}

void DigramFreqMatrix::clearColumn(uint32_t index) {
	for (std::vector<std::vector<uint32_t>>::iterator outer = matrix.begin(); outer != matrix.end(); outer++) {
		(*outer)[index] = 0;
	}
}

void DigramFreqMatrix::clearRow(uint32_t index) {
	std::fill(matrix[index].begin(), matrix[index].end(), 0);
}

void DigramFreqMatrix::clearMatrix() {
	for (std::vector<std::vector<uint32_t>>::iterator outer = matrix.begin(); outer != matrix.end(); outer++) {
		std::fill(outer -> begin(), outer -> end(), 0);
	}
}
// END: DIGRAM_FREQ_MATRIX


// BEGIN: D_CIPHER_MATRIX
DCipherMatrix::DCipherMatrix(uint32_t rowCount, uint32_t columnCount) : DigramFreqMatrix(rowCount, columnCount) {}

void DCipherMatrix::populateMatrix(const std::string& text) {
	clearMatrix();
	std::vector<std::string> splitVector = split(text, ',');
	std::vector<uint32_t> numVector = stringToUnsignedInt(splitVector);

	for (uint32_t i = 0; i < numVector.size() - 1; i++) {
		uint32_t row = numVector[i];
		uint32_t column = numVector[i + 1];

		matrix[row][column]++;
	}
}
// END: D_CIPHER_MATRIX


// BEGIN: D_PLAIN_MATRIX
DPlainMatrix::DPlainMatrix(uint32_t rowCount, uint32_t columnCount) : DigramFreqMatrix(rowCount, columnCount) {}

void DPlainMatrix::populateMatrix() {
	std::vector<uint32_t> row;
	clearMatrix();
	for (uint32_t i = 0; i < cipherMatrix -> size(); i++) {
		row = (*cipherMatrix)[i];

		for (uint32_t j = 0; j < row.size(); j++) {
			uint32_t xIndex = getIndexForChar((*key)[i]);
			uint32_t yIndex = getIndexForChar((*key)[j]);

			matrix[xIndex][yIndex] += row[j];
		}
	}
}

uint32_t DPlainMatrix::computeScore() {
	EMatrix expected = *expectedMatrix;

	uint32_t score = 0;

	for (uint32_t outer = 0; outer < rows; outer++) {
		for (uint32_t inner = 0; inner < columns; inner++) {
			int local = matrix[outer][inner] - expected[outer][inner];

			if (local < 0) {
				local *= -1;
			}

			score += local;
		}
	}

	return score;
}

void DPlainMatrix::setKey(std::vector<char>* k) {
	key = k;
	populateMatrix();
}

void DPlainMatrix::setFrequencyMap(std::map<char, uint32_t>* fm) {
	frequencyMap = fm;
}

void DPlainMatrix::setCipherMatrix(DCipherMatrix* dc) {
	cipherMatrix = dc;
}

void DPlainMatrix::setExpectedMatrix(EMatrix* em) {
	expectedMatrix = em;
}

void DPlainMatrix::safeUpdateKey(uint32_t x, uint32_t y) {
		// Finally, swap our key
	auto xIter = key -> begin() + x;
	auto yIter = key -> begin() + y;
	std::swap(*xIter, *yIter);

	// Then update our matrix to match
	populateMatrix();
}

// swap index x and y of the key
void DPlainMatrix::updateKey(uint32_t x, uint32_t y) {

	// Update the plaintext matrix by shuffling around quantities from the ciphertext matrix
	// The best way to think of this code is as each entry in the plaintext
	// matrix still holding memory of what was summed to get there in the first place
	// And we're just pulling a value out of that sum, and adding it elsewhere

	// First, swap rows x and y from the cipher matrix
	char oldKeyX = getIndexForChar((*key)[x]);
	char oldKeyY = getIndexForChar((*key)[y]);

	char newKeyX = oldKeyY; // For clarity
	char newKeyY = oldKeyX; // For clarity
	auto cipherMatrix = (*this->cipherMatrix);

	for(uint32_t element = 0; element < cipherMatrix.size(); element++) {
		uint32_t oldKeyElement = getIndexForChar((*key)[element]);
		uint32_t newKeyElement;
		// The corners where x and y interesect need to swap diagonally,
		// so we handle that carefully here
		if (element == x) {
			newKeyElement = getIndexForChar((*key)[y]); // X and Y swap
		} else if (element == y) {
			newKeyElement = getIndexForChar((*key)[x]); // X and Y swap
		} else {
			newKeyElement = oldKeyElement;
		}

		// Move the bits and bobs from old row X to new row X
		matrix[oldKeyX][oldKeyElement] -= cipherMatrix[x][element];
		matrix[newKeyX][newKeyElement] += cipherMatrix[x][element];

		// Move the bits and bobs from old row Y to new row Y
		matrix[oldKeyY][oldKeyElement] -= cipherMatrix[y][element];
		matrix[newKeyY][newKeyElement] += cipherMatrix[y][element];
	}

	for(uint32_t element = 0; element < cipherMatrix.size(); element++) {
		// Skip swapping the corners, because we already swapped them diagonally
		if (element == x || element == y) {
			continue;
		}

		// I use two variables here for clarity, even though they're the same value
		uint32_t oldKeyElement = getIndexForChar((*key)[element]);
		uint32_t newKeyElement = oldKeyElement;


		// Move the bits and bobs from old column X to new column X
		matrix[oldKeyElement][oldKeyX] -= cipherMatrix[element][x];
		matrix[newKeyElement][newKeyX] += cipherMatrix[element][x];

		// Move the bits and bobs from old column Y to new column Y
		matrix[oldKeyElement][oldKeyY] -= cipherMatrix[element][y];
		matrix[newKeyElement][newKeyY] += cipherMatrix[element][y];
	}

	// Finally, swap our key
	auto xIter = key -> begin() + x;
	auto yIter = key -> begin() + y;
	std::swap(*xIter, *yIter);
}

int DPlainMatrix::getFrequencyForChar(char x) {
	std::map<char, uint32_t>::iterator it;
	it = frequencyMap -> find(x);

	return it == frequencyMap -> end() ? -1 : it -> second;
}
// END: D_PLAIN_MATRIX


// BEGIN: E_MATRIX
EMatrix::EMatrix(uint32_t rowCount, uint32_t columnCount) : DigramFreqMatrix(rowCount, columnCount) {}

void EMatrix::populateMatrix(std::vector<std::vector<float>> percentage, uint32_t normalizer) {
	for (uint32_t i = 0; i < rows; i++) {
		for (uint32_t j = 0; j < columns; j++) {
			if (normalizer == 1) {
				matrix[i][j] = percentage[i][j];
			} else {
				matrix[i][j] = round(percentage[i][j] * normalizer);
			}
		}
	}
}
// END: E_MATRIX
