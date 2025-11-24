// Problem: CF 1208 B - Uniqueness
// https://codeforces.com/contest/1208/problem/B

/*
B. Uniqueness
Algorithm: Two Pointers + Hash Set
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to find the minimum length of a subsegment that needs to be removed 
so that all remaining elements in the array are pairwise distinct.

Approach:
1. First, we try to find the largest prefix with all distinct elements by using a set.
2. Then, we use two pointers to find the minimum subsegment to remove.
3. We maintain a sliding window where we ensure no duplicates are present.
4. The algorithm uses a set to track which elements are currently in the window.

Key steps:
- Use set to keep track of unique elements
- Use two pointers (i and j) to define the current valid window
- When we detect a duplicate, we shrink the window from the left
- Track the minimum subsegment that needs to be removed
*/

#include <stdio.h>
#include <set>
#include <utility>

int i, j, f = 1, n, a[2001];
std::set<int> s{0}; // Initialize set with 0 to avoid issues with indexing
int main() {
  scanf("%d", &n);
  while (i++ < n)
    scanf("%d", a + i), j += f = f && s.insert(a[i]).second; // Build initial prefix of unique elements
  while (j + 1) { // While there are elements in the window
    while (s.insert(a[n]).second) // Try to insert element from right, if it already exists, break
      n--;
    i = n - j < i ? n - j : i; // Update minimum subsegment length
    s.erase(a[j--]); // Shrink window from left
  }
  printf("%d", i); // Print the minimum subsegment length to remove
}


// https://github.com/VaHiX/codeForces/