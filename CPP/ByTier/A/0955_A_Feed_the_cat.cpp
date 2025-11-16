// Problem: CF 955 A - Feed the cat
// https://codeforces.com/contest/955/problem/A

#include <cstdio>
// Purpose: Determine the minimum cost for Andrew to feed his cat by buying buns,
// considering a discount after 20:00. The cat's hunger increases over time.
// Algorithm: 
//   - Calculate hunger at current time and at 20:00
//   - If already past 20:00, buy enough buns at discounted price
//   - Otherwise, compare cost of buying now vs. buying at 20:00 with hunger increase
// Time Complexity: O(1) - constant time operations
// Space Complexity: O(1) - only using a few variables
int main() {
  long hh, mm;
  scanf("%ld %ld", &hh, &mm);
  long h, d, c, n;
  scanf("%ld %ld %ld %ld", &h, &d, &c, &n);
  double cost(0.0);
  if (hh >= 20) {
    // If it's already past 20:00, buy buns at 20% discount
    cost = ((h + n - 1) / n) * c * 0.8;
  } else {
    // Calculate time until 20:00 in minutes
    long dur = 20 * 60 - (hh * 60 + mm);
    // Cost if buying now (no discount)
    long cnow = ((h + n - 1) / n) * c;
    // Cost if buying at 20:00 (with discount) after hunger increases
    long cafter = ((h + dur * d + n - 1) / n) * c * 0.8;
    // Choose the minimum cost option
    cost = (cnow < cafter) ? cnow : cafter;
  }
  printf("%.5lf\n", cost);
  return 0;
}


// https://github.com/VaHiX/CodeForces/