#pragma once

#include <iostream>
#include <string>

class DNumber {
public:
	DNumber();
	DNumber(std::string n);
	DNumber(int* pNumber, int length);

	void Add(DNumber n);
	void Multiply(DNumber n);
	void Factorial();
	void Show();
	void ClearNulls();

	int GetInt();
	int GetLength();
	int* GetNumber();
private:
	int length;
	int* pNumber;

	int* convertString(std::string n);

	
};