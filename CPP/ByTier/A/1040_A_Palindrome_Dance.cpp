// Problem: CF 1040 A - Palindrome Dance
// https://codeforces.com/contest/1040/problem/A

/*
Problem: A. Palindrome Dance
Purpose: Given n dancers with suits of known colors (0=white, 1=black, 2=unknown), determine the minimum cost to make the suit colors form a palindrome by buying new suits for unknown positions.

Algorithms/Techniques:
- Two-pointer technique to compare elements from both ends
- Greedy approach to minimize cost when choosing colors for unknown positions
- Special handling for odd-length arrays (middle element)

Time Complexity: O(n)
Space Complexity: O(1)

Input:
- n: number of dancers
- a: cost of white suit
- b: cost of black suit
- Array of n integers representing suit colors (0=white, 1=black, 2=unknown)

Output:
- Minimum cost to form palindrome or -1 if impossible
*/

#include <stdio.h>
#include <algorithm>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 55
#define inf 10000000000000000
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pff(n, m) printf("%d %d\n", n, m)
#define pffl(n, m) printf("%I64d %I64d\n", n, m)
#define pfl(n) printf("%I64d\n", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  int a, b;
  sf(n);
  sff(a, b);
  int ar[n];
  for (i = 0; i < n; i++)
    sf(ar[i]);
  int cnt = 0;
  i = 0, j = n - 1;
  while (i < j) {
    if (ar[i] == 2 || ar[j] == 2) {
      // At least one of the positions is unknown (2)
      if (ar[i] == 2 && ar[j] == 2)
        // Both unknown - choose cheaper color twice
        cnt += min(a, b) * 2;
      else if (ar[i] == 2) {
        // i is unknown, j is known
        if (ar[j] == 0)
          // If right position is white, buy white suit for left
          cnt += a;
        else
          // If right position is black, buy black suit for left
          cnt += b;
      } else {
        // j is unknown, i is known
        if (ar[i] == 0)
          // If left position is white, buy white suit for right
          cnt += a;
        else
          // If left position is black, buy black suit for right
          cnt += b;
      }
    } else {
      // Both known - check if they match to form palindrome
      if (ar[i] != ar[j]) {
        pf(-1);
        return 0;
      }
    }
    i++;
    j--;
  }
  if (n % 2) {
    // If odd length, handle middle element
    n = n / 2;
    if (ar[n] == 2)
      // Middle element unknown - buy cheaper color
      cnt += min(a, b);
  }
  pf(cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/