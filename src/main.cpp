#include <iostream>
#include "Utils.h"

using namespace std;

int main() {
    string content = "hello world";
    string hash = Utils::hashString(content);
    cout << "Hash of 'hello world': " << hash << "\n";

    Utils::writeFile("test.txt", "testing file write\n");
    string read = Utils::readFile("test.txt");
    cout << "Read back: " << read;

    cout << "Time: " << Utils::getCurrentTimestamp() << "\n";
    return 0;
}