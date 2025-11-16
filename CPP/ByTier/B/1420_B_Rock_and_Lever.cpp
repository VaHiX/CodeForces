// Problem: CF 1420 B - Rock and Lever
// https://codeforces.com/contest/1420/problem/B

/*
B. Rock and Lever
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task: Count pairs (i,j) such that i < j and a[i] & a[j] >= a[i] ^ a[j].

Algorithm:
- For each number, compute its bit level (number of divisions by 2 until it becomes 1).
- Use a frequency vector to count how many numbers have been seen at each bit level.
- For each new number, check how many previous numbers have the same bit level.
- This works because if two numbers have the same bit level, their bitwise AND is greater than or equal to their XOR.

Time Complexity: O(n * log(max(a[i]))) where n <= 1e5 and max(a[i]) <= 1e9
Space Complexity: O(log(max(a[i]))), i.e., O(30) = O(1) since log2(1e9) < 30
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    std::vector<ll> v(67, 0); // Track count of numbers at each bit level
    ll n;
    scanf("%lld", &n);
    ll res(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ll cnt(0);
      while (x > 1) {
        x /= 2;
        ++cnt;
      }
      // cnt is the bit level of x
      res += v[cnt]++; // Add previous count of same bit level numbers to result
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/