// Problem: CF 1323 B - Count Subrectangles
// https://codeforces.com/contest/1323/problem/B

/*
B. Count Subrectangles
time limit per test
1 second
memory limit per test
512 megabytes
input
standard input
output
standard output

You are given an array a of length n and array b of length m both consisting of only integers 0 and 1. Consider a matrix c of size n × m formed by following rule: c_{i, j} = a_i · b_j (i.e. a_i multiplied by b_j). It's easy to see that c consists of only zeroes and ones too.
How many subrectangles of size (area) k consisting only of ones are there in c?
A subrectangle is an intersection of a consecutive (subsequent) segment of rows and a consecutive (subsequent) segment of columns. I.e. consider four integers x_1, x_2, y_1, y_2 (1 ≤ x_1 ≤ x_2 ≤ n, 1 ≤ y_1 ≤ y_2 ≤ m) a subrectangle c[x_1 … x_2][y_1 … y_2] is an intersection of the rows x_1, x_1+1, x_1+2, …, x_2 and the columns y_1, y_1+1, y_1+2, …, y_2.
The size (area) of a subrectangle is the total number of cells in it.

Algorithms/Techniques:
- Prefix sums for efficient range sum queries
- Brute force over possible row segments to find valid column segments that form rectangles of area k

Time Complexity: O(n + m + n * d(k)) where d(k) is the number of divisors of k
Space Complexity: O(n + m)
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  std::vector<ll> a(n), b(m);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  for (ll p = 0; p < m; p++) {
    scanf("%lld", &b[p]);
  }
  
  // Compute prefix sums for array a
  for (ll p = 1; p < n; p++) {
    if (a[p]) {
      a[p] += a[p - 1];
    }
  }
  
  // Compute prefix sums for array b
  for (ll p = 1; p < m; p++) {
    if (b[p]) {
      b[p] += b[p - 1];
    }
  }
  
  ll cnt(0);
  // Iterate through all possible row segments (from index 0 to p inclusive)
  for (ll p = 0; p < n; p++) {
    // Only consider cases where k is divisible by (p + 1) 
    if (k % (p + 1) > 0) {
      continue;
    }
    ll u(p + 1), v(k / (p + 1)); // u = number of rows in segment, v = number of columns needed for area k
    ll w(0), z(0); // w = count of valid row ranges, z = count of valid column ranges
    
    // Count of row segments starting from 0 with length u such that sum(a) >= u (i.e., all elements are 1)
    for (ll q = 0; q < n; q++) {
      if (a[q] >= u) {
        ++w;
      }
    }
    
    // Count of column segments starting from 0 with length v such that sum(b) >= v 
    for (ll q = 0; q < m; q++) {
      if (b[q] >= v) {
        ++z;
      }
    }
    
    cnt += w * z;
  }
  
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/