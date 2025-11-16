// Problem: CF 1102 A - Integer Sequence Dividing
// https://codeforces.com/contest/1102/problem/A

/*
A. Integer Sequence Dividing
Algorithms/Techniques: Mathematical analysis, parity check

Time Complexity: O(1)
Space Complexity: O(1)

The problem asks to partition the sequence 1,2,...,n into two sets A and B such that 
the absolute difference of their sums is minimized.

Key insight:
- Total sum S = n*(n+1)/2
- To minimize |sum(A) - sum(B)|, we want sum(A) and sum(B) to be as close as possible.
- If S is even, we can split into two equal parts (difference = 0).
- If S is odd, the best we can do is have difference = 1.

The approach:
- Compute total sum S = n*(n+1)/2
- Return S % 2, which gives 0 if S is even, else 1.
*/

#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100
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
  ll n, m;
  cin >> n;           // Read input n
  m = n * (n + 1);    // Compute n*(n+1)
  m /= 2;             // Divide by 2 to get sum of sequence 1..n
  cout << (m % 2);    // Output remainder when divided by 2 (0 if even, 1 if odd)
  return 0;
}


// https://github.com/VaHiX/codeForces/