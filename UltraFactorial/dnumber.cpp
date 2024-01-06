#include "dnumber.h"
#include <iostream>
#include <string>

DNumber::DNumber() {
	length = 1;
	
	pNumber = new int[length];
	pNumber[0] = 0;
}

DNumber::DNumber(std::string n) {
	pNumber = convertString(n);
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

void DNumber::Add(DNumber n) {
	if (length < n.GetLength()) {
		n.Add(*this);
		length = n.GetLength();
		pNumber = n.GetNumber();

		return;
	}

	int next = 0;
	int* n1Numbers = GetNumber();
	int* n2Numbers = n.GetNumber();

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

	if (next >= 10) {
		int newLength = length + 1;

		resultNumber = new int[newLength];

		resultNumber[0] = 1;

		for (int i = 1; i <= length; i++) {
			resultNumber[i] = interResultNumber[i - 1];
		}

		length = newLength;
	}
	else {
		resultNumber = interResultNumber;
	}

	pNumber = resultNumber;
	
	delete[] interResultNumber;
	delete[] n1Numbers;
	delete[] n2Numbers;
}

void DNumber::Multiply(DNumber n) {
	if (length < n.GetLength()) {
		n.Multiply(*this);
		length = n.GetLength();
		pNumber = n.GetNumber();

		return;
	}

	int n2Length = n.GetLength();
	int newLength = length + n2Length;
	
	int* n2Numbers = n.GetNumber();

	int** sumMatrix = new int*[n2Length];
	
	std::cout << newLength << " new lenght" << std::endl;

	for (int j = 0; j < n2Length; j++) {
		int n2Index = n2Length - j - 1;
		int number2 = n2Numbers[n2Index];
		
		sumMatrix[j] = new int[newLength];

		int next = 0;

		for (int i = 0; i < newLength; i++) {
			if (i >= length) {
				sumMatrix[j][newLength - i - 1] = next;

				continue;
			}
			
			int n1Index = length - i - 1;
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

			sumMatrix[j][newLength - i - 1] = product;
		}
	}
}

void DNumber::Show() {
	for (int i = 0; i < length; i++) {
		std::cout << pNumber[i];
	}

	std::cout << std::endl;
}

int DNumber::GetLength() {
	return length;
}

int* DNumber::GetNumber() {
	return pNumber;
}