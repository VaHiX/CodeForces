// Problem: CF 2104 A - Three Decks
// https://codeforces.com/contest/2104/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long s = a + b + c; // Total number of cards
    long u = (s % 3) ? -1 : (s / 3); // Target number of cards per deck; -1 if not divisible by 3
    puts((u >= a && u >= b) ? "YES" : "NO"); // Check if we can distribute cards such that all decks have 'u' cards
  }
}

// https://github.com/VaHiX/codeForces/