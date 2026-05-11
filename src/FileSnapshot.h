#pragma once
#include <string>
#include "Utils.h"

using namespace std;

class FileSnapshot {
private:
    string filename;      // original file name e.g. "hello.txt"
    string contentHash;   // hash of file content e.g. "3551c8c1"
    string content;       // actual file content

public:
    // Constructor - takes the file path to snapshot
    FileSnapshot(const string& filepath);

    // Saves the snapshot to .minigit/objects/
    bool save(const string& repoPath);

    // Getters
    string getFilename() const;
    string getContentHash() const;
    string getContent() const;

    // Static - load a snapshot back from objects folder
    static string loadContent(const string& repoPath, const string& hash);
};