// Problem: CF 2093 G - Shorten the Array
// https://codeforces.com/contest/2093/problem/G

/*
G. Shorten the Array

Algorithm/Techniques: Trie data structure, Two Pointers, Bit Manipulation

Time Complexity: O(30 * n) per test case where n is the length of the array.
Space Complexity: O(30 * n) for the trie storage in worst-case scenario.

The problem asks us to find the shortest subarray whose XOR beauty (maximum XOR of any pair) is at least k.
We use a trie to efficiently store and query prefixes. For each element, we insert it into the trie and then 
query for the maximum value such that XOR with current value is >= k. This allows us to track the minimum
length subarray ending at current position that satisfies condition.

*/

#include <algorithm>
#include <cstdio>
using namespace std;
int a[200005];
int nxt[6000005][2], id; // nxt[node][bit] stores child node for bit 0 or 1, id tracks current node count
int val[6000005]; // val[node] stores the index of the number ending at this node (used to compute subarray length)

void ins(int x, int p) { // Insert number x with position p into the trie
  int now = 0;
  for (int i = 29; i >= 0; i--) { // Process from most significant bit to least
    int t = ((x >> i) & 1); // Extract bit at position i
    if (!nxt[now][t]) // If no child exists for this bit, create one
      nxt[now][t] = ++id;
    now = nxt[now][t]; // Move to the next node
    val[now] = p; // Store the position where this prefix ends
  }
}

int query(int x, int k) { // Query maximum index such that (x ^ previous_value) >= k
  int now = 0, ret = 0;
  for (int i = 29; i >= 0; i--) {
    int t = ((x >> i) & 1); // Extract bit at position i
    if (!(k & (1 << i))) { // If the bit in k is 0, we can go any direction to maximize result
      ret = max(ret, val[nxt[now][t ^ 1]]); // Go opposite bit if possible to avoid reducing XOR
      now = nxt[now][t]; // Continue with same bit
    } else { // If the bit in k is 1, we must go opposite to achieve >= k
      now = nxt[now][t ^ 1]; // Go opposite bit
    }
    if (!now) // If no such path exists, return current max
      return ret;
  }
  return max(ret, val[now]); // Return final answer after processing all bits
}

int main() {
  int t, n, k, l, ans;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    ans = 0x3f3f3f3f; // Initialize with a large value
    for (int i = 1; i <= n; i++) {
      ins(a[i], i); // Insert current number into trie
      l = query(a[i], k); // Query to find best left boundary
      if (l)
        ans = min(ans, i - l + 1); // Update minimum length
    }
    if (ans == 0x3f3f3f3f) // If not found, output -1
      ans = -1;
    printf("%d\n", ans);
    for (int i = 0; i <= id; i++) { // Clear the trie for next test case
      nxt[i][0] = 0;
      nxt[i][1] = 0;
      val[i] = 0;
    }
    id = 0;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/