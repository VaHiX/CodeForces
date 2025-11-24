// Problem: CF 1422 A - Fence
// https://codeforces.com/contest/1422/problem/A

/*
Purpose: This code solves the problem of finding a valid integer length for the fourth side of a quadrilateral,
         given three sides 'a', 'b', and 'c'. The goal is to ensure that the four sides can form a valid
         non-degenerate simple quadrilateral.

Algorithm/Techniques:
- The key observation is that for any quadrilateral, the sum of all four sides must be greater than twice the length
  of any one side. This is a necessary condition for forming a valid quadrilateral (quadrilateral inequality).
- To ensure the fourth side 'd' works, the easiest approach is to pick d such that d = a + b + c - 2.
  This choice guarantees that d satisfies the required conditions for quadrilateral formation.

Time Complexity: O(t), where t is the number of test cases. Each test case processes in constant time.
Space Complexity: O(1), as we only use a constant amount of extra space.

*/
#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld\n", a + b + c - 2);  // Valid choice for d ensuring quadrilateral validity
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/