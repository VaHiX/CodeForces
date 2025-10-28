// Problem: CF 1883 B - Chemistry
// https://codeforces.com/contest/1883/problem/B

/*
B. Chemistry
Algorithm: Greedy + Character Frequency Counting
Time Complexity: O(n) per test case, where n is the length of string s
Space Complexity: O(1) since we use a fixed-size array of 26 elements

The approach:
1. For each test case, read the string and number of characters to remove (k).
2. Count frequency of each character in the string.
3. Count how many characters have odd frequencies (these are candidates for the center of palindrome).
4. Since we can remove exactly k characters, the number of remaining characters is (n - k).
5. For a palindrome, at most one character may have an odd count (to place in the middle).
6. If (n - k) is even, then all characters must appear an even number of times.
   If (n - k) is odd, exactly one character can have an odd count.
7. The minimum number of characters to remove to satisfy palindrome condition is:
   (number of odd frequencies) - 1 if (n - k) is odd, or 0 if it's even.
8. If this value is <= k, then we can form a palindrome.

Key insight: Even though we don't know which characters to remove, we only care about
the parity of character counts. We can greedily adjust by removing enough characters
to reduce the number of odd counts to at most one (if needed).
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  const int B = 26; // Size of alphabet (lowercase a-z)
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k; // Read length of string and number of characters to remove
    std::string s;
    std::cin >> s; // Read input string
    int v[B] = {0}; // Array to store frequency of each character (a-z)
    for (long p = 0; p < s.size(); p++) {
      ++v[s[p] - 'a']; // Count frequency of each character
    }
    long cnt(0); // Count of characters with odd frequencies
    for (long p = 0; p < B; p++) {
      cnt += v[p] % 2; // Increment if frequency is odd
    }
    // Check if it's possible to form palindrome after removing exactly k characters
    puts(cnt <= k + 1 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/