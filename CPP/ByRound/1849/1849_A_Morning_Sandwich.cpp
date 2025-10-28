// Problem: CF 1849 A - Morning Sandwich
// https://codeforces.com/contest/1849/problem/A

/*
Problem: A. Morning Sandwich
Purpose: To determine the maximum number of layers in a sandwich given b pieces of bread, c slices of cheese, and h slices of ham.
Algorithms/Techniques: Greedy approach to maximize layers by optimally using available ingredients.

Time Complexity: O(1) per test case
Space Complexity: O(1)

The sandwich must start and end with bread, alternating between bread and fillings (cheese or ham).
Each piece of bread is a layer, and each slice of filling is also a layer.
We can create at most 2*b - 1 layers if we use all breads (since 1st and last are bread, middle ones alternate).
But the number of fillings limits how many alternating layers we can add.

Approach:
- Combine cheese and ham into total fillings: c + h
- If we have more bread than needed for fillings: we can use up to 2 * (c + h) + 1 layers.
- Otherwise, we're constrained by the number of breads. Maximum layers = 2 * b - 1.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long b, c, h;
    scanf("%ld %ld %ld", &b, &c, &h);
    c += h;           // Combine cheese and ham into total fillings
    long ans(0);
    if (b >= c + 1) { // If we have enough bread to accommodate all fillings plus 1 extra bread at the end
      ans = 2 * c + 1; // Use all fillings and alternate with breads, resulting in 2*c + 1 layers
    } else {
      ans = 2 * b - 1; // Constrained by number of breads, max layers = 2*b - 1
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/