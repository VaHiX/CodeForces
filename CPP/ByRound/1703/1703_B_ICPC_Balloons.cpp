// Problem: CF 1703 B - ICPC Balloons
// https://codeforces.com/contest/1703/problem/B

/*
Problem: B. ICPC Balloons
Purpose: Calculate total balloons distributed in an ICPC contest based on problem-solving order.
Algorithms/Techniques: Single pass through string with boolean tracking of solved problems.
Time Complexity: O(n) where n is the length of the input string.
Space Complexity: O(1) as we use a fixed-size array of 26 booleans regardless of input size.

Input:
- Number of test cases t
- For each test case:
  - Length of string n
  - String s representing order of solved problems

Output:
- Total number of balloons distributed for each test case

Example:
ABA -> 5 balloons (A:2, B:2, A:1)
A   -> 2 balloons (A:2)
ORZ -> 6 balloons (O:2, R:2, Z:2)
*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool v[26] = {0}; // Track which problems have been solved (first time)
    long total(0);
    for (long p = 0; p < s.size(); p++) {
      int idx = s[p] - 'A'; // Convert character to index (0-25)
      total += 2 - v[idx];  // Add 2 if first solve, 1 if not (v[idx] is 0 or 1)
      v[idx] = 1;           // Mark problem as solved
    }
    std::cout << total << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/