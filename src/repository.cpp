#include "Repository.h"
#include <iostream>
#include <sstream>

using namespace std;

static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \r\n\t");
    size_t end   = s.find_last_not_of(" \r\n\t");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

Repository::Repository(const string& dir) {
    workingDir = dir;
    repoPath   = dir + "/.minigit";
}

string Repository::getHEAD() {
    string headPath = repoPath + "/HEAD";
    if (!Utils::fileExists(headPath)) return "";
    return trim(Utils::readFile(headPath));
}

void Repository::setHEAD(const string& commitHash) {
    Utils::writeFile(repoPath + "/HEAD", commitHash);
}

void Repository::init() {
    if (Utils::fileExists(repoPath)) {
        cout << "Repository already initialized.\n";
        return;
    }
    Utils::createDirectory(repoPath);
    Utils::createDirectory(repoPath + "/objects");
    Utils::createDirectory(repoPath + "/commits");
    Utils::writeFile(repoPath + "/HEAD", "");
    cout << "Initialized empty mini-git repository in .minigit/\n";
}

void Repository::add(const string& filename) {
    if (!Utils::fileExists(filename)) {
        cerr << "Error: file not found: " << filename << "\n";
        return;
    }
    FileSnapshot snap(filename);
    snap.save(repoPath);
    stagingArea[filename] = snap.getContentHash();
    cout << "Staged: " << filename << " (" << snap.getContentHash() << ")\n";
}

void Repository::commit(const string& message) {
    if (stagingArea.empty()) {
        cout << "Nothing to commit. Stage files first with 'add'.\n";
        return;
    }
    string parentHash = getHEAD();
    Commit c(message, parentHash, stagingArea);
    c.save(repoPath);
    setHEAD(c.getCommitHash());
    stagingArea.clear();
    cout << "Committed: " << c.getCommitHash() << "\n";
    cout << "Message:   " << message << "\n";
}

void Repository::log() {
    string currentHash = getHEAD();

    if (currentHash.empty()) {
        cout << "No commits yet.\n";
        return;
    }

    cout << "\n=== Commit History ===\n\n";
    while (!currentHash.empty()) {
        Commit c = Commit::load(repoPath, currentHash);
        c.print();
        currentHash = trim(c.getParentHash());
    }
}

void Repository::status() {
    cout << "\n=== Staging Area ===\n";
    if (stagingArea.empty()) {
        cout << "Nothing staged.\n";
    } else {
        for (const auto& pair : stagingArea)
            cout << "  staged: " << pair.first
                 << " -> " << pair.second << "\n";
    }
    string head = getHEAD();
    cout << "\nHEAD: " << (head.empty() ? "no commits yet" : head) << "\n";
}

void Repository::restore(const string& commitHash) {
    string commitPath = repoPath + "/commits/" + commitHash;
    if (!Utils::fileExists(commitPath)) {
        cerr << "Error: commit not found: " << commitHash << "\n";
        return;
    }
    Commit c = Commit::load(repoPath, commitHash);
    for (const auto& pair : c.getFiles()) {
        string content = FileSnapshot::loadContent(repoPath, pair.second);
        Utils::writeFile(pair.first, content);
        cout << "Restored: " << pair.first << "\n";
    }
    cout << "Restored to commit: " << commitHash << "\n";
}