// Problem: CF 769 D - k-Interesting Pairs Of Integers
// https://codeforces.com/contest/769/problem/D

/*
Algorithm: 
- For k = 0: Count pairs of equal elements using combination formula C(n,2) = n*(n-1)/2
- For k > 0: For each unique value 'a', check all values 'b' > 'a' such that XOR of a and b has exactly k bits set
  - Use bit manipulation to count set bits in XOR result
  - Add f[a] * f[b] to result for valid pairs

Time Complexity: O(N + MAX_A^2)
Space Complexity: O(MAX_A)
Where MAX_A = 10007 as per the vector size
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const long N = 1e4 + 7;
  std::vector<ll> f(N, 0);  // Frequency array to store count of each number
  long n, k;
  scanf("%ld %ld", &n, &k);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++f[x];  // Increment frequency of number x
  }
  ll cnt(0);
  if (k == 0) {
    // For k=0, count pairs of identical elements
    for (long p = 0; p < N; p++) {
      cnt += f[p] * (f[p] - 1) / 2;  // C(n,2) combinations
    }
  } else {
    // For k>0, check all pairs (a,b) where a < b and they differ in exactly k bits
    for (long a = 0; a < N; a++) {
      if (f[a] == 0) {
        continue;  // Skip if this number doesn't exist in input
      }
      for (long b = a + 1; b < N; b++) {
        if (f[b] == 0) {
          continue;  // Skip if this number doesn't exist in input
        }
        long x = a ^ b;  // XOR to find differing bits
        int u(0);
        while (x > 0) {
          u += x % 2;  // Count number of 1s (set bits)
          x /= 2;
        }
        if (u == k) {
          cnt += f[a] * f[b];  // Add combinations of pairs
        }
      }
    }
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/