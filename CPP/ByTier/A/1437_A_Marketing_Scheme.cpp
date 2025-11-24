// Problem: CF 1437 A - Marketing Scheme
// https://codeforces.com/contest/1437/problem/A

/*
A. Marketing Scheme
Algorithms/Techniques: Mathematical analysis, greedy strategy simulation

Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem reduces to checking whether there exists a pack size `a` such that 
for all x in [l, r], the customer buys more than x cans due to the greedy rule:
- If x % a >= a/2, then x % a cans are bought as a full pack instead.
- This means we need x + (x % a) > x, i.e., x % a > 0 and x % a >= a/2.
- For all x in [l, r], this implies we must find an a such that for every x,
  if x % a != 0, then x % a >= a/2.
- If x = r, x%a would be smallest when a is large. To ensure condition holds for 
  all values from l to r, we check the worst case, which is when r % a is just 
  above a/2. If r + 1 <= 2 * l, there always exists an a where the greedy rule 
  triggers in such a way as to satisfy the condition.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    puts(r + 1 <= 2 * l ? "YES" : "NO"); // Check condition for valid pack size
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/