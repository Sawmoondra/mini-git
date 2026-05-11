#include <iostream>
#include "Utils.h"
#include "FileSnapshot.h"

using namespace std;

int main() {
    // Create a test file to snapshot
    Utils::writeFile("test.txt", "hello from mini-git!\n");

    // Take a snapshot of it
    FileSnapshot snap("test.txt");

    cout << "File: " << snap.getFilename() << "\n";
    cout << "Hash: " << snap.getContentHash() << "\n";
    cout << "Content: " << snap.getContent();

    // Save it to .minigit/objects/
    snap.save(".minigit");

    // Load it back using the hash
    string loaded = FileSnapshot::loadContent(".minigit", snap.getContentHash());
    cout << "Loaded back: " << loaded;

    return 0;
}