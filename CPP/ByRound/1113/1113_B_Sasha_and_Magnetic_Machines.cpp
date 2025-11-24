// Problem: CF 1113 B - Sasha and Magnetic Machines
// https://codeforces.com/contest/1113/problem/B

#include <cstdio>
#include <vector>
// Flowerbox
/*
Problem: Sasha and Magnetic Machines
Purpose: Given n machines with powers a_i, we can choose two indices i,j and a divisor x of a_i,
         then reduce a_i by x times and increase a_j by x times. Find the minimum total power.
Algorithms/Techniques: Brute force over all pairs (i,j) and divisors of a_i.
Time Complexity: O(n * max(a_i) * sqrt(max(a_i))) where max(a_i) <= 100
Space Complexity: O(n)
*/
int main() {
  long n;
  scanf("%ld", &n);
  long sum(0), mn(101);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    mn = (mn < a[p]) ? mn : a[p]; // Track minimum element
    sum += a[p];
  }
  long diff(0);
  for (long p = 0; p < n; p++) {
    long b = a[p];
    for (long u = 1; u <= b; u++) {
      if (b % u) { // Check if u is a divisor of b
        continue;
      }
      // Calculate change in total sum due to operation
      long tmp = (u - 1) * mn - (u - 1) * b / u;
      diff = (diff < tmp) ? diff : tmp; // Keep track of best gain (most negative)
    }
  }
  printf("%ld\n", sum + diff); // Add the best possible decrease to total
  return 0;
}


// https://github.com/VaHiX/codeForces/