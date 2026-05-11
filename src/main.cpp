#include <iostream>
#include "Utils.h"
#include "FileSnapshot.h"
#include "Commit.h"

using namespace std;

int main() {
    // Create and snapshot a test file
    Utils::writeFile("hello.txt", "hello from mini-git!\n");
    Utils::writeFile("world.txt", "world file content\n");

    FileSnapshot snap1("hello.txt");
    FileSnapshot snap2("world.txt");

    snap1.save(".minigit");
    snap2.save(".minigit");

    // Build file map
    map<string, string> files;
    files[snap1.getFilename()] = snap1.getContentHash();
    files[snap2.getFilename()] = snap2.getContentHash();

    // Create a commit
    Commit c("first commit", "", files);
    c.save(".minigit");
    c.print();

    // Load it back
    cout << "--- Loading commit back ---\n";
    Commit loaded = Commit::load(".minigit", c.getCommitHash());
    loaded.print();

    return 0;
}