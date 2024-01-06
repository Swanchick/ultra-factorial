#include "dnumber.h"
#include <iostream>
#include <string>
#include <cmath>

DNumber::DNumber() {
	length = 1;
	
	pNumber = new int[length];
	pNumber[0] = 0;
}

DNumber::DNumber(std::string n) {
	pNumber = convertString(n);
}

DNumber::DNumber(int* number, int l) {
	pNumber = number;
	length = l;
}

int* DNumber::convertString(std::string n) {
	length = n.length();
	int* number = new int[length];

	for (int i = 0; i < length; i++) {
		char c = n[i];

		number[i] = c - '0';
	}

	return number;
}

void DNumber::Add(DNumber& n) {
	if (length < n.GetLength()) {
		n.Add(*this);
		length = n.GetLength();
		pNumber = n.GetNumber();

		return;
	}

	int next = 0;
	int* n1Numbers = nullptr;
	n1Numbers = GetNumber();
	int* n2Numbers = nullptr;
	n2Numbers = n.GetNumber();

	int* interResultNumber = new int[length];
	int* resultNumber = nullptr;

	int n2Length = n.GetLength();

	for (int i = 0; i < length; i++) {
		int currentIndex1 = length - i - 1;
		int currentIndex2 = n2Length - i - 1;
		int n1Number = n1Numbers[currentIndex1];
		int n2Number = 0;

		if (i < n2Length) {
			n2Number = n2Numbers[currentIndex2];
		}
		
		int sum = n1Number + n2Number;
		if (next >= 10) {
			sum++;
		}
		
		if (sum >= 10) {
			next = sum;
			sum -= 10;
		}

		interResultNumber[currentIndex1] = sum;
	}

	if (next > 10) {
		int newLength = length + 1;

		resultNumber = new int[newLength];

		resultNumber[0] = 1;

		for (int i = 1; i <= length; i++) {
			resultNumber[i] = interResultNumber[i - 1];
		}

		length = newLength;

		delete[] interResultNumber;
	}
	else {
		resultNumber = interResultNumber;
	}

	delete pNumber;
	pNumber = nullptr;
	pNumber = resultNumber;
}

void DNumber::Multiply(DNumber& n) {
	if (length < n.GetLength()) {
		n.Multiply(*this);
		length = n.GetLength();
		pNumber = n.GetNumber();

		return;
	}

	if (n.GetLength() == 1 && n.GetNumber()[0] == 0) {
		length = 1;
		pNumber = new int[length];
		pNumber[0] = 0;

		return;
	}

	int n2Length = n.GetLength();
	int newLength = length + n2Length;
	
	int* n2Numbers = n.GetNumber();

	DNumber result;

	for (int j = 0; j < n2Length; j++) {
		int n2Index = n2Length - j - 1;
		int number2 = n2Numbers[n2Index];
		
		int* sumMatrix = new int[newLength];

		int next = 0;

		for (int i = 0; i < newLength; i++) {
			int newIndex = newLength - i - 1;
			
			if (i < j) {
				sumMatrix[newIndex] = 0;
				
				continue;
			}

			if (i >= length + j) {
				sumMatrix[newIndex] = next;
				next = 0;

				continue;
			}
			
			int n1Index = length - i - 1 + j;
			int number1 = pNumber[n1Index];

			int product = number1 * number2;

			if (next > 0) {
				product += next;

				next = 0;
			}

			if (product >= 10) {
				int resultNumber = product / 10;
				next = resultNumber;
				resultNumber = resultNumber * 10;

				product -= resultNumber;
			}

			sumMatrix[newIndex] = product;
		}

		DNumber interResult(sumMatrix, newLength);
		
		result.Add(interResult);
	}

	result.ClearNulls();

	length = result.GetLength();
	
	delete pNumber;
	pNumber = nullptr;
	pNumber = result.GetNumber();
}

void DNumber::Factorial() {
	int n1Number = GetInt();
	DNumber result("1");

	for (int i = 0; i < n1Number; i++) {
		DNumber n(std::to_string(i + 1));

		result.Multiply(n);

		std::cout << i + 1 << std::endl;
	}

	length = result.GetLength();
	pNumber = result.GetNumber();
}

void DNumber::Show() {
	for (int i = 0; i < length; i++) {
		std::cout << pNumber[i];
	}

	std::cout << std::endl;
}

void DNumber::ClearNulls() {
	int newLength = 0;
	bool prevNull = false;

	for (int i = 0; i < length; i++) {
		int number = pNumber[i];
		
		if (i == 0 && number == 0) {
			newLength++;
			prevNull = true;

			continue;
		}

		if (number == 0 && prevNull) {
			newLength++;

			continue;
		}

		prevNull = false;
	}

	int resultLength = length - newLength;
	
	int* result = new int[resultLength];

	for (int i = 0; i < resultLength; i++) {
		result[i] = pNumber[i + newLength];
	}

	length = resultLength;
	pNumber = result;
}

int DNumber::GetInt() {
	int result = 0;

	for (int i = 0; i < length; i++) {
		result += pow(10, i) * pNumber[length - i - 1];
	}

	return result;
}

int DNumber::GetLength() {
	return length;
}

int* DNumber::GetNumber() {
	return pNumber;
}