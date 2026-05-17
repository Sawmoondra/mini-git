#include <iostream>
#include "Repository.h"

using namespace std;

int main() {
    Repository repo(".");

    // 1. Init
    repo.init();

    // 2. Create some files
    Utils::writeFile("file1.txt", "Hello from file1!\n");
    Utils::writeFile("file2.txt", "Hello from file2!\n");

    // 3. Add and commit
    repo.add("file1.txt");
    repo.add("file2.txt");
    repo.status();
    repo.commit("first commit");

    // 4. Modify a file and make second commit
    Utils::writeFile("file1.txt", "file1 has been modified!\n");
    repo.add("file1.txt");
    repo.commit("second commit - modified file1");

    // 5. Show history
    repo.log();

    // 6. Restore first commit
string firstCommit = "a141d214";  // copy your actual first commit hash
repo.restore(firstCommit);

// 7. Verify file1.txt was restored
string content = Utils::readFile("file1.txt");
cout << "file1.txt after restore: " << content;

    return 0;
}