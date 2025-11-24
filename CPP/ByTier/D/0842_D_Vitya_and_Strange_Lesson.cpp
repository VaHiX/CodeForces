// Problem: CF 842 D - Vitya and Strange Lesson
// https://codeforces.com/contest/842/problem/D

/*
Purpose: This code solves the problem of efficiently processing multiple queries on an array,
where each query modifies the array by XORing all elements with a given value and then computes
the mex (minimum excludant) of the resulting array.

Algorithm:
- Uses a segment tree (or more precisely, a binary trie) to maintain which numbers are present
  in the current array, allowing fast insertion and lookup.
- For each query:
  1. XOR the global variable 'x' with the query value (to track cumulative XOR).
  2. Traverse the trie to find the smallest non-negative integer that is not present.
  3. Output the result of the mex computation.

Time Complexity: O(n + m * log(max_value)) where n is the size of the input array,
and m is the number of queries. The log factor comes from traversing the trie.
Space Complexity: O(2^k) where k is the number of bits required to represent the maximum value,
i.e., ~O(2^20) = ~1e6 in this case, due to the trie structure.

*/
#include <iostream>
using namespace std;
typedef unsigned int unt;
constexpr unt off = 1u << 19u;  // Offset to shift values into trie space
unt s[off << 1u];              // Segment tree-like array to represent presence of numbers
int main() {
  cin.tie(0)->sync_with_stdio(0);  // Fast I/O
  unt n, m;
  cin >> n >> m;
  while (n--) {
    unt a;
    cin >> a;
    a |= off;  // Shift value to avoid index 0
    if (s[a])
      continue;  // Skip if already present
    while (a) {
      s[a]++;  // Mark node as visited in trie
      a >>= 1u;  // Move to parent in trie
    }
  }
  unt x = 0u;  // Stores cumulative XOR from queries
  while (m--) {
    unt xx;
    cin >> xx;
    x ^= xx;  // Update global XOR
    unt i = 1u;  // Start traversal from root of trie
    for (unt b = off; b >>= 1u;) {  // Traverse bit by bit from MSB
      i <<= 1u;  // Move to child node
      if (x & b)  // If the bit matches the current xor value
        i |= 1u;  // Choose the right child
      if (s[i] == b)  // If this path has been completely filled
        i ^= 1u;  // Switch to other child
    }
    cout << (i & ~off ^ x) << '\n';  // Output the mex (result of the query)
  }
}


// https://github.com/VaHiX/CodeForces/