// Problem: CF 2102 D - Quartet Swapping
// https://codeforces.com/contest/2102/problem/D

/*
D. Quartet Swapping
Algorithm: 
    This problem involves rearranging a permutation using a specific swap operation.
    The allowed operation is to simultaneously swap elements at positions i and i+2,
    and elements at positions i+1 and i+3. This effectively partitions the array into two subsequences:
    one with odd indices (1, 3, 5, ...) and one with even indices (2, 4, 6, ...).
    Using this operation, we can sort each subsequence independently.
    
    Key idea:
        - Group elements by their positions: odd-indexed (1,3,5...) and even-indexed (2,4,6...).
        - Sort each group independently.
        - The overall strategy is to simulate the process of placing minimal values in ascending order
          by swapping elements within groups.

Time Complexity: O(n log n) due to sorting the two subsequences.
Space Complexity: O(n) for storing input and auxiliary arrays.
*/

#include <iostream>
#include <utility>

#define N 200005
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t, n, i, a[N], p[N], x, y, j, k;
  cin >> t;
  
  while (t--) {
    cin >> n;
    
    // Read input permutation
    for (i = 1; i <= n; i++)
      cin >> a[i];
    
    // Store the positions of each value in the permutation
    for (i = 1; i <= n; i++)
      p[a[i]] = i;
    
    // x and y track parity of inversions for odd/even indexed groups
    x = y = 0;
    
    // j tracks next odd position to fill, k tracks next even position to fill
    j = 1;
    k = 2;
    
    // Process elements in order from 1 to n
    for (i = 1; i <= n; i++) {
      if (p[i] % 2) { // If current element's position is odd
        // Check if it needs to be moved to correct odd-positioned slot
        if (p[i] != j)
          x ^= 1; // Toggle inversion count for odd group
        
        // Update the position of the element currently at j
        p[a[j]] = p[i];
        
        // Swap elements at positions j and p[i]
        swap(a[p[i]], a[j]);
        
        // Update position of element i to j (its new slot)
        p[i] = j;
        j += 2; // Move to next odd position
      } else { // If current element's position is even
        // Check if it needs to be moved to correct even-positioned slot
        if (p[i] != k)
          y ^= 1; // Toggle inversion count for even group
        
        // Update the position of the element currently at k
        p[a[k]] = p[i];
        
        // Swap elements at positions k and p[i]
        swap(a[p[i]], a[k]);
        
        // Update position of element i to k (its new slot)
        p[i] = k;
        k += 2; // Move to next even position
      }
    }

    // If parity of inversions is different for odd/even groups,
    // perform one final swap between last two elements.
    if (x ^ y)
      swap(a[n], a[n - 2]);

    // Output the resulting permutation
    for (i = 1; i <= n; i++)
      cout << a[i] << ' ';
    cout << '\n';
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/