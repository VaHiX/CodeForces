// Problem: CF 1467 B - Hills And Valleys
// https://codeforces.com/contest/1467/problem/B

/*
Algorithm/Technique: 
- Brute-force with optimization: For each element in the array (except first and last), we compute the change in intimidation value if we replace that element with either its left or right neighbor.
- The idea is to find that one element whose replacement reduces the total number of hills and valleys the most.
- Time Complexity: O(n) per test case, Space Complexity: O(1) extra space (not counting input array)

Approach:
1. First, count the initial number of hills and valleys.
2. For each middle element, calculate how changing it affects the overall intimidation value.
3. Try changing it to its left neighbor or right neighbor and see which gives better reduction.
4. Subtract the maximum reduction from total count to get the minimum possible intimidation value.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int t, n, a[300005], k, s;

// Function to determine if index i is a hill or valley
int f(int i) {
  if (a[i] > a[i - 1] && a[i] > a[i + 1])
    return 1; // it's a hill
  if (a[i] < a[i - 1] && a[i] < a[i + 1])
    return 1; // it's a valley
  return 0;
}

int main() {
  for (scanf("%d", &t); t; t--) {
    scanf("%d", &n);
    s = k = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    
    // Add sentinel values to simplify boundary checks
    a[0] = a[1];
    a[n + 1] = a[n];
    
    // Precompute the current number of hills and valleys
    for (int i = 2; i < n; i++) {
      s += f(i);
    }
    
    // Try changing each element (except first and last) to its left or right neighbor
    for (int i = 2; i < n; i++) {
      int p = 0, q = 0, w = a[i]; // p = change to left, q = change to right, w = current value

      // Calculate number of hills/valleys before any change
      p = q = f(i - 1) + f(i + 1) + f(i);

      // Simulate changing a[i] to a[i-1]
      a[i] = a[i - 1];
      p -= f(i + 1); // remove effect on next element

      // Simulate changing a[i] to a[i+1]
      a[i] = a[i + 1];
      q -= f(i - 1); // remove effect on previous element

      // Reset a[i] back to its original value
      a[i] = w;

      // Track the maximum gain (best improvement)
      k = max(p, max(q, k));
    }
    
    // The minimal intimidation value is total minus max gain
    printf("%d\n", s - k);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/