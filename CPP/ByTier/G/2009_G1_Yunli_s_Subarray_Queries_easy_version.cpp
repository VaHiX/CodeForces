// Problem: CF 2009 G1 - Yunli's Subarray Queries (easy version)
// https://codeforces.com/contest/2009/problem/G1

/*
Purpose: 
This code solves the problem of finding the minimum number of operations needed to form a consecutive subarray of length k in a given array, for each query. The key idea is to use a sliding window technique combined with frequency counting to efficiently compute answers for all possible subarrays of length k.

Algorithms/Techniques:
- Sliding window to maintain a window of size k
- Frequency counting of (a[i] - i) values to determine how many elements in the window follow a linear pattern
- Efficient update of frequency counts when elements enter or exit the window
- Preprocessing and answering queries in O(N + Q) time

Time Complexity:
O(N + Q) where N is the size of the array and Q is the number of queries.
Each element is processed once during the sliding window and each query is answered in O(1).

Space Complexity:
O(N) for storing the array, frequency arrays, and answer array.
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
void solve() {
  int N, K, Q;
  cin >> N >> K >> Q;
  vector<int> a(N);
  for (int i = 0; i < N; i++)
    cin >> a[i], a[i] += N; // Add N to prevent negative indices
  vector<int> answers(N - K + 2); // Store answer for each starting index of subarray of length K
  vector<int> freq(2 * N + 2, 0); // Frequency of (a[i] - i) values
  vector<int> count(K + 2, 0); // Count of how many values have a specific frequency
  int max_freq = 0; // Maximum frequency in current window

  // Initialize the first window of size K
  for (int i = 0; i < K; i++) {
    int val = a[i] - i; // Value used to identify arithmetic sequences
    count[freq[val]]--; // Decrement count of old frequency
    freq[val]++; // Increment frequency
    count[freq[val]]++; // Increment count of new frequency
    max_freq = max(max_freq, freq[val]); // Update maximum frequency
  }
  answers[1] = K - max_freq; // Minimum operations for first window

  // Slide the window over the rest of the array
  for (int i = K; i < N; i++) {
    // Remove the leftmost element of previous window
    int out_val = a[i - K] - (i - K);
    count[freq[out_val]]--; // Decrement count of old frequency
    freq[out_val]--; // Decrement frequency
    count[freq[out_val]]++; // Increment count of new frequency
    if (count[max_freq] == 0) // If max frequency is no longer valid
      max_freq--; // Reduce max frequency

    // Add the new rightmost element of current window
    int in_val = a[i] - i;
    count[freq[in_val]]--; // Decrement count of old frequency
    freq[in_val]++; // Increment frequency
    count[freq[in_val]]++; // Increment count of new frequency
    if (freq[in_val] > max_freq) // If new frequency is higher than current max
      max_freq = freq[in_val]; // Update max frequency

    // Store the minimum operations required for current window
    answers[i - K + 2] = K - max_freq;
  }

  // Process each query
  for (int query = 0; query < Q; query++) {
    int l, r;
    cin >> l >> r;
    cout << answers[l] << '\n'; // Output the precomputed answer for query range
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/