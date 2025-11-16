// Problem: CF 1560 A - Dislike of Threes
// https://codeforces.com/contest/1560/problem/A

/*
Algorithm/Techniques: Iterative checking
Time Complexity: O(k * D) where D is the average number of digits in the integers checked
Space Complexity: O(1)

This solution iterates through positive integers starting from 1, checking each one to see
if it's disliked by Polycarp (i.e., divisible by 3 or ends with digit 3).
It counts the numbers that are NOT disliked and returns the k-th such number.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 10101
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
    sf(k);
    int cnt = 0;
    for (i = 1;; i++) {
      // Check if the current number is disliked (divisible by 3 OR ends with 3)
      if (i % 3 == 0 || i % 10 == 3)
        continue; // Skip disliked numbers
      else
        cnt++; // Increment count of liked numbers
      
      // If we've found the k-th liked number, print it and break
      if (cnt == k) {
        pf(i), nl;
        break;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/