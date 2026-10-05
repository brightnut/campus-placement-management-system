# Campus Placement Management System (C++)

A terminal-based C++ prototype for browsing campus jobs, checking eligibility, applying, and tracking application status.

## Build and run

Requires a C++17 compiler.

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o campus-placement
./campus-placement
```

Or build with CMake:

```sh
cmake -S . -B build
cmake --build build
./build/campus-placement
```

## Demo navigation

- Choose `1` for student login, then enter student ID `1` (Aarav Mehta) or `2` (Maya Iyer).
- Choose `2` for the recruiter menu.
- Student accounts, recruiter, jobs, and one sample application are seeded in `seedData()`.
- Choose `0` at the main menu to exit.

## Included features

- Student and recruiter console menus.
- Job listings with company, role, location, package, and application deadline.
- Eligibility matching by minimum CGPA, maximum backlogs, and case-insensitive required skills.
- Duplicate-application prevention and application status tracking.
- Recruiter job posting and application status updates.
- Student dashboard counters.

## Current scope

This is a learning prototype. All records live in memory and reset when the program exits. It does not yet include real account authentication, registration, admin tools, resume files, SQL storage, email notifications, or interview scheduling. Recruiter access is currently a menu choice rather than authenticated access; add authentication and recruiter ownership checks before using it with real data.

See [CODE_REVIEW.md](CODE_REVIEW.md) for review notes.
