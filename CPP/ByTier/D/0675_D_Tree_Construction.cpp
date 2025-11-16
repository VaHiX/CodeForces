// Problem: CF 675 D - Tree Construction
// https://codeforces.com/contest/675/problem/D

/*
Code Purpose:
This code constructs a binary search tree (BST) from a given sequence of distinct integers and outputs the parent of each node (except the root) as the tree is built.

Algorithm:
- Use a set to maintain the nodes in sorted order for efficient lookup.
- Use a map to store the left and right child of each node.
- For each new element:
  1. Find the smallest element in the set that is greater than the current element.
  2. If such an element exists and its left child is already assigned, assign the current element as its right child.
  3. Otherwise, assign the current element as the left child.
  4. Insert the current element into the set and initialize its children in the map.
- Output the parent of each newly inserted node.

Time Complexity: O(n log n) due to insertion and lookup operations in the set and map.
Space Complexity: O(n) for storing the set and the map.
*/

#include <cstdio>
#include <map>
#include <set>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::set<long> s;
  std::map<long, std::pair<long, long>> m;
  long a;
  scanf("%ld", &a);
  s.insert(a);
  m[a] = std::make_pair(-1, -1); // Initialize root's children as -1 (null)
  for (long p = 1; p < n; p++) {
    scanf("%ld", &a);
    std::set<long>::iterator it = s.upper_bound(a); // Find the smallest element > a
    if (it == s.end() || m[*it].first >= 0) {
      // If no element > a exists, or the found element already has a left child,
      // assign a as the right child of the largest element <= a
      --it;
      m[*it].second = a;
    } else {
      // Otherwise, assign a as the left child of the smallest element > a
      m[*it].first = a;
    }
    s.insert(a); // Add a to the set
    m[a] = std::make_pair(-1, -1); // Initialize a's children
    printf("%ld ", *it); // Output the parent of a
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/