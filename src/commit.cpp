#include "Commit.h"
#include "Utils.h"
#include <iostream>
#include <sstream>

using namespace std;

static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \r\n\t");
    size_t end   = s.find_last_not_of(" \r\n\t");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

Commit::Commit(const string& msg,
               const string& parent,
               const map<string, string>& fileMap) {
    message    = msg;
    parentHash = trim(parent);
    files      = fileMap;
    timestamp  = Utils::getCurrentTimestamp();

    string raw = message + timestamp + parentHash;
    for (const auto& pair : files)
        raw += pair.first + pair.second;
    commitHash = Utils::hashString(raw);
}

bool Commit::save(const string& repoPath) {
    stringstream ss;
    ss << "hash:"      << commitHash << "\n";
    ss << "message:"   << message    << "\n";
    ss << "timestamp:" << timestamp  << "\n";
    ss << "parent:"    << parentHash << "\n";
    for (const auto& pair : files)
        ss << "file:" << pair.first << ":" << pair.second << "\n";

    Utils::writeFile(repoPath + "/commits/" + commitHash, ss.str());
    cout << "Commit saved: " << commitHash << "\n";
    return true;
}

Commit Commit::load(const string& repoPath, const string& hash) {
    string data = Utils::readFile(repoPath + "/commits/" + trim(hash));

    string msg, parent;
    map<string, string> fileMap;
    stringstream ss(data);
    string line;

    while (getline(ss, line)) {
        line = trim(line);
        if (line.rfind("message:", 0) == 0)
            msg = trim(line.substr(8));
        else if (line.rfind("parent:", 0) == 0)
            parent = trim(line.substr(7));
        else if (line.rfind("file:", 0) == 0) {
            string rest = line.substr(5);
            size_t colon = rest.find(':');
            if (colon != string::npos)
                fileMap[trim(rest.substr(0, colon))] = trim(rest.substr(colon + 1));
        }
    }
    return Commit(msg, parent, fileMap);
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
    for (const auto& pair : files)
        cout << "  " << pair.first << " -> " << pair.second << "\n";
    cout << "\n";
}