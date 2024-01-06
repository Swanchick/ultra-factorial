#pragma once

#include <iostream>
#include <string>

class DNumber {
public:
	DNumber();
	DNumber(std::string n);

	void Add(DNumber n);
	void Multiply(DNumber n);
	void Show();

	int GetLength();
	int* GetNumber();
private:
	int length;
	int* pNumber;

	int* convertString(std::string n);
};