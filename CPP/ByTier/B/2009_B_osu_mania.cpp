// Problem: CF 2009 B - osu!mania
// https://codeforces.com/contest/2009/problem/B

/*
B. osu!mania
Purpose: This code processes a rhythm game beatmap represented as n rows and 4 columns.
Each row contains exactly one note ('#'), and the notes are processed from bottom to top.
The goal is to determine the column position of each note in the order they are processed.

Algorithms/Techniques:
- Iteration through rows and characters
- Linear search for '#' character in each row
- Reverse output of processed results

Time Complexity: O(n * 4) = O(n) per test case, where n is the number of rows.
Space Complexity: O(n) for storing column positions of notes.

Input Format:
- First line: t (number of test cases)
- For each test case:
  - First line: n (number of rows)
  - Next n lines: 4-character strings representing each row

Output Format:
- For each test case: n integers representing column positions (1-indexed) of notes in reverse order
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) { // Process each test case
    long n;
    std::cin >> n;
    std::vector<long> v(n); // Store column positions of notes
    for (long p = 0; p < n; p++) { // Read each row
      std::string s;
      std::cin >> s;
      for (long u = 0; u < 4; u++) { // Scan each character in the row
        if (s[u] == '#') { // Found the note
          v[p] = u + 1; // Store column index (1-based)
          break;
        }
      }
    }
    for (long p = n - 1; p >= 0; p--) { // Output in reverse order (bottom to top)
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/