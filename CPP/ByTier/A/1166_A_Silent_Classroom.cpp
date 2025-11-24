// Problem: CF 1166 A - Silent Classroom
// https://codeforces.com/contest/1166/problem/A

/*
Problem: A. Silent Classroom
Purpose: Given n students with names starting with certain letters, split them into two classrooms to minimize the number of "chatty" pairs — pairs of students whose names start with the same letter and are in the same classroom.

Algorithm:
- Count how many students have names starting with each letter (a-z).
- For each group of students with names starting with the same letter, compute the minimum number of chatty pairs when split into two classrooms.
- To minimize pairs, try all possible ways to split a group of size `v[p]` into two non-empty groups and choose the split that minimizes total pairs.
- Since each student contributes to a pair if they are in the same classroom, we process each letter's count independently.

Time Complexity: O(n) where n is the number of students (counting names and splitting).
Space Complexity: O(1) as we use fixed-size vector of 26 elements for letters 'a' to 'z'.

*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n;
  std::cin >> n;
  // Vector to store count of students whose names start with each letter (a-z)
  std::vector<long> v('z' - 'a' + 1, 0);
  while (n--) {
    std::string s;
    std::cin >> s;
    ++v[s[0] - 'a']; // Increment count for the first letter of current name
  }
  long long cnt(0); // Total minimum chatty pairs across all classrooms
  for (long p = 0; p < v.size(); p++) {
    // For each group size v[p], split into two parts a and b such that a + b = v[p]
    // Try to minimize the sum of combinations C(a,2) + C(b,2)
    long a = v[p] / 2;
    long b = v[p] - a;
    // Add minimum possible pairs for this group
    cnt += a * (a - 1) / 2 + b * (b - 1) / 2;
  }
  printf("%lld\n", cnt); // Print resulting minimum number of chatty pairs
  return 0;
}


// https://github.com/VaHiX/codeForces/