// Problem: CF 1221 C - Perfect Team
// https://codeforces.com/contest/1221/problem/C

/* 
C. Perfect Team
Algorithms/Techniques: Greedy approach with mathematical analysis
Time Complexity: O(1) per query
Space Complexity: O(1)

Given c coders, m mathematicians, and x students with no specialization,
we need to form maximum number of perfect teams, each requiring:
- At least one coder
- At least one mathematician  
- Exactly three members total

Strategy:
1. Each team needs 3 members total.
2. We must satisfy the constraint of having at least one coder AND one mathematician per team.
3. If we have c + m + x students total, maximum teams possible is (c + m + x) / 3.
4. However, if we don't have enough coders or mathematicians to fill all teams,
   we are limited by the smaller of c and m.
5. So, answer is min(c, m, (c + m + x) / 3).
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int a, b, c, T;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &a, &b, &c);
    printf("%d\n", min({a, b, (a + b + c) / 3})); // Take minimum of available coders, mathematicians, and total possible teams
  }
}


// https://github.com/VaHiX/codeForces/