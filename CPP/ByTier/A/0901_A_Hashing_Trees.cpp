// Problem: CF 901 A - Hashing Trees
// https://codeforces.com/contest/901/problem/A

/*
 * Purpose: This program determines whether there is only one rooted tree
 *          that matches a given sequence of vertex counts at each level,
 *          or if there are multiple non-isomorphic trees that match the same
 *          sequence. It constructs two possible tree structures when ambiguity
 *          is found.
 *
 * Algorithm:
 * - For a given sequence a[0] to a[h], the algorithm builds two different
 *   tree structures by varying how children are assigned to parents.
 * - If at any level beyond the root, there's more than one node at that level
 *   and more than one child is available, it creates two different assignments.
 * - This is done by using two different parent assignment strategies:
 *   - First tree: each node points to the first node of the previous level.
 *   - Second tree: each node points to the first node of the previous level,
 *     but for every (r - l)th child, it points to an earlier node to allow
 *     different structure.
 *
 * Time Complexity: O(h + sum(a_i)) where h is the height and sum(a_i) is
 *                  the total number of nodes in the tree.
 *
 * Space Complexity: O(sum(a_i)) for storing parent information for each node.
 */

#include <cstdio>
#include <vector>
int main() {
  const int N = 200007;
  std::vector<std::vector<long>> fa(N, std::vector<long>(2, 0)); // fa[p][0] and fa[p][1] store two possible parents
  long l(1), r(2); // l = start of current level, r = end of current level
  bool ambiguous(false);
  long h;
  scanf("%ld", &h);
  for (long p = 0; p <= h; p++) {
    long a;
    scanf("%ld", &a);
    if (p == 0) {
      continue; // Root has no parent
    }
    // If there's more than one node at current level and more than one node
    // in the previous level, and there are multiple children, then ambiguity arises
    if (r - l > 1 && a > 1) {
      ambiguous = true;
    }
    // Assign parents for each node in the current level
    for (long q = 0; q < a; q++) {
      // First tree: each node points to the first node of the previous level
      fa[r + q][0] = l;
      // Second tree: node alternates between first parent and earlier nodes to produce different structure
      fa[r + q][1] = l + q % (r - l);
    }
    l = r; // Move to next level
    r += a;
  }
  if (ambiguous) {
    puts("ambiguous");
    // Print first tree structure (parent assignments)
    for (long p = 1; p < r; p++) {
      printf("%ld ", fa[p][0]);
    };
    puts("");
    // Print second tree structure (different parent assignments)
    for (long p = 1; p < r; p++) {
      printf("%ld ", fa[p][1]);
    };
    puts("");
  } else {
    puts("perfect");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/