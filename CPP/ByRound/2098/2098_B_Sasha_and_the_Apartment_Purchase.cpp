// Problem: CF 2098 B - Sasha and the Apartment Purchase
// https://codeforces.com/contest/2098/problem/B

/*
B. Sasha and the Apartment Purchase
Algorithms/Techniques: Sorting, Two Pointers, Median Calculation

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the bar positions

Sasha wants to buy an apartment on a street where the houses are numbered from
1 to 10^9 from left to right.
There are n bars on this street, located in houses with numbers a1, a2, ..., an.
Note that there might be multiple bars in the same house.

Sasha is afraid that by the time he buys the apartment, some bars may close, but no more than k bars can close.
For any house with number x, define f(x) as the sum of |x - y| over all open bars y.
Sasha can potentially buy an apartment in a house with number x if and only if it is possible to close at most k bars so that f(x) becomes minimal among all houses.

Determine how many different houses Sasha can potentially buy an apartment in.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read the positions of bars
    }
    sort(a.begin(), a.end()); // Sort bar positions to allow efficient median calculation
    
    // Calculate the number of houses where Sasha can buy an apartment
    // The formula uses the concept of finding optimal median with at most k elements removed
    printf("%ld\n", (a[k + (n - k) / 2] - a[(n - k - 1) / 2]) + 1);
  }
}


// https://github.com/VaHiX/codeForces/