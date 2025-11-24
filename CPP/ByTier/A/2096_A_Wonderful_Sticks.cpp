// Problem: CF 2096 A - Wonderful Sticks
// https://codeforces.com/contest/2096/problem/A

/*
 * Problem: Wonderful Sticks
 * Algorithm: Greedy approach with two pointers
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the result vector
 *
 * The task is to arrange n distinct sticks of lengths 1 to n in a sequence
 * that satisfies the given string constraints.
 * - '<' means the next stick must be smaller than all previous sticks.
 * - '>' means the next stick must be larger than all previous sticks.
 *
 * Strategy:
 * We use two variables mn (minimum) and mx (maximum), initialized to 1 and n respectively.
 * Traverse the string from right to left. For each '<', assign the current minimum
 * value and increment mn. For each '>', assign the current maximum value and decrement mx.
 * Finally, place the last remaining value at index 0.
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
    long mn(1), mx(n);
    std::vector<long> v(n);
    // Traverse the string from right to left
    for (long p = s.size() - 1; p >= 0; p--) {
      // If '<', assign minimum value and increment mn
      v[p + 1] = (s[p] == '<') ? (mn++) : (mx--);
    }
    // Assign the last remaining value to first position
    v[0] = mx;
    for (long p = 0; p < v.size(); p++) {
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/