// Problem: CF 1676 B - Equal Candies
// https://codeforces.com/contest/1676/problem/B

/*
B. Equal Candies
Algorithm: For each test case, we want to make all boxes have the same number of candies,
           which is at least the minimum candy count in any box. The optimal strategy is
           to reduce every box to the minimum value among all boxes.
           This minimizes the total candies eaten.

Time Complexity: O(n) per test case, where n is the number of boxes.
Space Complexity: O(1), only using a constant amount of extra space.

Techniques:
- Greedy approach: Reduce all elements in array to minimum element
- Prefix sum technique for computing total candies to be removed
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0), mn(1e9); // s = total sum, mn = minimum candy count
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      mn = (mn < x) ? mn : x; // update minimum
      s += x; // accumulate total candies
    }
    long res = s - n * mn; // minimum candies to eat = total - (n * min)
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/