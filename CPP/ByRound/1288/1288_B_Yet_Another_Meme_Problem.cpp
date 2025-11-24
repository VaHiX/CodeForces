// Problem: CF 1288 B - Yet Another Meme Problem
// https://codeforces.com/contest/1288/problem/B

/*
B. Yet Another Meme Problem
Algorithms/Techniques: Mathematical analysis to find pattern in equation a*b + a + b = conc(a,b)
Time Complexity: O(log B) per test case
Space Complexity: O(1)

The key insight is that the equation can be rewritten as:
a*b + a + b = conc(a, b)
a*b + a + b + 1 = conc(a, b) + 1
(a+1)*(b+1) = conc(a, b) + 1

For concatenation conc(a,b), if a has d digits, then conc(a,b) = a * 10^len(b) + b.
So (a+1)(b+1) = a * 10^len(b) + b + 1
Expanding the left side:
a*b + a + b + 1 = a * 10^len(b) + b + 1
Simplifying:
a*b + a = a * 10^len(b)
a*(b+1) = a * 10^len(b)
Since a != 0:
b + 1 = 10^len(b)
This means b must be of the form 99...9 (all 9s).
So for a given b, a can be any number from 1 to A.
But we only count valid b's where b <= B and b is all 9s.
We iterate through all possible values of b = 9, 99, 999, ..., up to B.
For each such b, we add A to the count.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll A, B;
    scanf("%lld %lld", &A, &B);
    ll b(9), cnt(0);
    while (b <= B) {
      cnt += A; // For each valid b, we can choose any a from 1 to A
      b = 10 * b + 9; // Generate next number of form 99...9
    }
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/