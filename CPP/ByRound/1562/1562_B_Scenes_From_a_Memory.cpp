// Problem: CF 1562 B - Scenes From a Memory
// https://codeforces.com/contest/1562/problem/B

/*
Algorithm: Prime Number Identification and Digit Removal
Approach:
1. Precompute composite numbers up to 100 using Sieve of Eratosthenes.
2. For each test case:
   - Check if any single digit in the number is 1, 4, 6, 8, or 9 (these are not prime).
     If found, output that single digit as it will form a composite number.
   - Otherwise, check all pairs of digits to form two-digit numbers.
     If a two-digit composite number is found, output it.
Time Complexity: O(k * k) per test case, where k is the number of digits.
Space Complexity: O(1) as we use a fixed-size boolean array for primes up to 100.

The code checks for the smallest number of digits to remove such that
the remaining number is composite:
- If any single digit is 1,4,6,8,9, it's not prime, so removing others is enough.
- Otherwise, try two-digit combinations for the first valid composite number.
*/

#include <iostream>
#include <string>

int main() {
  bool composite[100] = {0};
  composite[1] = true;
  for (long p = 2; p < 11; p++) {
    if (composite[p]) {
      continue;
    }
    for (long q = 2 * p; q < 100; q += p) {
      composite[q] = 1;
    }
  }
  long t;
  std::cin >> t;
  while (t--) {
    long k;
    std::cin >> k;
    std::string s;
    std::cin >> s;
    int res(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1' || s[p] == '4' || s[p] == '6' || s[p] == '8' ||
          s[p] == '9') {
        res = s[p] - '0'; // Found a single digit that's not prime
      }
    }
    if (res) {
      std::cout << 1 << std::endl << res << std::endl;
      continue;
    }
    for (long p = 0; !res && p < s.size(); p++) {
      for (long q = p + 1; !res && q < s.size(); q++) {
        long x = 10 * (s[p] - '0') + (s[q] - '0'); // Form two-digit number
        if (composite[x]) {
          res = x;
        }
      }
    }
    std::cout << 2 << std::endl << res << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/