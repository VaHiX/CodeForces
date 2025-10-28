// Problem: CF 1213 B - Bad Prices
// https://codeforces.com/contest/1213/problem/B

/*
B. Bad Prices
Purpose: Count the number of "bad" days where a price is higher than a later lower price.
Algorithm: Traverse from right to left, keeping track of the minimum price seen so far.
           A day is bad if its price is greater than the minimum price seen in future days.
Time Complexity: O(n) for each test case, where n is the number of days.
Space Complexity: O(n) for storing the prices in a vector.

Input Format:
- First line: t (number of test cases)
- For each test case:
  - First line: n (number of days)
  - Second line: n space-separated integers representing prices

Output Format:
- For each test case: number of bad days
*/

#include <cstdio>
#include <vector>
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
    long cnt(0), mn(1e7); // cnt counts bad days, mn tracks minimum price seen so far
    for (long p = n - 1; p >= 0; p--) {
      cnt += (a[p] > mn); // increment if current price is greater than min seen in future
      mn = (mn < a[p]) ? mn : a[p]; // update minimum price seen so far
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/