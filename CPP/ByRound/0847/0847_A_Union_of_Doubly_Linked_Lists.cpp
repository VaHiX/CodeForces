// Problem: CF 847 A - Union of Doubly Linked Lists
// https://codeforces.com/contest/847/problem/A

/*
Algorithm: Union of Doubly Linked Lists
Approach:
1. Parse input to build left and right arrays representing the doubly linked list structure.
2. Identify all list heads (nodes with left[i] == 0) and store them in a set.
3. Start with the first list head.
4. For each remaining list head:
   - Traverse to the end of the current list (following right pointers until 0).
   - Connect the end of the current list to the new list head (set left of new head to current end).
   - Connect the new list head to the current list (set right of current end to new head).
5. Output the final left and right arrays.

Time Complexity: O(n^2) in worst case due to repeated traversals and set operations.
Space Complexity: O(n) for storing the left/right arrays and the set of list heads.

*/
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> left(n + 1, 0), right(n + 1, 0);
  std::set<long> s;
  for (long p = 1; p <= n; p++) {
    scanf("%ld %ld", &left[p], &right[p]);
    if (left[p] == 0) {
      s.insert(p); // Insert list head into set
    }
  }
  long cur = *s.begin(); // Start with the first list
  s.erase(cur);
  long node = cur;
  while (s.size() > 0) {
    while (right[node] > 0) {
      node = right[node]; // Traverse to end of current list
    }
    cur = *s.begin(); // Get next list head
    s.erase(cur);
    left[cur] = node; // Link new list to current list
    right[node] = cur;
    node = cur; // Move to new list head
  }
  for (long p = 1; p <= n; p++) {
    printf("%ld %ld\n", left[p], right[p]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/