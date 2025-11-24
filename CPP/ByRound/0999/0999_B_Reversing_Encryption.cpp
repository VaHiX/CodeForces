// Problem: CF 999 B - Reversing Encryption
// https://codeforces.com/contest/999/problem/B

/*
Purpose: Decrypt a string that was encrypted using a specific reversing algorithm.
         The encryption process reverses substrings of lengths that are divisors of the string length,
         in increasing order of divisor values.

Algorithm:
1. Read the length of the string and the encrypted string.
2. Iterate through all integers from 2 to n.
3. For each integer p that divides n (i.e., n % p == 0), reverse the prefix of the string of length p.
4. Output the resulting string.

Time Complexity: O(n^2)
Space Complexity: O(n)
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long n;
  scanf("%ld", &n);
  std::string s;
  std::cin >> s;
  for (long p = 2; p <= n; p++) {
    if (n % p > 0) {
      continue;
    }
    std::reverse(s.begin(), s.begin() + p); // Reverse the prefix of length p
  }
  std::cout << s << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/