#include <iostream>
#include "strings.hpp"

using namespace jggtools;
using namespace std;
int main() {
    cout << "Checking library\n";
    if (testStrings()) exit (1);

    exit(0);
}
