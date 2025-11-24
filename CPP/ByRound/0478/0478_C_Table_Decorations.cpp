// Problem: CF 478 C - Table Decorations
// https://codeforces.com/contest/478/problem/C

/*
Purpose: 
  This program determines the maximum number of tables that can be decorated 
  using given counts of red, green, and blue balloons. Each table requires exactly 
  three balloons, and no table can have all three balloons of the same color.

Algorithm:
  - Sort the balloon counts in ascending order.
  - Initially, assume we can make (r + g + b) / 3 tables (total balloons divided by 3).
  - However, if the sum of the two smaller counts is less than this initial estimate,
    we can't use all the balloons because of the constraint that no color can dominate.
  - In such cases, the actual maximum is limited by the sum of the two smaller counts.

Time Complexity: O(1) - Sorting 3 elements is constant time.
Space Complexity: O(1) - Only using a fixed-size vector and a few variables.

Techniques:
  - Greedy approach: sorting helps in identifying bottlenecks.
  - Mathematical optimization: leveraging the constraint to avoid overcounting.
*/

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  std::vector<long long> array(3);
  scanf("%lld %lld %lld\n", &array[0], &array[1], &array[2]);
  sort(array.begin(), array.end());  // Sort the counts in ascending order
  long long result = (array[0] + array[1] + array[2]) / 3;  // Initial estimate
  if (array[0] + array[1] < result) {  // Check if the two smaller counts are the bottleneck
    result = array[0] + array[1];  // Adjust result to the limit imposed by smaller counts
  }
  printf("%lld\n", result);
  return 0;
}


// https://github.com/VaHiX/CodeForces/