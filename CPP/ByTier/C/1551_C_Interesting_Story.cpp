// Problem: CF 1551 C - Interesting Story
// https://codeforces.com/contest/1551/problem/C

/*
C. Interesting Story
Algorithms/Techniques: Greedy with sorting, brute force over letters a-e
Time Complexity: O(20 * n * log(n)) per test case where n is the number of words
Space Complexity: O(n) for storing the count array and words

The problem asks us to find the maximum number of words that can form an "interesting" story.
An interesting story is one where there exists a letter that occurs more times than all other letters combined.

Approach:
- For each possible letter (a through e), compute how many times each word contributes to that letter's count
- Positive contribution if the word contains the letter, negative otherwise
- Sort these contributions in descending order to greedily select words with highest net contribution for that letter
- Use greedy selection: keep adding words as long as cumulative sum remains positive
- Track maximum across all 5 letters
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q;
  cin >> q;
  while (q--) {
    int n;
    cin >> n;
    vector<string> words(n);
    for (string &s : words)
      cin >> s;
    int ans = 0;
    for (char l = 'a'; l <= 'e'; l++) {
      vector<int> cnt(n, 0); // cnt[i] stores net contribution of word i to letter l
      for (int i = 0; i < n; i++)
        for (char c : words[i]) {
          cnt[i] += (c == l ? 1 : -1); // Positive if word contains letter l, negative otherwise
        }
      sort(cnt.rbegin(), cnt.rend()); // Sort in descending order to pick best words first
      int x = 0, y = 0;
      for (int i : cnt)
        if (y + i > 0) // Only include word if adding it keeps total positive
          x++, y += i;
      ans = max(ans, x); // Track maximum number of words for any letter
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/codeForces/