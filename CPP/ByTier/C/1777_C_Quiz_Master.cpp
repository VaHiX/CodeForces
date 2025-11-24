// Problem: CF 1777 C - Quiz Master
// https://codeforces.com/contest/1777/problem/C

/*
 * Problem: Quiz Master
 * 
 * Algorithm: Two-pointer technique with preprocessing of divisors
 * 
 * Time Complexity: O(N * log(N) + M * log(M)) where N is max number of students and M is max number of topics
 * Space Complexity: O(N + M) for the divisors array and counters
 * 
 * Approach:
 * - Precompute all divisors for each number up to 1e5
 * - Use a sliding window (two pointers) to find the minimal difference
 * - Track how many topics are still not covered by current window
 * - For each valid window, update the minimum difference
 * 
 * Key idea:
 * - Each student is proficient in topics that divide their smartness value
 * - A team is valid if all topics 1..m are covered by at least one team member
 * - We minimize the difference in smartness among team members
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = int(1e5) + 10;
int a[N];
int cnt[N]; // count of students proficient in each topic
vector<int> divs[N]; // list of divisors for each number up to N

// Preprocess all divisors for numbers from 1 to N-1
void process_divs() {
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divs[j].push_back(i);
    }
  }
}

// Add student with smartness 'x' to current window
// Update the count of covered topics and number of uncovered topics
void process(int x, int &num_of_profs, int &m) {
  for (auto k : divs[x]) {
    if (k > m) {
      break;
    }
    cnt[k]++;
    if (cnt[k] == 1) {
      num_of_profs--; // topic now covered
    }
  }
}

// Remove student with smartness 'x' from current window
// Update the count of covered topics and number of uncovered topics
void unprocess(int x, int &num_of_profs, int &m) {
  for (auto k : divs[x]) {
    if (k > m) {
      break;
    }
    cnt[k]--;
    if (cnt[k] == 0) {
      num_of_profs++; // topic now uncovered
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  process_divs(); // Preprocessing step
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int num_of_prof = m; // initially all topics are uncovered
    int i = 0, j = 0;
    int ans = -1;
    sort(a, a + n); // Sort for sliding window
    while (i < n) {
      // Expand window until all topics are covered
      while (j < n && num_of_prof != 0) {
        process(a[j], num_of_prof, m);
        j++;
      }
      // Check if valid window exists and update answer
      if (num_of_prof == 0) {
        ans = (ans == -1) ? a[j - 1] - a[i] : min(ans, a[j - 1] - a[i]);
      }
      // Shrink window from left
      unprocess(a[i], num_of_prof, m);
      i++;
    }
    cout << ans << "\n";
    // Reset counter array for next test case
    for (int i = 0; i <= m; i++) {
      cnt[i] = 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/