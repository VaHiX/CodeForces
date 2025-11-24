// Problem: CF 709 A - Juicer
// https://codeforces.com/contest/709/problem/A

/*
 * Problem: Kolya Juicer
 * Algorithm: Simulation
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Approach:
 * - Iterate through each orange in the given order.
 * - If the orange's size exceeds 'b', skip it.
 * - Otherwise, add its size to the current sum of waste.
 * - If the sum exceeds 'd', increment the count of emptying the waste section,
 *   and reset the sum to zero.
 * - Output the total count of times the waste section was emptied.
 */

#include <iostream>

using namespace std;
int main() {
  long long int i, j, k;
  long long int sum = 0, count = 0;
  long long int n, b, d;
  cin >> n >> b >> d;
  long long int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  for (i = 0; i < n; i++) {
    if (a[i] > b)
      continue;  // Skip oranges that are too large for the juicer
    sum += a[i];   // Add the orange's size to the current waste sum
    if (sum > d) { // If the waste sum exceeds the limit
      sum = 0;     // Reset the waste sum
      count++;     // Increment the count of emptying the waste section
    }
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/