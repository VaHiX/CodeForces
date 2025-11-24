// Problem: CF 1583 A - Windblume Ode
// https://codeforces.com/contest/1583/problem/A

#include <cstdio>
#include <vector>
// Flowerbox: 
// Problem: Find the largest subset of an array such that its sum is composite.
// Algorithm: 
//   1. Compute the total sum of all elements.
//   2. If the sum is composite, return the full array.
//   3. If the sum is prime, find an element whose removal makes the sum composite.
//   4. Output the indices of the chosen subset.
// Time Complexity: O(n * sqrt(S)) where S is the sum of all elements (up to 200*100 = 20000),
//   thus O(n * sqrt(20000)) ≈ O(n * 141). 
// Space Complexity: O(n) for storing the array.
bool isPrime(long u) {
  if (u <= 1) {
    return false;
  }
  for (long p = 2; p * p <= u; p++) {
    if (u % p == 0) {
      return false;
    }
  }
  return true;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    long sum(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      sum += a[p];
    }
    long idx(-1);
    bool check = isPrime(sum);
    if (check) {
      for (long p = 0; p < n; p++) {
        if (!isPrime(sum - a[p])) {
          idx = p;
          break;
        }
      }
    }
    printf("%ld\n", n - check);
    for (long p = 0; p < n; p++) {
      if (p == idx) {
        continue;
      }
      printf("%ld ", p + 1);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/