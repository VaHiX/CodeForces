// Problem: CF 1914 A - Problemsolving Log
// https://codeforces.com/contest/1914/problem/A

/*
Problem: Count how many problems Monocarp solved during a contest based on his log.

Algorithm:
- For each test case, we iterate through the string of problem letters.
- We maintain a count of minutes spent on each problem (indexed by letter).
- After processing all actions, for each problem 'A' to 'Z', we check if the total time spent
  is greater than or equal to the time required to solve that problem (1 minute for A, 2 for B, ..., 26 for Z).
- If so, we increment our solution counter.

Time Complexity: O(n) per test case, where n is the length of the log string.
Space Complexity: O(1), since we use a fixed-size array of 26 integers regardless of input size.

Techniques:
- Use of fixed-size array for counting occurrences.
- Direct simulation of time tracking and problem-solving logic.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const int B = 26; // Number of problems (A-Z)
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    int v[B] = {0}; // Array to store time spent on each problem
    for (long p = 0; p < s.size(); p++) {
      ++v[s[p] - 'A']; // Increment count for the respective problem
    }
    long cnt(0);
    for (long p = 0; p < B; p++) {
      cnt += (v[p] > p); // Check if time spent >= required time to solve problem
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/