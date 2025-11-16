// Problem: CF 2026 C - Action Figures
// https://codeforces.com/contest/2026/problem/C

/*
C. Action Figures
Algorithms/Techniques: Greedy algorithm with backward iteration and two-pointer-like logic.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The problem asks to buy n figures, each figure i costs i coins and is available from day i to day n.
Monocarp can visit the shop on some days (given by string s).
If he buys at least 2 figures in one day, he gets the most expensive one for free.
We need to minimize total cost.

The approach:
- Process days from right to left (n to 1)
- Keep track of how many figures we've "collected" so far (j)
- When we see a '1' in s[i], we can buy figures
- If we have collected at least one figure, we can pair them with current figure for a discount
- Otherwise, we just buy the current figure
- The logic computes optimal grouping and cost efficiently.
*/

#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 4e5 + 10;
int t, n;
char s[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%s", &n, s + 1);
    long long ans = 0;
    for (int i = n, j = 0; j < i; i--) // i: current day, j: number of figures collected so far
      if (s[i] == '0') // can't visit shop on day i
        ans += i - j, j = max(j - 1, 0); // pay price for all remaining figures and adjust collection
      else
        ans += ++j; // buy current figure, increment collected count
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/