// Problem: CF 1425 H - Huge Boxes of Animal Toys
// https://codeforces.com/contest/1425/problem/H

/*
H. Huge Boxes of Animal Toys

Algorithm:
The problem involves determining which boxes can be the final "special box" after a series of operations where toys are sewn together (multiplied) and placed in appropriate boxes based on the result's value range.

Key Insight:
Each operation multiplies two toy values. The sign and magnitude of the product determine the destination box:
- Box 1: (-∞, -1] → negative products
- Box 2: (-1, 0) → negative products with |product| < 1
- Box 3: (0, 1) → positive products with |product| < 1
- Box 4: [1, ∞) → positive products with |product| ≥ 1

Analysis:
We need to find whether it is possible, given the initial counts of toys in each box, for any of the four boxes to become the final box holding the super toy. The approach uses parity and availability of negative/positive numbers from different boxes.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    bool neg = (a + b) % 2;  // true if odd number of negatives from boxes 1 and 2
    bool ltn = (b > 0 || c > 0);  // true if box 2 or 3 has at least one toy
    bool gtn = (a > 0 || d > 0);  // true if box 1 or 4 has at least one toy
    printf((neg && gtn) ? "Ya " : "Tidak ");  // Box 1 can be special if odd negative count and box 1/4 not empty
    printf((neg && ltn) ? "Ya " : "Tidak ");  // Box 2 can be special if odd negative count and box 2/3 not empty
    printf((!neg && ltn) ? "Ya " : "Tidak ");  // Box 3 can be special if even negative count and box 2/3 not empty
    printf((!neg && gtn) ? "Ya\n" : "Tidak\n");  // Box 4 can be special if even negative count and box 1/4 not empty
  }
}


// https://github.com/VaHiX/codeForces/