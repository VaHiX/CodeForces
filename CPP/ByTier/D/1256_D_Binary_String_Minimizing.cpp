// Problem: CF 1256 D - Binary String Minimizing
// https://codeforces.com/contest/1256/problem/D

/*
D. Binary String Minimizing
Algorithm: Greedy with sliding window approach
Time Complexity: O(n^2) in worst case due to nested operations
Space Complexity: O(1) excluding input/output storage

Problem:
You are given a binary string of length n. In one move you can swap two adjacent characters.
What is the lexicographically minimum possible string you can obtain from the given one if you can perform no more than k moves?

Approach:
We process the string from left to right. For each '1' we encounter, we try to move it as far left as possible (within k swaps),
by swapping it with adjacent '0's to its left. We keep track of how many '1's we've seen so far and use that to determine how many swaps are needed.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    long long n, k;
    string s;
    cin >> n >> k >> s;
    long long l = 0; // Count of '1's seen so far
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '1') {
        l++; // Increment count of '1's
      } else {
        // Swap '1' with the element at position (i - min(l, k)) to move it left
        swap(s[i], s[i - min(l, k)]);
        k -= l; // Decrease remaining swaps by number of '1's we processed
      }
      if (k <= 0)
        break; // No more moves allowed
    }
    cout << s << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/