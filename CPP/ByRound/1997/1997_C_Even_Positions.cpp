// Problem: CF 1997 C - Even Positions
// https://codeforces.com/contest/1997/problem/C

/*
C. Even Positions

Purpose:
This code solves the problem of reconstructing a valid bracket sequence from a partially corrupted string,
where only even positions have actual brackets and odd positions are represented by '_'. The goal is to
assign brackets to odd positions such that the resulting sequence is a valid bracket sequence and has minimal cost.
The cost is defined as the sum of distances between matched pairs of brackets.

Algorithm:
- Use a stack-based approach to simulate matching brackets.
- Traverse the string, tracking indices of unmatched opening brackets in a vector.
- When encountering a closing bracket, match it with the most recent unmatched opening bracket,
  and accumulate the distance between their positions.
- For underscores (odd positions), treat them as potential opening or closing brackets,
  depending on what ensures a valid and minimal-cost sequence.

Time Complexity: O(n) where n is the length of the string. Each character is processed once, and operations on the vector are amortized constant time.
Space Complexity: O(n) for storing the vector of indices, which in worst case can hold all opening brackets.

Techniques:
- Stack simulation using a vector to track unmatched opening brackets.
- Greedy matching strategy with minimal cost assignment.
- Efficient use of input/output synchronization for performance.
*/

#include <iostream>
#include <vector>
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
    long cost(0);
    std::vector<long> v; // Vector to store indices of unmatched opening brackets
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '(') {
        v.push_back(p); // Push index of opening bracket onto stack
      } else if (s[p] == ')') {
        cost += p - v.back(); // Match closing bracket with last unmatched opening bracket and accumulate cost
        v.pop_back(); // Remove matched opening bracket from stack
      } else if (v.empty()) {
        // If underscore and no unmatched opening brackets, treat as opening bracket
        v.push_back(p);
      } else {
        // If underscore and there are unmatched opening brackets, match with the most recent one
        cost += p - v.back();
        v.pop_back();
      }
    }
    std::cout << cost << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/