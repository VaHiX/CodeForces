// Problem: CF 1359 A - Berland Poker
// https://codeforces.com/contest/1359/problem/A

/*
A. Berland Poker
Algorithms/Techniques: Greedy approach, mathematical simulation
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem is to distribute m jokers among k players, each getting n/k cards,
and find the maximum points a player can get. Points are calculated as:
x - y, where x is the max jokers in any winner's hand, and y is the max jokers 
among non-winners. If multiple players have the same max jokers, all get 0.
The approach is to try to maximize x for one player while minimizing y for others.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long x = (n / k);  // Each player gets n/k cards
    long a = (x < m) ? x : m;  // Max jokers one player can get (limited by cards per player or total jokers)
    long b = ((m - a) + (k - 2)) / (k - 1);  // Minimizing max jokers among others
    long res = a - b;  // Points = difference between max and second max
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/