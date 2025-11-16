// Problem: CF 1337 A - Ichihime and Triangle
// https://codeforces.com/contest/1337/problem/A

/*
Purpose: This code solves the problem of finding three integers x, y, z that can form a valid triangle,
         given constraints on their ranges. The approach is to select values that are likely to satisfy
         the triangle inequality (sum of any two sides must be greater than the third side).

Algorithms/Techniques: Greedy selection based on given constraints.
                       Since a <= b <= c <= d, choosing b, c, c ensures:
                       - b is within [a, b]
                       - c is within [b, c]
                       - c is within [c, d]
                       Additionally, this selection often satisfies triangle inequality.

Time Complexity: O(t), where t is the number of test cases. Each test case is processed in constant time.
Space Complexity: O(1), only a constant amount of extra space is used.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    printf("%ld %ld %ld\n", b, c, c);  // Select b, c, c as a valid triangle candidate
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/