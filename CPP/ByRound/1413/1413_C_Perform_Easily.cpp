// Problem: CF 1413 C - Perform Easily
// https://codeforces.com/contest/1413/problem/C

/*
C. Perform Easily
Algorithms/Techniques: Binary search, two pointers, sorting, uniqueness filtering

Time Complexity: O(n * log(n) + m * log(m) + n * m)
Space Complexity: O(n + m)

Problem: Given 6 strings with base notes a[i], and a sequence of n notes b[i],
find the minimum difference between max and min fret positions when assigning
each note to a string-fret combination such that note b[i] = a[j] + fret.

Approach:
1. Sort and deduplicate the note array (b) and note base array (a).
2. For each unique base note in 'a' and each unique note in 'b', calculate an initial
   potential difference between max and min frets.
3. Use two-pointer technique to find minimal difference efficiently.
4. A key optimization: skip unnecessary calculations where the current difference
   cannot lead to a better solution.

The code uses sorting, binary search, and smart pruning techniques to solve 
this problem in acceptable time with the constraints.
*/

#include <algorithm>
#include <iostream>
using namespace std;

int a[10], na, n, b[100500], ans, minn;

int main() {
  ios::sync_with_stdio(false);
  na = 6;
  for (int i = 0; i < 6; i++)
    cin >> a[i];
  sort(a, a + na);
  // Remove duplicates from array a
  na = unique(a, a + na) - a;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> b[i];
  sort(b, b + n);
  ans = -1;
  // Remove duplicates from array b
  n = unique(b, b + n) - b;
  
  for (int k = 0; k < na; k++) // Try each base note
    for (int i = 0; i < n; i++) { // Try each unique note
      // Early skip optimization: if max fret possible with current
      // (b[n-1] - a[na-1]) is less than b[i] - a[k], then no point in continuing
      if (i != n - 1 && b[n - 1] - a[na - 1] > b[i] - a[k])
        continue;
      
      // The current base fret difference for this combination
      minn = b[i] - a[k];
      
      // Two pointer approach to calculate minimal required fret difference
      for (int r = 0, cur = 0; r < na; r++) {
        // Skip combinations where we would need a fret smaller than minimum available
        if (b[i] - a[k] < b[0] - a[r])
          continue;
          
        minn = min(minn, b[cur] - a[r]); // Update minimum fret difference
        
        // Find the next index where we can use note corresponding to a[r]
        cur = upper_bound(b + cur, b + n, b[i] - a[k] + a[r]) - b;
        
        if (cur == n) // If no more elements left, break
          break;
      }
      
      // Update global answer with minimum difference found so far
      if (ans == -1)
        ans = b[i] - a[k] - minn;
      else
        ans = min(ans, b[i] - a[k] - minn);
    }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/