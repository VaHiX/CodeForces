// Problem: CF 791 A - Bear and Big Brother
// https://codeforces.com/contest/791/problem/A

/*
 * Problem: Bear and Big Brother
 * Algorithm/Technique: Simulation
 *
 * Time Complexity: O(log(b/a)), since the weight of Limak (a) is tripled and Bob's (b) is doubled each year,
 *                    the ratio a/b decreases exponentially, leading to a logarithmic number of iterations.
 *
 * Space Complexity: O(1), as only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  const int A = 3;  // Limak's weight is tripled each year
  const int B = 2;  // Bob's weight is doubled each year
  int a, b;
  scanf("%d %d", &a, &b);
  int n(0);  // Number of years counter
  while (a <= b) {  // Continue until Limak becomes strictly heavier than Bob
    a *= A;  // Triple Limak's weight
    b *= B;  // Double Bob's weight
    ++n;  // Increment year counter
  }
  printf("%d\n", n);  // Output the number of years
  return 0;
}


// https://github.com/VaHiX/CodeForces/