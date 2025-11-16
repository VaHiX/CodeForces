// Problem: CF 2057 C - Trip to the Olympiad
// https://codeforces.com/contest/2057/problem/C

/*
 * Problem: C. Trip to the Olympiad
 * 
 * Purpose: To find three distinct integers a, b, c within range [l, r] 
 * such that the expression (a⊕b)+(b⊕c)+(a⊕c) is maximized.
 * 
 * Algorithm:
 * - The key insight is to maximize the XOR sum by choosing numbers 
 *   that differ in as many bits as possible at each position.
 * - We compute the highest bit where l and r differ, k.
 * - Then construct a, b, c using this bit to form combinations that 
 *   yield maximum XOR values.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
int T, l, r;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &l, &r);
    int k = 31 - __builtin_clz(l ^ r);  // Find highest differing bit position between l and r
    int a = l | (1 << k) - 1;           // Construct a such that it has 1s from bit k onwards
    printf("%d %d %d\n", a, a + 1, a == l ? r : l);  // Output a, a+1, and either l or r depending on a
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/