#include "Commit.h"
#include "Utils.h"
#include <iostream>
#include <sstream>

using namespace std;

Commit::Commit(const string& msg,
               const string& parent,
               const map<string, string>& fileMap) {
    message    = msg;
    parentHash = parent;
    files      = fileMap;
    timestamp  = Utils::getCurrentTimestamp();

    string raw = message + timestamp + parentHash;
    for (const auto& pair : files) {
        raw += pair.first + pair.second;
    }
    commitHash = Utils::hashString(raw);
}

bool Commit::save(const string& repoPath) {
    stringstream ss;
    ss << "hash:"      << commitHash << "\n";
    ss << "message:"   << message    << "\n";
    ss << "timestamp:" << timestamp  << "\n";
    ss << "parent:"    << parentHash << "\n";
    for (const auto& pair : files) {
        ss << "file:" << pair.first << ":" << pair.second << "\n";
    }
    string commitPath = repoPath + "/commits/" + commitHash;
    Utils::writeFile(commitPath, ss.str());
    cout << "Commit saved: " << commitHash << "\n";
    return true;
}

Commit Commit::load(const string& repoPath, const string& hash) {
    string commitPath = repoPath + "/commits/" + hash;
    string data = Utils::readFile(commitPath);

    string loadedMsg, loadedParent;
    map<string, string> loadedFiles;
    stringstream ss(data);
    string line;

    while (getline(ss, line)) {
        if (line.rfind("message:", 0) == 0)
            loadedMsg = line.substr(8);
        else if (line.rfind("parent:", 0) == 0)
            loadedParent = line.substr(7);
        else if (line.rfind("file:", 0) == 0) {
            string rest = line.substr(5);
            size_t colon = rest.find(':');
            if (colon != string::npos) {
                string fname = rest.substr(0, colon);
                string fhash = rest.substr(colon + 1);
                // trim any trailing whitespace or \r
                fhash.erase(fhash.find_last_not_of(" \r\n") + 1);
                loadedFiles[fname] = fhash;
            }
        }
    }
    return Commit(loadedMsg, loadedParent, loadedFiles);
}

string Commit::getCommitHash() const { return commitHash; }
string Commit::getMessage()    const { return message;    }
string Commit::getTimestamp()  const { return timestamp;  }
string Commit::getParentHash() const { return parentHash; }
map<string, string> Commit::getFiles() const { return files; }

void Commit::print() const {
    cout << "commit " << commitHash << "\n";
    cout << "Date:   " << timestamp << "\n";
    cout << "        " << message   << "\n";
    cout << "\nFiles:\n";
    for (const auto& pair : files) {
        cout << "  " << pair.first << " -> " << pair.second << "\n";
    }
    cout << "\n";
}