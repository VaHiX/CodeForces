// Problem: CF 1984 G - Magic Trick II
// https://codeforces.com/contest/1984/problem/G

/*
 * Problem: G. Magic Trick II
 * Purpose: Given a permutation of [1, 2, ..., n], find the maximum k such that we can sort the permutation using operations of moving a subarray of length k and inserting it at any position. 
 * Algorithm: 
 *  - The solution uses a greedy approach to analyze the structure of the permutation.
 *  - If the permutation has exactly one "drop" (i.e., exactly one index where arr[i] > arr[i+1]), then optimal k is n-1.
 *  - Otherwise, k is determined based on the parity of inversions.
 *  - The solution then generates the sequence of operations for sorting.
 * 
 * Time Complexity: O(n^2) per test case (due to nested loops and operations)
 * Space Complexity: O(n) for storing the array and operations.
 */

#include <stdio.h>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define oo 1000000010
#define mod 998244353
vector<pair<int, int>> ans;
int n, k;
vector<int> arr;

// Function to perform a move operation:
// Remove subarray starting at index i with length k, and insert it at index j
void make(vector<int> &arr, int k, int i, int j) {
  vector<int> b;
  for (int l = 0; l < i; l++)
    b.push_back(arr[l]);
  for (int l = i + k; l < (int)arr.size(); l++)
    b.push_back(arr[l]);
  vector<int> c;
  for (int l = 0; l < j; l++)
    c.push_back(b[l]);
  for (int l = i; l < i + k; l++)
    c.push_back(arr[l]);
  for (int l = j; l < (int)b.size(); l++)
    c.push_back(b[l]);
  arr = c;
}

// Rotate the array: move elements from index i1 to end to the front
void rot(vector<int> &a, int i1) {
  vector<int> b;
  for (int i = i1; i < (int)a.size(); i++)
    b.push_back(a[i]);
  for (int i = 0; i < i1; i++)
    b.push_back(a[i]);
  a = b;
}

void solve() {
  scanf("%d", &n);
  arr.clear();
  arr.resize(n);
  ans.clear();
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
    arr[i]--;
  }
  int counter = 0;
  for (int nxt, i = 0; i < n; i++) {
    nxt = i + 1;
    if (i == n - 1)
      nxt = 0;
    if (arr[nxt] < arr[i])
      counter++;
  }
  if (counter == 1) { // Special case: if there's only one drop in rotation
    if (arr[0] == 0) {
      printf("%d\n0\n", n);
      return;
    }
    printf("%d\n", n - 1);
    for (int i = 0; i < n; i++) {
      if (arr[i] == 0)
        break;
      ans.push_back(make_pair(1, 0));
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++)
      printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    return;
  }
  k = n - 2;
  if (n % 2 == 0) {
    int counter = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (arr[j] < arr[i])
          counter++;
    if (counter % 2 != 0)
      k = n - 3;
  }
  printf("%d\n", k);
  if (k == n - 3) {
    int idx = 0;
    while (arr[idx] != n - 1)
      idx++;
    int inc = 0;
    while (idx + inc < k - 1) {
      inc += 3;
      ans.push_back({0, 3});
    }
    int last = idx + (n - 1 - (idx + inc));
    rot(arr, last + 1);
    idx += inc;
    if (idx < n - 1) {
      ans.push_back({idx - k + 1, 3});
      make(arr, k, idx - k + 1, 3);
    }
    n--;
    arr.pop_back();
  }
  for (int idx, idx2, val = 1; val < n; val++) {
    idx = 0;
    while (arr[idx] != val)
      idx++;
    idx2 = idx;
    while (idx > 1) {
      idx -= 2;
      ans.push_back({2, 0});
    }
    rot(arr, (idx % 2 == 0 ? idx2 : idx2 - 1));
    if (idx == 1) {
      rot(arr, idx + 1);
      ans.push_back({2, 0});
      idx = n - 1;
    }
    vector<int> b;
    for (int i = 0; i < n; i++) {
      if (arr[i] != val)
        b.push_back(arr[i]);
    }
    idx2 = 0;
    while (b[idx2] != val - 1)
      idx2++;
    rot(b, idx2 + 1);
    while (idx2 + 1 < (int)b.size()) {
      ans.push_back((idx == 0 ? make_pair(1, 2) : make_pair(0, 1)));
      idx2++;
    }
    arr = b;
    if (idx == 0)
      arr.insert(arr.begin(), val);
    else
      arr.push_back(val);
  }
  if (arr.back() != n - 1) {
    ans.push_back({1, 0});
    for (int it = 0; it < (n - 1) / 2; it++)
      ans.push_back({2, 0});
    ans.push_back({1, 0});
  }
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < (int)ans.size(); i++)
    printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/