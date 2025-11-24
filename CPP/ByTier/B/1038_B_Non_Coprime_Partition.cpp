// Problem: CF 1038 B - Non-Coprime Partition
// https://codeforces.com/contest/1038/problem/B

/*
B. Non-Coprime Partition
Algorithms/Techniques: Greedy partitioning based on parity
Time Complexity: O(n)
Space Complexity: O(1)

Find out if it is possible to partition the first n positive integers into two 
non-empty disjoint sets S1 and S2 such that:
gcd(sum(S1), sum(S2)) > 1

The approach is:
- If n <= 2, impossible to split into two non-empty sets
- For even n: split odd numbers in one set, even in another
- For odd n: put one more odd number (n) in the first set to make sums non-coprime
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 105
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
  sf(n);
  if (n <= 2) {
    pfs("No\n"); // impossible to partition into two non-empty sets when n <= 2
    return 0;
  }
  pfs("Yes\n");
  if (n % 2 == 0) {
    // For even n, distribute odd and even numbers alternately
    pf(n / 2); // size of first set
    for (i = 1; i <= n; i += 2) // iterate through odd indices
      pf(i);
    nl pf(n / 2); // size of second set
    for (i = 2; i <= n; i += 2) // iterate through even indices
      pf(i);
  } else {
    // For odd n, give one extra odd number to first set to make sums non-coprime
    pf(n / 2 + 1); // size of first set is (n/2 + 1)
    for (i = 1; i <= n; i += 2) // odd numbers in first set
      pf(i);
    nl pf(n / 2); // size of second set
    for (i = 2; i <= n; i += 2) // even numbers in second set
      pf(i);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/