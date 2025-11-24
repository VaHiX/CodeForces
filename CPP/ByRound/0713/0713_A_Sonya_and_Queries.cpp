// Problem: CF 713 A - Sonya and Queries
// https://codeforces.com/contest/713/problem/A

/*
 * Problem: Sonya and Queries
 * 
 * Purpose: This code handles a multiset of integers with operations to add, remove, and query based on digit parity patterns.
 * 
 * Algorithm:
 * - Use a map to store the count of numbers matching each pattern.
 * - For each number, convert it to a "pattern number" by replacing each digit with its parity (0 for even, 1 for odd).
 * - Store these pattern numbers in a map to allow efficient counting, insertion, and deletion.
 * 
 * Time Complexity: O(t * log t) where t is the number of operations.
 *   - Each map operation (insert, find, update) takes O(log t) time.
 *   - Conversion of a number to its pattern takes O(log(max_number)) which is bounded by 18 digits, so constant time.
 * 
 * Space Complexity: O(n) where n is the number of distinct pattern numbers stored.
 * 
 * Techniques:
 * - Pattern matching via digit parity conversion.
 * - Map-based frequency counting for efficient query resolution.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// Converts a number to its parity pattern representation
// Each digit is replaced by 0 if even, 1 if odd
long long convert(long long x) {
  std::vector<int> v;
  while (x > 0) {
    v.push_back((x % 10) % 2); // get parity of last digit
    x /= 10;
  }
  std::reverse(v.begin(), v.end()); // reverse to get left-to-right order
  long long ans(0);
  for (int p = 0; p < v.size(); p++) {
    ans = 2 * ans + v[p]; // build binary number from parity bits
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::map<long long, long> m; // map to store pattern -> count
  long t;
  std::cin >> t;
  while (t--) {
    char c;
    long long a;
    std::cin >> c >> a;
    long long pat = convert(a); // get pattern for the number
    
    if (c == '+') {
      // Add the pattern to map if not present, then increment its count
      if (m.count(pat) <= 0) {
        m[pat] = 0;
      }
      ++m[pat];
    } else if (c == '-') {
      // Decrement the count of the pattern
      --m[pat];
    } else if (c == '?') {
      // Answer the query by printing count of matching patterns
      std::cout << m[pat] << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/