// Problem: CF 900 B - Position in Fraction
// https://codeforces.com/contest/900/problem/B

/*
 * Problem: Find the first occurrence of digit 'c' in the decimal expansion of fraction a/b.
 * Algorithm: Simulation of long division with cycle detection.
 * Time Complexity: O(b), where b is the denominator, since we can have at most b-1 unique remainders.
 * Space Complexity: O(b), for storing the set of previously seen remainders.
 *
 * Techniques:
 * - Simulate decimal expansion using long division
 * - Use a set to detect cycles in the remainder sequence
 * - Stop when digit 'c' is found or a cycle is detected
 */

#include <iostream>
#include <set>
#include <utility>

int main() {
  long a, b, c;
  std::cin >> a >> b >> c;
  a %= b;  // Start with the remainder after the integer part
  long cnt(1);  // Position counter starting from 1 after decimal point
  std::set<std::pair<long, long>> s;  // Set to store seen (remainder, denominator) pairs for cycle detection
  while (true) {
    a *= 10;  // Multiply remainder by 10 to get next digit
    if (a / b == c) {  // Check if the current digit matches target digit 'c'
      break;
    }
    ++cnt;  // Increment position counter
    a %= b;  // Update remainder
    std::pair<long, long> f = std::make_pair(a, b);  // Create pair of current remainder and denominator
    if (s.count(f)) {  // If we've seen this remainder before, a cycle exists
      cnt = -1;  // Mark as not found
      break;
    }
    s.insert(f);  // Store the current remainder
  }
  std::cout << cnt << std::endl;  // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/