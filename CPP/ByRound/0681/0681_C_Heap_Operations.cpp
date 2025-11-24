// Problem: CF 681 C - Heap Operations
// https://codeforces.com/contest/681/problem/C

/*
 * Purpose: Correct a sequence of heap operations to ensure consistency.
 *          The heap supports insert, getMin, and removeMin operations.
 *          Given a sequence of operations that may be inconsistent,
 *          we add the minimum number of operations to make it valid.
 *
 * Algorithm:
 *   - Use a multiset to simulate the heap (maintains elements in sorted order).
 *   - Process each operation in order:
 *     - For "insert x": insert x into the multiset and record the operation.
 *     - For "removeMin": if heap is empty, insert 0 first; then remove the minimum.
 *     - For "getMin x": while the minimum is less than x, remove elements and record removals;
 *                      if x is smaller than the current minimum, insert x and record insertion.
 *   - This ensures the heap state matches what is expected by the recorded operations.
 *
 * Time Complexity: O(n log n) where n is the number of operations.
 *                  Each element can be inserted/removed from the multiset in O(log n) time,
 *                  and we process each operation once.
 *
 * Space Complexity: O(n) to store the operations and the multiset.
 */

#include <stddef.h>
#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> op;
  std::multiset<long> ms;
  for (long p = 0; p < n; p++) {
    std::string s;
    std::cin >> s;
    if (s == "insert") {
      long x;
      std::cin >> x;
      ms.insert(x);
      op.push_back("insert " + std::to_string(x));
    } else if (s == "removeMin") {
      if (ms.empty()) {
        ms.insert(0);
        op.push_back("insert 0");
      }
      ms.erase(ms.begin());
      op.push_back(s);
    } else if (s == "getMin") {
      long x;
      std::cin >> x;
      // Remove elements from heap until we have a minimum >= x
      while (!ms.empty() && ((*ms.begin()) < x)) {
        ms.erase(ms.begin());
        op.push_back("removeMin");
      }
      // If no elements left or x is smaller than minimum, insert x
      if (ms.empty() || x < (*ms.begin())) {
        ms.insert(x);
        op.push_back("insert " + std::to_string(x));
      }
      op.push_back("getMin " + std::to_string(x));
    }
  }
  std::cout << op.size() << std::endl;
  for (size_t p = 0; p < op.size(); p++) {
    std::cout << op[p] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/