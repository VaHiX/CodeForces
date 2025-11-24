// Problem: CF 984 A - Game
// https://codeforces.com/contest/984/problem/A

/*
Purpose: This program determines the last number remaining on the board after two players alternately remove numbers, with the first player trying to minimize and the second trying to maximize the final number. The optimal strategy leads to selecting the median of the sorted array.

Algorithms/Techniques: Sorting, Median selection

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

The game dynamics result in the optimal play leading to the median of the sorted array being the final answer.
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort the array to find the median
  printf("%ld\n", a[(n - 1) / 2]);  // Output the median element
  return 0;
}


// https://github.com/VaHiX/CodeForces/