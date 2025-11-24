// Problem: CF 632 B - Alice, Bob, Two Teams
// https://codeforces.com/contest/632/problem/B

/*
Algorithm: 
  We are trying to maximize Bob's strength by considering all possible flips (prefix or suffix) that he can perform after Alice's initial assignment.
  
  Key idea:
    1. Initially, sum up all the strengths of pieces assigned to Bob (marked 'B').
    2. For each possible prefix flip (from left), compute the change in Bob's score.
    3. For each possible suffix flip (from right), compute the change in Bob's score.
    4. The maximum of these values is the answer.

  Time Complexity: O(n)
  Space Complexity: O(1)

  Techniques:
    - Prefix and suffix analysis
    - Running sum optimization to avoid recomputation
*/

#include <algorithm>
#include <stdio.h>
#define ll long long
int main() {
  long n;
  scanf("%ld", &n);
  long a[n];
  char s[n + 1];
  ll out, t = 0, x = 0;
  for (long i = 0; i < n; i++)
    scanf("%ld", &a[i]);
  scanf("%*c%[^\n]", s);
  // Calculate total strength of initial Bob's team
  for (long i = 0; i < n; i++)
    if (s[i] == 'B')
      t += a[i];
  out = t; // Initially, Bob gets all B pieces
  // Check all prefix flips from left to right
  for (long i = 0; i < n; i++) {
    // If current piece is B, flipping it makes it A -> reduce Bob's strength
    // If current piece is A, flipping it makes it B -> increase Bob's strength
    if (s[i] == 'B')
      x -= a[i];
    else
      x += a[i];
    out = std::max(out, t + x); // update best strength Bob can get
  }
  x = 0;
  // Check all suffix flips from right to left
  for (long i = n - 1; i >= 0; i--) {
    // Same logic as above but in reverse direction
    if (s[i] == 'B')
      x -= a[i];
    else
      x += a[i];
    out = std::max(out, t + x);
  }
  printf("%lld", out);
}


// https://github.com/VaHiX/CodeForces/