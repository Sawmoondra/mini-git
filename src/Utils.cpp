#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>

using namespace std;

namespace Utils {

    string hashString(const string& content) {
        unsigned long hash = 5381;
        for (char c : content) {
            hash = ((hash << 5) + hash) + c;
        }
        stringstream ss;
        ss << hex << hash;
        return ss.str();
    }

    string readFile(const string& path) {
        ifstream file(path);
        if (!file.is_open()) {
            cerr << "Error: Cannot open file: " << path << "\n";
            return "";
        }
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void writeFile(const string& path, const string& content) {
        ofstream file(path);
        if (!file.is_open()) {
            cerr << "Error: Cannot write to file: " << path << "\n";
            return;
        }
        file << content;
    }

    bool fileExists(const string& path) {
        return filesystem::exists(path);
    }

    void createDirectory(const string& path) {
        filesystem::create_directories(path);
    }

    vector<string> listFiles(const string& dirPath) {
        vector<string> files;
        for (const auto& entry : filesystem::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().string());
            }
        }
        return files;
    }

    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);
        string ts = ctime(&t);
        if (!ts.empty() && ts.back() == '\n') ts.pop_back();
        return ts;
    }

}