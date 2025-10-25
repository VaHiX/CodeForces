// Problem: CF 1886 D - Monocarp and the Set
// https://codeforces.com/contest/1886/problem/D

/*
 * Problem: Monocarp and the Set
 * 
 * Algorithm/Techniques:
 * - Combinatorial Mathematics with Dynamic Programming
 * - Modular arithmetic and precomputed factorials
 * - Efficient query processing using incremental updates
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 * 
 * Approach:
 * - We process the string s of length n-1 which represents the sequence of operations
 *   (> for max, < for min, ? for neither)
 * - For a valid permutation, we count valid arrangements by considering the constraints
 *   imposed by each character in s
 * - Using precomputed factorials and modular inverse to efficiently calculate combinations
 * - Update answer efficiently when each query changes a character in the string
 * 
 * Key Observations:
 * - First element cannot be ? (since only one element at start)
 * - Each '?' contributes (i-2) possible values, where i is position (1-indexed from 2)
 * - If first character is '?', result is 0 since no valid way to start
 * - Queries update the string and adjust the count accordingly
 */

#include <ctype.h>
#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
static char buf[1 << 22], *p1 = buf, *p2 = buf;
inline int read(void) {
  char ch = getchar();
  int res = 0;
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch))
    res = 10 * res + (ch - '0'), ch = getchar();
  return res;
}
inline char *read(char *s) {
  do
    *s = getchar();
  while (*s != '<' && *s != '?' && *s != '>');
  while (*s == '<' || *s == '?' || *s == '>')
    *++s = getchar();
  *s = '\0';
  return s;
}
const int mod = 998244353;
inline int add(int a, int b) {
  int sum = a + b;
  return sum >= mod ? sum - mod : sum;
}
inline int sub(int a, int b) {
  int sum = a - b;
  return sum < 0 ? sum + mod : sum;
}
inline int mul(int a, int b) { return 1ll * a * b % mod; }
inline int fpow(int x, int exp) {
  int res = 1;
  for (; exp; exp >>= 1, x = mul(x, x))
    if (exp & 1)
      res = mul(res, x);
  return res;
}
const int MAXN = 3e5 + 5;
const int MAXM = 3e5 + 5;
int n, m;
char s[MAXN]; // 1-based string indexing
int fac[MAXN], invfac[MAXN], inv[MAXN];

int main() {
  n = read(), m = read();
  read(s + 2); // Start from index 2, leaving s[1] unused to simplify indexing
  fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = mul(fac[i - 1], i); // Precompute factorials
    
  invfac[n] = fpow(fac[n], mod - 2); // Modular inverse of factorial of n
  for (int i = n - 1; i >= 0; --i)
    invfac[i] = mul(invfac[i + 1], i + 1); // Precompute inverse factorials
    
  inv[0] = 1;
  for (int i = 1; i <= n; ++i)
    inv[i] = mul(fac[i - 1], invfac[i]); // Inverse of factorial of i (used for division)
    
  int ans = 1;
  for (int i = 3; i <= n; ++i) // Start from i=3 (2nd position in 1-based, but indexing starts at 2)
    if (s[i] == '?')
      ans = mul(ans, i - 2); // For each ?, multiply by (i - 2), as it can take any value that keeps it in middle (not max/min)
      
  // Check if s[2] is '?', if so, there's no valid arrangement
  printf("%d\n", s[2] == '?' ? 0 : ans); // Print initial answer

  while (m--) { // Process m queries
    static int i;
    static char c;
    i = read();
    do
      c = getchar();
    while (c != '<' && c != '?' && c != '>');
    ++i; // Convert to 1-indexed
    
    // Adjust answer based on previous character being '?'
    if (s[i] == '?' && i > 2)
      ans = mul(ans, inv[i - 2]); // Undo the multiplication from before
    
    s[i] = c; // Update character in string
    
    // Adjust answer based on new character being '?'
    if (s[i] == '?' && i > 2)
      ans = mul(ans, i - 2); // Multiply by (i - 2) for new '?' value

    printf("%d\n", s[2] == '?' ? 0 : ans); // Output current answer
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/