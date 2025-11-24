// Problem: CF 2005 A - Simple Palindrome
// https://codeforces.com/contest/2005/problem/A

/*
 * Problem: Find a string of length n consisting of vowels only,
 * such that the number of palindromic subsequences is minimized.
 *
 * Approach:
 * To minimize the number of palindromic subsequences, we want to avoid
 * having too many repeated characters in a row. The best strategy is to
 * distribute the vowels as evenly as possible. Since there are 5 vowels,
 * we first assign `n / 5` copies of each vowel, then assign one more
 * copy to the first `n % 5` vowels to balance the distribution.
 *
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1) excluding input/output buffers.
 */

#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

using namespace std;

inline int read() {
  int x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch))
    f = ch == '-', ch = getchar();
  while (isdigit(ch))
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}

const char ch[5] = {'a', 'e', 'i', 'o', 'u'};

void work() {
  int n = read();
  for (int i = 0; i < 5; ++i) {
    // Output n/5 copies of the current vowel
    for (int j = 1; j <= n / 5; ++j) {
      putchar(ch[i]);
    }
    // If there's a remainder, output one more of this vowel
    if (i < n % 5)
      putchar(ch[i]);
  }
  putchar('\n');
}

int main() {
  int Tt = read();
  while (Tt--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/