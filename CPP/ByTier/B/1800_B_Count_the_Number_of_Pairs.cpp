// Problem: CF 1800 B - Count the Number of Pairs
// https://codeforces.com/contest/1800/problem/B

/*
B. Count the Number of Pairs
Algorithm: Greedy with character frequency counting and pairing optimization
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1) since we use a fixed-size array of 26 elements

The solution works by:
1. Counting lowercase and uppercase letters in a frequency array (positive for lowercase, negative for uppercase)
2. Pairing existing compatible pairs immediately
3. Using remaining operations to create new pairs from unpaired characters
*/

#include <iostream>
#include <string>

int main() {
  const int B = 26;
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long v[B] = {0}; // Frequency array: positive for lowercase, negative for uppercase
    long ans(0);
    for (long p = 0; p < n; p++) {
      char c = s[p];
      if ('a' <= c && c <= 'z') {
        int idx = c - 'a';
        if (v[idx] < 0) { // If we have a matching uppercase letter already
          ++ans;
        }
        ++v[idx]; // Increment lowercase count
      } else if ('A' <= c && c <= 'Z') {
        int idx = c - 'A';
        if (v[idx] > 0) { // If we have a matching lowercase letter already
          ++ans;
        }
        --v[idx]; // Decrement uppercase count
      }
    }
    for (long p = 0; p < B; p++) {
      long cur = v[p] / 2; // Calculate how many pairs we can make with the current character
      cur = (cur < 0) ? -cur : cur; // Take absolute value to treat both cases equally
      cur = (cur < k ? cur : k); // Use minimum of possible pairs and remaining operations
      ans += cur;
      k -= cur; // Deduct used operations
    }
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/