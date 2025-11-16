// Problem: CF 954 B - String Typing
// https://codeforces.com/contest/954/problem/B

/*
Purpose: 
This code solves the "String Typing" problem where we need to find the minimum number of operations to type a given string on a keyboard. 
We can either append characters one by one or, at most once, copy the current string and append it to itself.

Algorithm:
The approach uses a reverse iteration over the string, checking if the suffix can be duplicated by copying a prefix. 
By doing so, we determine the optimal split point where copying the prefix would be beneficial. 
The algorithm checks for palindromic-like duplication from the end to find the minimum operations required.

Time Complexity: O(n^2), where n is the length of the string. In worst case, for each position, we check a substring of length up to n.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 100010
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb(n) push_back(n)
using namespace std;
int main() {
  int i, j, k;
  int n, m, x, y;
  string s;
  sf(n);
  cin >> s;
  int cnt = 0;
  for (i = n - 1; i >= 0; i--) {
    if ((i + 1) % 2)
      cnt++; // If odd length suffix, add one operation
    else {
      m = i + 1; // Length of suffix
      k = m / 2 - 1; // Index to start comparison from
      j = i; // Index at end of suffix
      x = 0; // Counter for matching characters
      while (k >= 0) {
        if (s[j] == s[k])
          x++, j--, k--; // Match found, decrement indices
        else
          break; // No match, stop checking
      }
      if (x * 2 == m) { // If all characters matched (full duplication)
        cnt += (1 + m / 2); // Increment operations by 1 (copy) + m/2 (remaining chars)
        pf(cnt);
        return 0; // Return early as solution found
      }
      cnt++; // Increment count for current operation
    }
  }
  pf(cnt); // Output final count
  return 0;
}


// https://github.com/VaHiX/CodeForces/