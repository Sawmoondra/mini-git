#pragma once
#include <string>
#include <map>
#include <vector>
#include "FileSnapshot.h"
#include "Commit.h"
#include "Utils.h"

using namespace std;

class Repository {
private:
    string repoPath;        // path to .minigit/
    string workingDir;      // current working directory
    map<string, string> stagingArea;  // filename -> contentHash

    string getHEAD();
    void setHEAD(const string& commitHash);

public:
    Repository(const string& workingDir);

    void init();
    void add(const string& filename);
    void commit(const string& message);
    void log();
    void status();
    void restore(const string& commitHash);
};