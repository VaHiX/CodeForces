// Problem: CF 1296 B - Food Buying
// https://codeforces.com/contest/1296/problem/B

/*
B. Food Buying
Algorithms/Techniques: Greedy algorithm
Time complexity: O(1) per test case
Space complexity: O(1)

Mishka wants to maximize the number of burles he spends by optimally using cashback.
The key insight is that buying items worth x burles gives a cashback of floor(x/10),
which can be reinvested. The optimal strategy is to keep spending until s < 10,
then spend all remaining s burles. This can be optimized as:
- For s >= 10: total_spent = s + (s - 1) / 9
- For s < 10: total_spent = s
The formula works because: when s >= 10, we can always spend in a way that
gives us maximum benefit from cashback. The term (s-1)/9 is derived from
the sum of cashback received over multiple operations.
*/

#include <cstdio>
int t, s;
int main() {
  for (scanf("%d", &t); t--; printf("%d\n", s + (s - 1) / 9)) // Process each test case and print result
    scanf("%d", &s); // Read the initial amount of burles
}


// https://github.com/VaHiX/codeForces/