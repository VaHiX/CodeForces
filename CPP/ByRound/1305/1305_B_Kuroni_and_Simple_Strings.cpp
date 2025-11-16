// Problem: CF 1305 B - Kuroni and Simple Strings
// https://codeforces.com/contest/1305/problem/B

/*
B. Kuroni and Simple Strings
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Given a bracket sequence, find the minimum number of operations to remove all simple subsequences.
A simple subsequence is one where first half has only '(', and second half has only ')', with equal lengths.

Algorithm:
1. For each opening bracket, find the corresponding closing bracket that makes a simple subsequence
2. Remove such pairs until no more operations are possible
3. Greedy matching: for every '(' we find the nearest unmatched ')'
4. Track indices of removed brackets

Time Complexity: O(n^2) in worst case due to nested loops for bracket matching
Space Complexity: O(n) for storing indices of brackets to be removed

*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  std::vector<long> v; // Vector to store pairs of indices of brackets to remove
  long idx(s.size());  // Start index from end of string
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == ')') {
      continue; // Skip closing brackets initially
    }
    while (idx > p) { // Search backward for matching closing bracket
      if (s[idx] == ')') {
        v.push_back(1 + p);   // Add 1-based index of opening bracket
        v.push_back(1 + idx--); // Add 1-based index of closing bracket, then decrement idx
        break;
      }
      --idx; // Move backward to find matching ')'
    }
  }
  std::sort(v.begin(), v.end()); // Sort indices in ascending order
  if (v.empty()) {
    std::cout << "0" << std::endl; // No operations needed
  } else {
    std::cout << 1 << std::endl << v.size() << std::endl;
    for (long p = 0; p < v.size(); p++) {
      std::cout << v[p] << " "; // Print indices of brackets to remove
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/