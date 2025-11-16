// Problem: CF 1574 A - Regular Bracket Sequences
// https://codeforces.com/contest/1574/problem/A

/*
 * Code Purpose: Generate exactly n different regular bracket sequences of length 2n.
 * 
 * Algorithm/Techniques:
 * - For each test case, start with a base sequence of n opening brackets followed by n closing brackets: ((...))
 * - Then, iteratively modify the sequence by swapping one closing bracket from the end with an opening bracket from the middle.
 * - This ensures all generated sequences are distinct and valid.
 * 
 * Time Complexity: O(n^2) per test case, due to string operations (copying and modifying).
 * Space Complexity: O(n) for each sequence; overall space is O(n^2) for storing all generated sequences.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a(n, '('), b(n, ')');
    std::string s(a + b); // Create initial sequence: (((...)))
    std::cout << s << std::endl;
    for (long p = 0; p + 1 < n; p++) {
      std::string x(s); // Copy current sequence
      x[n - 1] = ')';   // Change last character to ')'
      x[n + p] = '(';   // Change p-th character from the end to '('
      std::cout << x << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/