// Problem: CF 1462 A - Favorite Sequence
// https://codeforces.com/contest/1462/problem/A

/*
Algorithm/Techniques: Two Pointers
Time Complexity: O(n) where n is the length of the sequence
Space Complexity: O(n) for storing the input sequence

The approach uses two pointers, one starting from the beginning (i) and the other from the end (j) of the array.
At each step, we print the element at the left pointer (i) followed by the element at the right pointer (j).
We then move the left pointer forward and the right pointer backward.
If the array has an odd length, the middle element will be printed once at the end.
This simulates the process of reconstructing the original sequence from the whiteboard output.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  sf(t);
  while (t--) {
    sf(n);
    int a[n];
    for (i = 0; i < n; i++)
      sf(a[i]);
    i = 0, j = n - 1;
    while (i < j) {
      pf(a[i]), pfs(" "), pf(a[j]), pfs(" "); // Print elements from both ends
      i++;
      j--;
    }
    if (n % 2)
      pf(a[i]); // Print middle element if odd length
    nl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/