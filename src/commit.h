#pragma once
#include <string>
#include <map>
#include "Utils.h"

using namespace std;

class Commit {
private:
    string commitHash;           // unique hash for this commit
    string message;              // commit message e.g. "first commit"
    string timestamp;            // when it was made
    string parentHash;           // previous commit hash (empty if first commit)
    map<string, string> files;   // filename -> contentHash

public:
    // Constructor - create a new commit
    Commit(const string& message, 
           const string& parentHash, 
           const map<string, string>& files);

    // Save commit to .minigit/commits/
    bool save(const string& repoPath);

    // Static - load a commit back from disk
    static Commit load(const string& repoPath, const string& hash);

    // Getters
    string getCommitHash() const;
    string getMessage() const;
    string getTimestamp() const;
    string getParentHash() const;
    map<string, string> getFiles() const;

    // Display commit info
    void print() const;
};