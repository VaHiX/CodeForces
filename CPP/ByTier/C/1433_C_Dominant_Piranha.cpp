// Problem: CF 1433 C - Dominant Piranha
// https://codeforces.com/contest/1433/problem/C

/*
Algorithm: Find a dominant piranha
Approach:
1. Find maximum and minimum sizes in the array.
2. If all sizes are equal (mn == mx), then no dominant piranha can exist.
3. Otherwise:
   - Check if the first element is maximum and the second is smaller.
   - Check if the last element is maximum and the second-to-last is smaller.
   - For middle elements, check if it's maximum and adjacent elements are smaller.
Time Complexity: O(n) - single pass through the array
Space Complexity: O(n) - for storing the array of piranha sizes
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mx(0), mn(2e9 + 7); // Initialize max and min values
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      mn = (mn < a[p]) ? mn : a[p]; // Update minimum
      mx = (mx > a[p]) ? mx : a[p]; // Update maximum
    }
    long where(-1); // Position of dominant piranha, -1 if none
    if (mn == mx) {
      puts("-1"); // All piranhas have same size, no dominant possible
      continue;
    }
    // Check if first piranha can be dominant (if it's max and next is smaller)
    if (a[0] == mx && a[1] < mx) {
      where = 1;
    } 
    // Check if last piranha can be dominant (if it's max and previous is smaller)
    else if (a[n - 1] == mx && a[n - 2] < mx) {
      where = n;
    } 
    // Check middle piranhas
    else {
      for (long p = 1; p + 1 < n; p++) {
        if ((a[p] == mx) && (a[p - 1] < mx || a[p + 1] < mx)) {
          where = p + 1; // 1-indexed position
          break;
        }
      }
    }
    printf("%ld\n", where);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/