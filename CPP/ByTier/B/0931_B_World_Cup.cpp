// Problem: CF 931 B - World Cup
// https://codeforces.com/contest/931/problem/B

#include <cstdio>
int main() {
  long n, a, b;
  scanf("%ld %ld %ld", &n, &a, &b);
  --a;  // Convert to 0-based indexing
  --b;
  long m(n), h(0);
  while (m /= 2) {
    ++h;  // Calculate the number of rounds needed to finish the tournament
  };
  long x(a ^ b), t(n / 2), r(h);  // x is XOR of adjusted team indices, t is half the number of teams, r is round counter
  while (t > x) {  // Loop until we find the round where teams can meet
    --r;
    t /= 2;  // Move to the next round
  }
  if (r == h) {
    puts("Final!");  // Teams meet in the final round
  } else {
    printf("%ld\n", r);  // Output the round number
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/