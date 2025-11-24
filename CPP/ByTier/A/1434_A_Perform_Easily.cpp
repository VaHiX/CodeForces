// Problem: CF 1434 A - Perform Easily
// https://codeforces.com/contest/1434/problem/A

/*
Algorithm: Two-Pointer Technique with Sorting
Time Complexity: O(N * S * log(N * S)) where N is the number of notes and S is the number of strings (6)
Space Complexity: O(N * S) for storing all note-string combinations

The problem is to minimize the difference between the maximum and minimum fret indices used to play a melody.
We can use a greedy approach with sorting:
1. For each note, we compute all possible frets on all strings.
2. We sort these (fret_index, string_gap) pairs.
3. We use a two-pointer technique to find the minimum difference by adjusting the maximum fret based on string gaps.
*/

#include <algorithm>
#include <cstdio>
#include <functional>
#include <utility>
const int S = 6;
const int N = 100000;
int n, a[S];
std::pair<int, int> b[N * S]; // Stores (fret_index, next_string_gap)
int main() {
  for (int i = 0; i < S; ++i)
    scanf("%d", a + i);
  // Sort strings in descending order to get the highest frets first
  std::sort(a, a + S, std::greater<int>());
  scanf("%d", &n);
  int mx = 0; // Tracks the maximum fret index used so far
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    // For each note, generate all possible fret positions on each string
    for (int j = 0; j < S; ++j)
      // Store pair of (fret_index, string_gap_to_next_string)
      b[i * S + j] =
          std::make_pair(v - a[j], j + 1 < S ? a[j] - a[j + 1] : ~(1 << 31));
    // Update the maximum fret index seen so far
    mx = std::max(mx, v - a[0]);
  }
  // Sort all generated fret-position pairs
  std::sort(b, b + n * S);
  int ans = ~(1 << 31); // Initialize result to maximum int value
  for (int i = 0;; ++i) {
    // Calculate difference between current max fret and current min fret
    ans = std::min(ans, mx - b[i].first);
    // If we've reached the end (last string gap), stop
    if (b[i].second == ~(1 << 31))
      break;
    // Update maximum fret when we move to a higher string
    mx = std::max(mx, b[i].first + b[i].second);
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/