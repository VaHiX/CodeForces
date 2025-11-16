// Problem: CF 1659 B - Bit Flipping
// https://codeforces.com/contest/1659/problem/B

/*
Algorithm/Technique:
- Greedily maximize the lexicographical value by flipping bits from left to right.
- If k is odd, flip all bits once at the beginning to maximize the result.
- Then, for remaining moves, greedily set '0's to '1's from left to right.
- If remaining moves after that are odd, adjust the last bit to maintain parity.
- Time Complexity: O(n) per test case
- Space Complexity: O(n) for the result string and frequency vector

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    
    // If k is odd, flip all bits to maximize lexicographical value
    if (k % 2) {
      for (char &x : s) {
        x = (x == '0' ? '1' : '0');
      }
    }
    
    // Vector to store how many times each bit is selected
    std::vector<long> v(n, 0);
    
    // Greedily set bits from left to right to '1' using available moves
    for (long p = 0; k && p < n; p++) {
      if (s[p] == '1') {
        continue;  // Skip if already '1'
      }
      v[p] = 1;  // Mark that we selected this bit once
      s[p] = '1';  // Flip it to '1'
      --k;  // Decrease remaining moves
    }
    
    // If there are still moves left (k > 0), we need to handle them
    if (k) {
      if (k % 2) {
        // If k is odd, we must adjust the last bit
        s.back() = '0';
      }
      v.back() += k;  // Add all remaining moves to last bit
    }
    
    std::cout << s << std::endl;
    for (long x : v) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/