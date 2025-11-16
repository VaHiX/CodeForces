// Problem: CF 1985 F - Final Boss
// https://codeforces.com/contest/1985/problem/F

/*
Algorithm: Binary Search on Answer
Approach:
- Use binary search to find the minimum number of turns needed to defeat the boss.
- For a given number of turns T, calculate the total damage that can be dealt.
- This is done by counting how many times each attack can be used in T turns,
  i.e., (T - 1) / cooldown[i] + 1 for each attack.
- If the total damage is sufficient, we can try a smaller number of turns.
- If not, we need to increase the number of turns.

Time Complexity: O(n * log(max_turns))
Space Complexity: O(1) excluding input storage
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Function to check if the boss can be defeated in 'T' turns
bool canDefeat(long long T, const vector<int> &damages,
               const vector<int> &cooldowns, long long h) {
  long long total = 0;
  for (int i = 0; i < damages.size(); ++i) {
    // Calculate number of times attack i can be used in T turns
    long long cnt = (T - 1) / cooldowns[i] + 1;
    total += cnt * damages[i];
    // Early exit if we already defeated the boss
    if (total >= h) {
      return true;
    }
  }
  return total >= h;
}

// Binary search to find minimum number of turns
long long findMinRounds(long long h, const vector<int> &damages,
                        const vector<int> &cooldowns) {
  long long left = 1;
  long long right = 1;
  // Double right until it's enough to defeat the boss
  while (!canDefeat(right, damages, cooldowns, h)) {
    right *= 2;
  }
  // Binary search for the minimum number of turns
  while (left < right) {
    long long mid = left + (right - left) / 2;
    if (canDefeat(mid, damages, cooldowns, h)) {
      right = mid; // Try to find a smaller number of turns
    } else {
      left = mid + 1; // Need more turns
    }
  }
  return left;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int h, n;
    cin >> h >> n;
    vector<int> damages(n);
    vector<int> cooldowns(n);
    for (int i = 0; i < n; ++i) {
      cin >> damages[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> cooldowns[i];
    }
    cout << findMinRounds(h, damages, cooldowns) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/