// Problem: CF 455 A - Boredom
// https://codeforces.com/contest/455/problem/A

/*
 * Code purpose: Solves the "Boredom" problem where we need to maximize points
 *               by deleting elements from a sequence, with the constraint that
 *               deleting an element also deletes all elements equal to its 
 *               adjacent values (element - 1 and element + 1).
 * 
 * Algorithm: Dynamic Programming
 *            1. Count total points for each value (value * count)
 *            2. Use DP where points[i] = max(points[i-2] + counts[i], points[i-1])
 *               This represents choosing to take current value or skip it.
 * 
 * Time Complexity: O(n + max_value), where n is the length of input and max_value
 *                  is the maximum element in the input.
 * Space Complexity: O(max_value), for storing counts and DP array.
 */
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> data(n);
  long maxElement(0);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &data[p]);
    maxElement = (maxElement > data[p]) ? maxElement : data[p]; // Find max element to size arrays
  }
  std::vector<long long> counts(maxElement + 1); // Count of points for each value
  for (int p = 0; p < n; p++) {
    counts[data[p]] += data[p]; // Accumulate points for each value
  }
  long long output(0);
  std::vector<long long> points(maxElement + 1); // DP array for maximum points
  points[0] = 0;
  points[1] = counts[1]; // Base case: only one element possible
  for (int p = 2; p <= maxElement; p++) {
    long long first = points[p - 2] + counts[p];   // Take current value + max from 2 steps back
    long long second = points[p - 1];              // Skip current value
    points[p] = (first > second) ? first : second; // Choose better option
  }
  printf("%lld\n", points[maxElement]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/