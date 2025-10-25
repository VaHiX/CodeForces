// Problem: CF 1996 A - Legs
// https://codeforces.com/contest/1996/problem/A

/*
Problem: Minimum number of animals given total legs
Algorithm: Mathematical approach to minimize animals
Time Complexity: O(1) per test case
Space Complexity: O(1)

Since cows have 4 legs and chickens have 2 legs, to minimize the number of animals:
- Use as many cows as possible (4 legs each)
- Use chickens for remaining legs (2 legs each)
- For n legs: n/4 cows + (n%4)/2 chickens
*/

#include <cstdio>
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n; // total number of legs
    scanf("%ld", &n);
    // Calculate minimum animals: (n/4) cows + (n%4)/2 chickens
    printf("%ld\n", (n / 4) + (n % 4) / 2);
  }
}


// https://github.com/VaHiX/codeForces/