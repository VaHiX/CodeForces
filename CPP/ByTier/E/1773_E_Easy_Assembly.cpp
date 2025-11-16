// Problem: CF 1773 E - Easy Assembly
// https://codeforces.com/contest/1773/problem/E
//
// Overview:
// Given n sequences of integers, this solution computes two values:
// - ans1: the number of "breaks" needed when concatenating pieces to
//   attempt to produce the globally sorted sequence (counting unavoidable
//   order violations)
// - ans2: the number of segments processed (minus one in final output)
//
// Approach (high level):
// 1. For each input sequence, split it into monotone nondecreasing blocks
//    at positions where a[i][j] > a[i][j+1] (each block is pushed into a
//    priority queue). Increment ans1 for every split found inside a sequence.
// 2. Collect all values into array `b` and sort it to know the target order.
// 3. Repeatedly take the smallest block (lexicographically, since queue
//    uses `greater<>` on deques) and try to match its elements against the
//    sorted array `b` starting at current position `j`. If a mismatch occurs
//    inside the block, increment ans1 (we'll need an extra break). Otherwise
//    consume prefix elements from the block and, if the block is not empty,
//    push it back. Count how many blocks were processed in ans2.

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  // b: flattened list of all values (for global sort)
  vector<int> b;

  // a[i]: deque for the i-th input sequence (we keep deque to pop from front)
  vector<deque<int>> a(n);

  // Priority queue of blocks (each block is a deque<int>); using greater<>
  // makes the smallest block lexicographically come first (heap root).
  priority_queue<deque<int>, vector<deque<int>>, greater<>> q;

  i64 ans1 = 0, ans2 = 0;

  // Read sequences and split them into monotone nondecreasing blocks.
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    a[i].resize(k);
    for (int j = 0; j < k; j++) {
      cin >> a[i][j];
      b.push_back(a[i][j]);
    }

    // Break sequence into blocks at each strict descent
    deque<int> c;
    for (int j = 0; j < k - 1; j++) {
      c.push_back(a[i][j]);
      if (a[i][j] > a[i][j + 1]) {
        // descent detected -> end of current block
        ans1++;    // internal split counted toward ans1
        q.push(c); // push completed block into priority queue
        c = {};
      }
    }
    // push the final block (contains last element)
    c.push_back(a[i][k - 1]);
    q.push(c);
  }

  // Sort flattened values to know the target global order
  int j = 0;
  sort(b.begin(), b.end());

  // Process blocks in increasing lexicographic order (smallest deque first)
  while (!q.empty()) {
    auto now = q.top();
    q.pop();
    int cnt = 0; // number of matched elements consumed from front of `now`
    for (int i = 0; i < (int)now.size(); i++) {
      if (now[i] != b[j]) {
        // mismatch inside block: we need an extra break to reorder
        ans1++;
        break;
      } else {
        // matched: advance global pointer j and mark this element consumed
        j++;
        cnt++;
      }
    }

    // remove consumed elements from front of the deque
    while (cnt--) {
      now.pop_front();
    }
    // if block still contains elements, push it back into queue
    if (!now.empty()) {
      q.push(now);
    }
    // we processed one block (either fully matched or caused a break)
    ans2++;
  }

  // Output: ans1 (number of breaks) and ans2-1 (as problem expects)
  cout << ans1 << ' ' << ans2 - 1 << '\n';
  return 0;
}

// https://github.com/VaHiX/CodeForces/