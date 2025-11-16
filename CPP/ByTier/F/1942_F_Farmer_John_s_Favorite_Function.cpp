// Problem: CF 1942 F - Farmer John's Favorite Function
// https://codeforces.com/contest/1942/problem/F

/*
 * Problem: Farmer John's Favorite Function
 * Algorithm: Block-based Segment Tree with Square Root Updates
 * Time Complexity: O((n + q) * sqrt(n) * log(n)) 
 * Space Complexity: O(n)
 * 
 * The solution uses a block-based approach to efficiently maintain
 * the function f(i) = sqrt(f(i-1) + a[i]) by updating blocks of the array.
 * For each block, we precompute the value and 'need' for maintaining
 * the recurrence relation. The segment tree helps in quickly updating
 * the block information when an array element is changed.
 */

#include <stddef.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#ifdef LOCAL
#include "Debug.h"
#else
#define debug(...) 42
#endif
using namespace std;

const int B = 6; // Block size
const int oo = 1.5e9; // A large value to represent infinity

struct SegmentTree {
  int low, mid, high; // Range of the segment tree node
  pair<int, int> value; // value: current computed function value, need: required value to achieve
  SegmentTree *l, *r; // Left and right children
  
  // Constructor for segment tree node
  SegmentTree(int low, int high) : low(low), high(high) {
    mid = (low + high) / 2;
    value = {0, 0};
    if (low == high)
      l = r = NULL;
    else {
      l = new SegmentTree(low, mid);
      r = new SegmentTree(mid + 1, high);
    }
  }
  
  // Update the function value for a specific index in the segment tree
  void update(int x, pair<int, int> v) {
    if (low == high) {
      value = v;
      return;
    }
    if (x <= mid)
      l->update(x, v);
    else
      r->update(x, v);
    
    // Merge values from left and right subtrees to compute the current node's value
    auto [lVal, lNeed] = l->value;
    auto [rVal, rNeed] = r->value;
    if (lVal >= rNeed)
      value = {rVal + 1, oo};
    else if (lVal + 1 == rNeed)
      value = {rVal, lNeed};
    else
      value = {rVal, oo};
  }
};

// Helper function to compute square of an integer
long long sqr(int x) { return 1LL * x * x; }

// Custom integer square root function
int intSqrt(long long x) {
  int y = int(sqrt(x));
  while (sqr(y + 1) <= x)
    y++;
  while (sqr(y) > x)
    y--;
  return y;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  int offset = (B - n % B) % B; // Calculate offset to make array size multiple of block size
  int blockCnt = (n + offset) / B; // Calculate number of blocks
  vector<long long> a(n + offset); // Extended array to make size multiple of B
  for (int i = 0; i < n; i++)
    cin >> a[i + offset];
  
  SegmentTree tree(0, blockCnt - 1); // Initialize the segment tree
  
  // Function to update a block's value in the segment tree
  auto updateBlock = [&](int blockId) {
    int l = blockId * B, r = l + B - 1;
    int value = 0;
    for (int i = l; i <= r; i++)
      value = intSqrt(value + a[i]);
    long long need = value + 1;
    for (int i = r; i >= l; i--) {
      need = sqr(need) - a[i];
      if (need > oo) {
        need = oo;
        break;
      }
    }
    tree.update(blockId, {value, int(need)});
  };
  
  // Initialize the segment tree with all blocks
  for (int i = 0; i < blockCnt; i++)
    updateBlock(i);
  
  // Process each query
  while (q--) {
    int i;
    long long x;
    cin >> i >> x;
    i = i - 1 + offset; // Adjust for offset
    a[i] = x;
    updateBlock(i / B); // Update the block
    cout << tree.value.first << '\n'; // Output the result
  }
}


// https://github.com/VaHiX/CodeForces/