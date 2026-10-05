# Code review

The provided source compiles successfully with `g++ -std=c++17 -Wall -Wextra -pedantic` and exits cleanly through the main menu.

## Findings

- **High: recruiter actions are unauthenticated.** Anyone can choose the recruiter menu and update any application. The program has no recruiter identity check or job ownership check.
- **Medium: data is not persisted.** Students, jobs, and applications are kept in vectors and are lost at exit.
- **Medium: input is not validated.** If a non-number is entered where `cin >>` expects an integer or decimal, the stream enters a failed state and menus may stop working. Recruiter CGPA/backlog/skill-count inputs also accept invalid ranges.
- **Low: feature scope is narrower than the web portal.** Registration, admin/company approval, resume upload, search/filtering, pagination, email, and interview scheduling are not present.

## Small source adjustment in this folder

Added the direct `<cctype>` include used for `std::tolower`; the rest of the supplied C++ logic is preserved.
