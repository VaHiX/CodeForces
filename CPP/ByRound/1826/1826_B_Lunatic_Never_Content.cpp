// Problem: CF 1826 B - Lunatic Never Content
// https://codeforces.com/contest/1826/problem/B

/*
B. Lunatic Never Content
Algorithm: For each test case, find the largest positive integer x such that f(a, x) is a palindrome.
The key insight is to observe that for f(a, x) to be a palindrome, the elements at symmetric positions must be equal modulo x.
Let’s define diff = a[i] - a[n-1-i], then diff % x must be 0 for all such pairs for the array to remain palindromic under modulo x.
Hence, we look for the GCD of all such absolute differences. If this GCD is 0 (i.e., the difference is always 0), 
then the array is already palindromic regardless of x -> x can be arbitrarily large so output is 0.

Time Complexity: O(n * log(max(a))) per test case, due to GCD computation.
Space Complexity: O(n) for storing the input array.
*/

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return b ? gcd(b, a % b) : a; }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long res(0);
    // Iterate through symmetric pairs of elements
    for (long p = 0; p < n - p; p++) {
      long diff = a[p] - a[n - 1 - p];
      if (diff < 0) {
        diff = -diff;
      }
      res = gcd(diff, res);
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/