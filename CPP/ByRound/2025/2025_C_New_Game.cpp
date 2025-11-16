// Problem: CF 2025 C - New Game
// https://codeforces.com/contest/2025/problem/C

/*
Algorithm: Sliding Window + Sorting
Approach:
- Sort the array of card values.
- Use a sliding window technique to find the longest subsequence where the difference between the maximum and minimum values is less than k.
- The constraint is that the number of distinct numbers in the taken cards must not exceed k.
- We maintain a window [i, j) such that all elements in it are within a range of k.
- For each valid window, we update the result with the window size.

Time Complexity: O(n log n) due to sorting, where n is the number of cards
Space Complexity: O(1) if we ignore input storage, otherwise O(n) for the array
*/
#include <stdio.h>
#include <algorithm>

int n, k, r, i, j, p;
int main() {
  for (scanf("%*d"); ~scanf("%d%d", &n, &k); r = i = j = p = 0) {
    int a[n];  // Array to store card values
    while (i < n)
      scanf("%d", a + i++);  // Read input card values
    
    for (std::sort(a, a + n); j < n; r = ++j - i > r ? j - i : r) {
      // Adjust i if current card value exceeds the allowed range
      i = a[j] > p ? j : i;
      
      // Shrink window from left while the difference is >= k
      while (a[j] - a[i] >= k)
        i++;
      
      // Update p to the next possible start value (a[j] + 1)
      p = a[j] + 1;
    }
    printf("%d ", r);  // Print the maximum number of cards that can be taken
  }
}


// https://github.com/VaHiX/CodeForces/