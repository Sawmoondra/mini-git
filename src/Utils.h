#pragma once
#include <string>
#include <vector>

using namespace std;

namespace Utils {

    // Hashing
    string hashString(const string& content);

    // File I/O
    string readFile(const string& path);
    void writeFile(const string& path, const string& content);
    bool fileExists(const string& path);

    // Directory
    void createDirectory(const string& path);
    vector<string> listFiles(const string& dirPath);

    // String helpers
    string getCurrentTimestamp();

}