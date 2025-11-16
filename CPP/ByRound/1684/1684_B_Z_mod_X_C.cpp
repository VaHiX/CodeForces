// Problem: CF 1684 B - Z mod X = C
// https://codeforces.com/contest/1684/problem/B

/*
Algorithm/Technique: Direct Construction

The problem asks to find x, y, z such that:
- x mod y = a
- y mod z = b  
- z mod x = c

We can construct a solution by setting:
- z = c
- y = b + c
- x = a + b + c

This works because:
- x mod y = (a + b + c) mod (b + c) = a (since a < b, a < b + c, so a + b + c = a + (b + c) => a + b + c ≡ a mod (b + c))
- y mod z = (b + c) mod c = b (since b < c, b + c ≡ b mod c)
- z mod x = c mod (a + b + c) = c (since c < a + b + c, so c ≡ c mod (a + b + c))

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld %lld %lld\n", a + b + c, b + c, c);
  }
}


// https://github.com/VaHiX/CodeForces/