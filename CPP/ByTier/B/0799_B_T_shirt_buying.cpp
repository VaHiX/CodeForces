// Problem: CF 799 B - T-shirt buying
// https://codeforces.com/contest/799/problem/B

/*
Purpose: This program solves the problem of assigning t-shirts to buyers based on their favorite color and the lowest price available.
         Each buyer wants a t-shirt where at least one side matches their favorite color.
         Buyers are served in order, and each t-shirt can only be bought once.
         A greedy approach is used: for each buyer, we scan through sorted t-shirts and find the first one that matches their favorite color and is still available.

Algorithms:
- Sorting t-shirts by price (ascending) to easily access cheapest valid t-shirt
- For each buyer, we scan through sorted t-shirts using index array to track progress per color
- Time complexity: O(n log n + m * n) where n is number of t-shirts and m is number of buyers
- Space complexity: O(n) for storing t-shirts and auxiliary arrays

*/

#include <algorithm>
#include <cstdio>
#include <vector>
struct tshirt {
  long price, colf, colb;
  bool taken;
};
bool tshirtCompare(tshirt a, tshirt b) { return a.price < b.price; }
int main() {
  const int C = 3;
  long n;
  scanf("%ld", &n);
  std::vector<tshirt> a(n);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a[p].price = x;
    a[p].taken = false;
  }
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a[p].colf = x;
  }
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a[p].colb = x;
  }
  sort(a.begin(), a.end(), tshirtCompare);
  long m;
  scanf("%ld", &m);
  std::vector<long> ind(C, 0); // keeps track of the next index in the sorted list for each color
  for (long p = 0; p < m; p++) {
    int r;
    scanf("%d", &r);
    // Skip t-shirts until we find one that's not taken and has the favorite color on front or back
    while (ind[r] < n && (a[ind[r]].taken ||
                          ((a[ind[r]].colf != r) && (a[ind[r]].colb != r)))) {
      ++ind[r];
    }
    printf("%ld ", (ind[r] < n) ? a[ind[r]].price : (-1));
    if (ind[r] < n) {
      a[ind[r]].taken = true; // Mark the t-shirt as taken
      ++ind[r]; // Advance index for this color for the next buyer
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/