// Problem: CF 1015 B - Obtaining the String
// https://codeforces.com/contest/1015/problem/B

/*
B. Obtaining the String
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
You are given two strings s and t of equal length n. You can swap adjacent characters in s any number of times.
The goal is to transform s into t using at most 10^4 swaps.

Algorithm:
1. First check if transformation is possible by comparing character frequencies in both strings.
2. For each position in the string, if s[i] != t[i]:
   - Find where t[i] exists in s starting from position i
   - Bubble-sort that character to position i using adjacent swaps
3. Maintain a list of swap operations (1-indexed positions of left elements in swaps)

Time Complexity: O(n^2) - due to nested loops for bubble sorting each mismatched character
Space Complexity: O(n) - for frequency vector and move sequence vector

Input:
n - length of strings
s - source string
t - target string

Output:
If transformation is impossible, print "-1"
Else, print number of operations followed by operation indices (1-indexed)
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  const long N = 26;
  long n;
  std::cin >> n;
  std::string s, t;
  std::cin >> s >> t;
  std::vector<long> v(N, 0); // Frequency vector for characters 'a' to 'z'
  for (long p = 0; p < s.size(); p++) {
    ++v[s[p] - 'a']; // Count characters in s
  }
  for (long p = 0; p < t.size(); p++) {
    --v[t[p] - 'a']; // Subtract character count from t
  }
  for (long p = 0; p < N; p++) {
    if (v[p]) { // If any character count is non-zero, strings can't be made equal
      puts("-1");
      return 0;
    }
  }
  std::vector<long> m; // Vector to store swap operations
  long cnt(0);
  for (long p = 0; p < n; p++) {
    if (s[p] == t[p]) { // If characters match, no need to do anything
      continue;
    }
    long ind(p + 1); // Start looking for character t[p] from position p+1
    while (s[ind] != t[p]) { // Find index of character t[p] in s
      ++ind;
    }
    // Bubble up the character at ind to position p using adjacent swaps
    for (long q = ind; q > p; q--) {
      char x = s[q]; // Swap characters s[q] and s[q-1]
      s[q] = s[q - 1];
      s[q - 1] = x;
      m.push_back(q); // Record the move (1-indexed)
    }
  }
  printf("%ld\n", m.size()); // Print number of moves
  for (long p = 0; p < m.size(); p++) {
    printf("%ld ", m[p]); // Print each move
  }
  puts(""); // New line after moves
  return 0;
}


// https://github.com/VaHiX/codeForces/