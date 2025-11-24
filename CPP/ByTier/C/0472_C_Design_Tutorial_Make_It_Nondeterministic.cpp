// Problem: CF 472 C - Design Tutorial: Make It Nondeterministic
// https://codeforces.com/contest/472/problem/C

/*
 * Task: Determine if a given permutation of people can be achieved by choosing
 *       either first or last name as the handle for each person, such that the
 *       resulting lexicographical order matches the given permutation.
 *
 * Algorithm:
 * - For each person, we store their first and last name, sorted so that first <= second.
 * - We process the permutation step by step, and for each position, we decide whether
 *   to use the first or last name of the current person to maintain lexicographical order.
 * - At each step, we try to use the first name if it maintains the order;
 *   otherwise, we try the last name.
 * - If at any point we cannot maintain the order, we output "NO".
 *
 * Time Complexity: O(n log n) due to sorting names and linear scan
 * Space Complexity: O(n) for storing names and order
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<std::pair<std::string, std::string>> nameVec(n);
  for (long p = 0; p < n; p++) {
    std::string first, second;
    std::cin >> first >> second;
    // Ensure first name is lexicographically smaller or equal to second name
    if (first > second) {
      std::string temp = first;
      first = second;
      second = temp;
    }
    nameVec[p] = std::pair<std::string, std::string>(first, second);
  }
  std::vector<long> order(n);
  for (long p = 0; p < n; p++) {
    long temp;
    std::cin >> temp;
    order[p] = temp - 1;  // Convert to 0-based indexing
  }
  std::string last = nameVec[order[0]].first;  // Start with first name of first person in perm
  std::string result = "YES";
  for (int p = 0; p < n; p++) {
    // Try to use first name if it maintains the order
    if (nameVec[order[p]].first >= last) {
      last = nameVec[order[p]].first;
    } 
    // Otherwise, try using last name
    else if (nameVec[order[p]].second >= last) {
      last = nameVec[order[p]].second;
    } 
    // If neither works, impossible to achieve given order
    else {
      result = "NO";
      break;
    }
  }
  std::cout << result << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/