// Problem: CF 996 D - Suit and Tie
// https://codeforces.com/contest/996/problem/D

/*
Algorithm: Greedy with Adjacent Swaps
Approach:
- Iterate through the array in steps of 2 (i += 2).
- For each pair at positions i and i+1:
  - If they are already a couple (a[i] == a[i+1]), continue.
  - Else, find the partner of a[i] (let's call it 'm') in the remaining array.
  - Calculate the number of adjacent swaps needed to move 'm' from its current position to position i+1.
  - Perform the swaps by shifting elements to the left.

Time Complexity: O(n^2) - In worst case, for each element we might need to scan the rest of the array and perform shifts.
Space Complexity: O(1) - Only a constant amount of additional space used (excluding input array).

*/
#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 200100
#define inf 100000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;
int main() {
  int i, j, k;
  int n, m, r;
  sf(n);
  n *= 2;
  int a[n];
  for (i = 0; i < n; i++)
    sf(a[i]);
  int cnt = 0;
  for (i = 0; i < n; i += 2) {
    if (a[i] == a[i + 1])
      continue;
    for (j = i + 1; j < n; j++) {
      if (a[j] == a[i])
        break;
    }
    cnt += ((j + 1) - (i + 2));  // Number of adjacent swaps needed to bring a[j] to position i+1
    m = a[j];
    for (k = j; k >= i + 2; k--)
      a[k] = a[k - 1];  // Shift elements to the left
    a[i + 1] = m;  // Place the partner at the correct position
  }
  pf(cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/