
#include "FileSnapshot.h"
#include "Utils.h"
#include <iostream>

using namespace std;

FileSnapshot::FileSnapshot(const string& filepath) {
    filename = filepath;
    content = Utils::readFile(filepath);
    contentHash = Utils::hashString(content);
}

bool FileSnapshot::save(const string& repoPath) {
    // Build path: .minigit/objects/<hash>
    string objectPath = repoPath + "/objects/" + contentHash;

    // Don't save again if already exists (same content = same hash)
    if (Utils::fileExists(objectPath)) {
        cout << "Object already exists: " << contentHash << "\n";
        return true;
    }

    // Save content to objects folder
    Utils::writeFile(objectPath, content);
    cout << "Saved snapshot: " << filename << " -> " << contentHash << "\n";
    return true;
}

string FileSnapshot::getFilename() const {
    return filename;
}

string FileSnapshot::getContentHash() const {
    return contentHash;
}

string FileSnapshot::getContent() const {
    return content;
}

// Static method - load file content back using its hash
string FileSnapshot::loadContent(const string& repoPath, const string& hash) {
    string objectPath = repoPath + "/objects/" + hash;
    if (!Utils::fileExists(objectPath)) {
        cerr << "Error: object not found: " << hash << "\n";
        return "";
    }
    return Utils::readFile(objectPath);
}