// Problem: CF 472 B - Design Tutorial: Learn from Life
// https://codeforces.com/contest/472/problem/B

/*
 * Code Purpose:
 * This program calculates the minimum time required to transport all people
 * to their respective floors using an elevator with limited capacity.
 * 
 * Algorithm:
 * - Sort the target floors in ascending order.
 * - Process people in batches of size k (elevator capacity).
 * - For each batch, calculate the time taken to go to the highest floor
 *   in that batch and return to the first floor (2 * (max_floor - 1)).
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of people.
 * Space Complexity: O(1) as we use only a constant amount of extra space.
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n, k, a[2000], sum = 0;
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);  // Sort floors in ascending order
  for (int i = n - 1; i >= 0; i -= k)  // Process people in batches of size k
    sum += 2 * (a[i] - 1);  // Add round trip time to the highest floor in the batch
  cout << sum;
}


// https://github.com/VaHiX/CodeForces/