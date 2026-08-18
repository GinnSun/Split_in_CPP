#include<iostream>
#include<string>
using namespace std;


class ConsoleReader {
private:
	char* input;
	int size;
	int length{};

public:
	ConsoleReader(const int size)
	{
		input = new char[size];
		this->size = size;
	}

	void read() {
		cin.getline(input, size);
	}

	int findLength() {
		length = 0;

		for (int i{}; i < size; i++, length++) {
			if (input[i] == '\0')
				break;
		}

		return length;
	}

	int getLength() {
		return length;
	}

	char* getInput() {
		return input;
	}


	~ConsoleReader() {
		delete[] input;
	}
};


class Converter {
private:
	char** array = nullptr;
	int length{};
public:
	Converter() {}

	Converter(char* str, const int length)
	{
		int countOfWhiteSpace = getCountOfWhiteSpace(str, length);
		int countOfNotWhiteSpace = countOfWhiteSpace + 1;

		array = new char* [countOfNotWhiteSpace];
		this->length = countOfNotWhiteSpace;

		setArray(array, str, this->length, length);
		fillArray(array, str, this->length, length);

	}

	int getLengthOfInnerArray(char* array) {
		int i{};
		for (; array[i] != '\0'; i++) {}
		return i;
	}

	char** getArray() {
		return array;
	}

	int getOuterArraySize() {
		return length;
	} 

private:
	void setArray(char** array, char* str, const int sizeArray, const int sizeStr) {
		int length{};
		for (int i{}, j{0}; i < sizeStr; i++) {
			if (str[i] == ' ') {
				array[j] = new char[length + 1];
				j++;
				length = 0;
				continue;
			}

			length++;
		}

		array[sizeArray - 1] = new char[length];
	}

	void fillArray(char** array, char* str, const int sizeArray, const int sizeStr) {
		for (int i{}, j{}, k{}; i < sizeStr; i++) {
			if (str[i] == ' ') {
				array[j][k] = '\0';
				k = 0;
				j++;
				continue;
			}
			array[j][k] = str[i];
			k++;
		}
	}

	int getCountOfWhiteSpace(char* str, const int length) {
		int countWhiteSpace{};
		for (int i = 0; i < length; i++) {
			if (str[i] == ' ')
				countWhiteSpace++;
		}

		return countWhiteSpace;
	}
};

class NumbersHandler {
private:
	int* array;
	int size;
	Converter converter;
public:
	NumbersHandler(Converter converter)
	{
		this->converter = converter;
		size = converter.getOuterArraySize();
		array = new int[size];
	}

	void setArraySize() {

		char** arr = converter.getArray();

		for (int i{}; i < size; i++) {
			string str{};
			for (int j{}; j < converter.getLengthOfInnerArray(arr[i]); j++) {
				str += arr[i][j];
			}

			array[i] = stoi(str);
		}
	}

	int* getArray() {
		return array;
	}

	int getSize() {
		return size;
	}

	void showNumbers() {
		for (int i{}; i < size; i++) {
			cout << "array[" << i << "] = " << array[i] << endl;
	 	}
	}

	~NumbersHandler() {
		delete[] array;
	}
};




int main() {

	ConsoleReader reader(255);

	reader.read();
	Converter converter(reader.getInput(), reader.findLength());


	NumbersHandler numsHandler(converter);

	numsHandler.setArraySize();

	numsHandler.showNumbers();

	return 0;
}
