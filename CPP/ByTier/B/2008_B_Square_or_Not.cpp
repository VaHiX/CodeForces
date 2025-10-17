// Problem: CF 2008 B - Square or Not
// https://codeforces.com/contest/2008/problem/B

/*
B. Square or Not
Algorithm: Preprocessing all perfect squares up to 1000*1000 to quickly check if a given string length could correspond to a square matrix.
           Then for each input string, we validate:
           - If the string length is not a perfect square, it's impossible to form a valid square matrix -> "No"
           - Otherwise, we try to build a square matrix of that side length using string characters,
             and verify that:
             - The edges are all '1' and internal cells are all '0'
           Time Complexity: O(n) for preprocessing + O(sqrt(n)) for each query
           Space Complexity: O(1000^2) = O(10^6)

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: integer n (length of string)
  - Line 2: binary string s of length n

Output Format:
For each test case, print "Yes" if the string could have been formed from a square beautiful matrix, else "No".
*/

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::map<long, long> msqrt;
  // Precompute all perfect squares up to 1000*1000 and map them to their square root
  for (long p = 1; p <= 1000; p++) {
    msqrt[p * p] = p;
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::string s;
    std::cin >> s;
    // Check if the string length is a perfect square
    if (!msqrt.count(s.size())) {
      puts("No");
      continue;
    }
    long sz = msqrt[s.size()];
    bool possible(true);
    // Iterate through each cell in the matrix, and validate edge vs interior condition
    for (long row = 0; possible && row < sz; row++) {
      for (long col = 0; possible && col < sz; col++) {
        bool digit = (s[row * sz + col] == '1');
        bool edge = (row == 0 || row == sz - 1 || col == 0 || col == sz - 1);
        // For a valid beautiful matrix, an edge should be '1', and an interior should be '0'
        if (edge ^ digit) {
          possible = false;
        }
      }
    }
    puts(possible ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/