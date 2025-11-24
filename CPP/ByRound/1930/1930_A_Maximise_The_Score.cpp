// Problem: CF 1930 A - Maximise The Score
// https://codeforces.com/contest/1930/problem/A

/*
Problem: A. Maximise The Score
Algorithms/Techniques: Greedy algorithm with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector of size 2n

The strategy is to sort the array and then pick every second element starting from index 0.
This ensures that we always pair the smallest available numbers together, maximizing the sum of minimums.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(2 * n); // Create vector to hold 2*n elements
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &a[p]); // Read all elements into the vector
    }
    sort(a.begin(), a.end()); // Sort the array in ascending order
    long sum(0);
    for (long p = 0; p < 2 * n; p += 2) {
      sum += a[p]; // Add the smaller element of each pair to the total score
    }
    printf("%ld\n", sum);
  }
}


// https://github.com/VaHiX/codeForces/