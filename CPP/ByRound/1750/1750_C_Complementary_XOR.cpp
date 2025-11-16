// Problem: CF 1750 C - Complementary XOR
// https://codeforces.com/contest/1750/problem/C

/*
Algorithm/Technique: 
This solution uses a greedy approach to determine if it is possible to make both strings zero through a series of operations.
Each operation flips a segment of string 'a' and the complement of string 'b' outside that segment.
The key insight is to count mismatches and parity conditions to decide strategy.

Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(n) for storing the input strings and operations.
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 2;
int T, n, s, x;
char a[N], b[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %s %s", &n, a + 1, b + 1); // Read input strings (1-indexed)
    s = x = 0;
    for (int i = 1; i <= n; ++i)
      s += a[i] ^ b[i], x += a[i] & 1; // s counts mismatches, x counts 1s in a
    if (s && s < n) {
      printf("NO\n"); // If there are mismatches but not all, impossible
      continue;
    }
    printf("YES\n");
    if (x % 2 ^ !s) // Check parity condition to determine number of operations
      printf("%d\n", x); // If parity matches, just flip each 1 in a
    else
      printf("%d\n1 1\n1 %d\n2 %d\n", x + 3, n, n); // Otherwise use 3 extra operations
    for (int i = 1; i <= n; ++i)
      if (a[i] & 1) // Output operations to flip each 1 in a
        printf("%d %d\n", i, i);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/