// Problem: CF 1504 B - Flip the Bits
// https://codeforces.com/contest/1504/problem/B

/*
B. Flip the Bits
Algorithms/Techniques: Greedy approach with prefix balance tracking

Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1) additional space (not counting input storage)

The problem involves transforming string 'a' into string 'b' using operations that flip prefixes 
with equal numbers of 0s and 1s. The key insight is to track the balance (difference between count of 1s and 0s) 
as we iterate through the strings. If at any point the condition (a[p] == b[p]) != (a[p+1] == b[p+1]) is violated
and the balance is non-zero, it's impossible to transform the string.
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
    std::string a, b;
    std::cin >> a >> b;
    a += '0';  // Append dummy '0' to handle boundary condition
    b += '0';
    long cnt(0);  // Tracks the balance of 1s and 0s in prefix
    bool ans(true);
    for (long p = 0; p < a.size(); p++) {
      cnt += (a[p] == '1') - (a[p] == '0');  // Update balance: +1 for '1', -1 for '0'
      if ((a[p] == b[p]) != (a[p + 1] == b[p + 1]) && cnt) {  // If a and b differ at position p, and balance is non-zero
        ans = false;
        break;
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/