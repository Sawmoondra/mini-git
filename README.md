# mini-git
A Git-inspired version control system built from scratch in C++
# mini-git

A Git-inspired version control system built from scratch in C++.
Simulates core Git internals including content-addressable storage,
commit snapshots, file hashing, and repository management.

## Features
- `init` — initialize a repository
- `add` — stage files for commit
- `commit` — save a snapshot with a message
- `log` — view commit history
- `diff` — see what changed between commits
- `restore` — go back to a previous commit
- `status` — show currently staged files

## Concepts Implemented
- SHA-style hashing (content-addressable storage)
- Merkle-tree inspired commit chaining
- Binary file serialization
- Command-line argument parsing
- OOP architecture with separation of concerns

## Tech Stack
- Language: C++17
- Build: g++ / Makefile
- Platform: Windows / Linux / macOS

## Project Structure
