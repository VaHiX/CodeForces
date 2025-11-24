// Problem: CF 1236 A - Stones
// https://codeforces.com/contest/1236/problem/A

/*
Problem: A. Stones
Purpose: Maximize the number of stones Alice can collect by performing two allowed operations:
         1. Take 1 stone from heap1 and 2 stones from heap2
         2. Take 1 stone from heap2 and 2 stones from heap3

Algorithms/Techniques:
- Greedy approach with case analysis
- Try different combinations of operations to maximize collected stones

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a constant amount of extra space

Approach:
The solution tries two different strategies:
1. Prioritize operation 1 (a,b) first, then operation 2 (b,c)
2. Prioritize operation 2 (b,c) first, then operation 1 (a,b)
Then take the maximum result from both approaches.
*/

#include <stdio.h>
#include <algorithm>

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
#define pp pair<ll, ll>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  int a, b, c;
  sf(t); // Read number of test cases
  while (t--) {
    sff(a, b); // Read a and b
    sf(c); // Read c
    int ans = 0, cnt; // Initialize answer and counter
    int x = min(a, b / 2); // Try to do as many operation 1 as possible (a, b/2)
    int rem = b - (2 * x); // Remaining stones in heap2 after doing operation 1
    cnt = x + 2 * x; // Count stones taken from all three heaps (x from heap1, 2*x from heap2)
    x = min(rem, c / 2); // Try to do as many operation 2 as possible with remaining b and c
    cnt += x + 2 * x; // Add stones taken from remaining heaps
    ans = cnt; // Save this result
    cnt = 0;
    x = min(b, c / 2); // Try to do as many operation 2 as possible (b, c/2)
    rem = b - x; // Remaining stones in heap2 after doing operation 2
    cnt = x + 2 * x; // Count stones from this sequence
    x = min(rem / 2, a); // Try to do operation 1 with remaining a and heap1
    cnt += x + 2 * x; // Add the stones taken from remaining heaps
    ans = max(ans, cnt); // Take maximum of both approaches
    pf(ans); // Print final answer
    nl; // Print newline
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/