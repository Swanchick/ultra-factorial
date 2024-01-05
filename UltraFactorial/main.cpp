#include <iostream>
#include <string>
#include "dnumber.h"

int main() {
    DNumber n1("1");
    DNumber n2("999");

    n1.Add(n2);
    n1.Show();
}