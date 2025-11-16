// Problem: CF 920 C - Swap Adjacent Elements
// https://codeforces.com/contest/920/problem/C

/*
 * Problem: C. Swap Adjacent Elements
 * 
 * Algorithm/Technique: Union-Find / Segment-based Analysis
 * 
 * Approach:
 * - The key idea is to identify contiguous segments where swapping is allowed.
 * - For each such segment, we check whether the elements within that segment 
 *   can be rearranged to match the sorted order (i.e., the values in the segment 
 *   should be exactly the integers from start to end of that segment).
 * 
 * Time Complexity: O(n log n) - due to set operations (insert and count)
 * Space Complexity: O(n) - for storing array, string, and set
 * 
 * The algorithm processes the string of allowed swaps to find contiguous blocks
 * where elements can be reordered freely. For each such block, it ensures that 
 * the values in that block cover all integers in the correct range, thus allowing
 * the sorting to be possible.
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<long> a(n + 1); // 1-indexed array to store elements
  for (long p = 1; p <= n; p++) {
    std::cin >> a[p];
  }
  std::vector<long> f(n + 1, 0); // Not used in current implementation
  for (long p = 1; p <= n; p++) {
    f[p] = p;
  }
  std::string s;
  std::cin >> s;
  s += '0'; // Append '0' to simplify loop logic
  s = '0' + s; // Prepend '0' to make indexing consistent with a[]
  bool possible = true; // Result flag
  bool state(0); // Current state: 0 = no active segment, 1 = active segment
  long start(0); // Start of current segment
  std::set<long> st; // Set to store elements in current segment
  for (long p = 1; p <= n; p++) {
    if (!state && s[p] == '0') {
      // If we are not in a segment and encounter a '0', check if a[p] matches expected position
      if (a[p] != p) {
        possible = false;
        break;
      }
    } else if (s[p] == '1') {
      // If we are allowed to swap, start a new segment or continue existing
      if (!state) {
        state = 1;
        start = p;
      }
      st.insert(a[p]); // Add element to current segment
    } else if (state && s[p] == '0') {
      // End of a segment: check if all required numbers are present
      st.insert(a[p]); // Insert the current element into segment
      for (long k = start; k <= p; k++) {
        if (st.count(k) == 0) { // If any number in range is missing
          possible = false;
          break;
        }
      }
      if (!possible) {
        break;
      }
      state = 0; // Reset state
      st.clear(); // Clear set
      start = 0; // Reset start
    }
  }
  std::cout << (possible ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/