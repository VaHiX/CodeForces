// Problem: CF 621 C - Wet Shark and Flowers
// https://codeforces.com/contest/621/problem/C

/*
Flowerbox:
Problem: Wet Shark and Flowers
Algorithms/Techniques: Probability, Inclusion-Exclusion Principle, Modular Arithmetic
Time Complexity: O(n)
Space Complexity: O(n)

This code calculates the expected total amount of money sharks receive based on the
condition that the product of flowers grown by neighboring sharks is divisible by a prime p.
The solution uses the linearity of expectation and computes the probability that two
neighboring sharks both grow a number of flowers divisible by p.

Key idea:
- For each shark, compute the probability that it grows a number of flowers divisible by p
- For each pair of neighboring sharks, compute the probability that both grow numbers divisible by p
- Use inclusion-exclusion to calculate expected contribution from each pair
- Sum up contributions for all pairs of neighbors
*/

#include <cstdio>
#include <vector>
int main() {
  const double R = 1000.0; // Reward per shark per neighbor pair satisfying condition
  long n, m; // n: number of sharks, m: prime number p
  scanf("%ld %ld", &n, &m);
  std::vector<double> pr(n, 0.0); // pr[i] stores probability that i-th shark's flower count is divisible by p
  for (long p = 0; p < n; p++) {
    long x, y; // Range [x, y] for shark p
    scanf("%ld %ld", &x, &y);
    // Find the smallest multiple of m >= x
    long left = (1 + (x - 1) / m) * m;
    // Find the largest multiple of m <= y
    long right = (y / m) * m;
    // Count how many multiples of m exist in [x, y]
    long cnt = (1 + (right - left) / m);
    // Probability that shark p grows a number divisible by m (i.e., by p)
    pr[p] = 1.0 * cnt / (y - x + 1);
  }
  double total(0.0); // Expected total reward
  for (long p = 0; p < n; p++) {
    long q = (p + 1) % n; // q is the next shark in circular order
    // Probability that at least one of the two neighbors has a flower count divisible by p
    // Using inclusion-exclusion principle:
    // P(A or B) = P(A) + P(B) - P(A and B)
    // But we're calculating E[reward] = 2*R*(1 - P(both not divisible))
    total += 2 * R * (1 - (1 - pr[p]) * (1 - pr[q]));
  }
  printf("%.8lf\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/