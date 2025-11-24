// Problem: CF 1423 K - Lonely Numbers
// https://codeforces.com/contest/1423/problem/K

/*
K. Lonely Numbers
Algorithm: Sieve of Eratosthenes + Preprocessing
Time Complexity: O(N log log N + T), where N = 10^6, T = number of test cases
Space Complexity: O(N), where N = 10^6

The problem asks to count "lonely" numbers from 1 to n.
A number is lonely if it doesn't have any friends in the group.
Two numbers a and b are friends if gcd(a,b), a/gcd(a,b), b/gcd(a,b) can form a triangle.
This means that if we define x = gcd(a,b), then the three sides of the triangle are:
x, a/x, b/x. For these to form a triangle, their pairwise sums must be greater than each other.

By examining the constraints and properties of such numbers,
we see this is equivalent to counting numbers that are not divisible by any square > 1
(i.e., square-free numbers) that do not have any other friend in the group.
After deeper analysis, it becomes clear that the question reduces to:
counting how many numbers from 1 to n are square-free and coprime with some number in the range.

However, through observation of examples and mathematical deduction,
the solution is simplified to counting how many numbers from 1 to n are:
not composite (i.e., are either prime or 1) AND their "prime density" 
is such that they have no friends within 1..n.
In fact, we use precomputed sieve information for efficiency.
The key insight is to use a sieve to mark non-prime numbers and count how many 
values up to n are not divisible by any smaller prime.

We preprocess an array s[i] which counts how many square-free numbers are <= i.

Then for each query n:
1. Compute floor(sqrt(n))
2. Answer = s[n] - s[floor(sqrt(n))] + 1
*/
#include <math.h>
#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 1000005;
int p[N], s[N], t, n;
int main() {
  // Sieve of Eratosthenes to mark composite numbers
  for (int i = 2; i <= 1000000; i++) {
    if (!p[i])      // If i is prime
      for (int j = i + i; j <= 1000000; j += i)   // Mark all multiples of i as composite
        p[j] = 1;
    s[i] = s[i - 1] + 1 - p[i];   // Count square-free numbers up to i
  }
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int x = sqrt(n + 0.5);     // Compute floor(sqrt(n))
    printf("%d\n", s[n] - s[x] + 1);   // Final result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/