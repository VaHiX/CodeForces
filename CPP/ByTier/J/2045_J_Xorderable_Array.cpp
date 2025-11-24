// Problem: CF 2045 J - Xorderable Array
// https://codeforces.com/contest/2045/problem/J

/*
 * Problem: J. Xorderable Array
 * 
 * Purpose: Given an array A of N integers and another array X of M integers,
 * determine how many pairs (u,v) where 1 <= u < v <= M satisfy the condition:
 * array A is (X[u], X[v])-xorderable. An array A is (p,q)-xorderable if the
 * elements can be rearranged such that for all i < j, A[i] XOR p <= A[j] XOR q
 * and A[i] XOR q <= A[j] XOR p.
 * 
 * Approach:
 * 1. Sort input array A.
 * 2. Compute the minimum XOR of adjacent elements in sorted A to help with queries.
 * 3. Use a trie to store values from X as we process them.
 * 4. For each value x in X, query the trie to find how many previously inserted
 *    elements satisfy the xorderable condition using a custom trie-based method.
 * 5. The key insight is that for an array to be (p,q)-xorderable, we need:
 *    - For all i < j: A[i] XOR p <= A[j] XOR q
 *    - For all i < j: A[i] XOR q <= A[j] XOR p
 *    These two conditions are equivalent to:
 *    - A[i] XOR (p XOR q) <= A[j] XOR (p XOR q)
 *    Meaning, sorting the array and checking order of A[i] XOR (p XOR q) values.
 *    
 *    This can be reformulated to checking how many elements have been inserted
 *    so far that satisfy the order constraint.
 *    
 * Time Complexity: O(N log N + M * 30) where N is size of A and M is size of X.
 * Space Complexity: O(M * 30) for the trie storage.
 */

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int maxn = 2e5 + 10;
int trie[31 * maxn][2]; // Trie to store values from array X
int val[31 * maxn];     // Count of values ending at each node
int cnt = 1;            // Counter for nodes in the trie
int minxor = INT_MAX;   // Minimum XOR of adjacent elements in sorted A

// Function to add a number to the trie
void add(int x) {
  int p = 1; // Start from root node
  for (int i = 29; i >= 0; i--) { // Process bits from MSB to LSB
    int irany = ((x >> i) & 1);  // Extract bit at position i
    if (!trie[p][irany]) {       // If child node doesn't exist, create it
      cnt++;
      trie[p][irany] = cnt;
    }
    p = trie[p][irany]; // Move to child node
    val[p]++;           // Increment count of elements going through this node
  }
}

// Function to query the number of previously added elements that satisfy constraint
long long get(int x) {
  int p = 1;
  long long res = 0;
  for (int i = 29; i >= 0; i--) {
    if (!p)
      return res;
    int irany = ((x >> i) & 1); // Current bit of query value
    int dir = (minxor >> i) & 1; // Bit of min_xor that determines direction
    if (!dir) {
      // If dir is 0, move in same direction as bit
      p = trie[p][irany];
    } else {
      // If dir is 1, move in opposite direction and accumulate values
      res += val[trie[p][irany]];
      p = trie[p][1 - irany];
    }
  }
  res += val[p]; // Add the final node
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto &i : a)
    cin >> i;
  sort(a.begin(), a.end()); // Sort array A to compute minxor quickly
  
  for (int i = 0; i < n - 1; i++) {
    minxor = min(minxor, a[i] ^ a[i + 1]); // Find minimum XOR of adjacent elements
  }
  
  long long ans = 0;
  for (int i = 0; i < m; i++) {
    int b;
    cin >> b;
    ans += get(b);    // Query how many previous values satisfy constraint
    add(b);           // Add current value to trie
  }
  cout << ans;
}


// https://github.com/VaHiX/CodeForces/