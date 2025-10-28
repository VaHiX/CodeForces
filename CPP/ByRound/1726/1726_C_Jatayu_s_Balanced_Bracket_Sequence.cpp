// Problem: CF 1726 C - Jatayu's Balanced Bracket Sequence
// https://codeforces.com/contest/1726/problem/C

/*
C. Jatayu's Balanced Bracket Sequence
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Given a balanced bracket sequence of length 2n, construct an undirected graph where each vertex represents a character in the string.
Two vertices i and j are connected if and only if the substring s[i..j] is a balanced bracket sequence.
Return the number of connected components in this graph.

Algorithm:
We observe that a substring s[i..j] is balanced if and only if the prefix difference (number of '(' minus number of ')') remains non-negative throughout and equals zero at the end.
For a balanced bracket sequence, the key insight is that we can group segments that form valid subexpressions.
Each time we encounter a `(` followed by another `(` in consecutive positions, it implies a new independent component or a continuation of an existing one.

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding input)

Definitions:
- Balanced bracket sequence: A string of parentheses such that every opening parenthesis has a matching closing one and they are properly nested.
- Subsegment s[i..j]: The continuous substring from index i to j (inclusive).
- Connected component: A subset of vertices such that any two vertices in this set are connected by a path, and no vertex outside the set is connected to any inside.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(1); // Start with at least one component
    for (long p = 1; p < s.size(); p++) {
      // If two consecutive characters are both '(', increase component count
      cnt += (s[p - 1] == '(' && s[p] == '(');
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/