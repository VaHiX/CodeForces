// Problem: CF 2164 D - Copy String
// https://codeforces.com/contest/2164/problem/D

/*
Algorithms/Techniques: Binary Search + Greedy Construction
Time Complexity: O(n * k_max) where n is the length of strings and k_max is the maximum operations allowed
Space Complexity: O(n) for storing the strings and intermediate results

The problem requires transforming string s into string t using a specific operation where each character of the new string can either be the same as the original or the previous character in the original string. The goal is to find the minimum number of operations needed to do so, or return -1 if it's not possible within k_max steps.

The approach uses binary search on the number of operations (from 0 to k_max), and for each candidate number, it checks whether it's possible to transform s into t using that many operations. If yes, it then constructs the actual steps required to perform the transformation.
*/

#include <iostream>
#include <string>

using namespace std;
#define ll long long
int n, k;
string s, t;

// Function to check if transformation is possible within x operations
bool check(int x) {
  // For each position in t, we need to match it with a character from s
  // j is the index in t that we are trying to match with s[i]
  for (int i = 0, j = -1; i < n; i++) {
    // While j+1 is within bounds and the difference between j+1 and i is <= x
    // and the character at t[j+1] matches s[i], we increment j
    while (j + 1 < n && j + 1 - i <= x && t[j + 1] == s[i])
      j++;
    // If j is less than i, means we couldn't find a match within x operations
    if (j < i)
      return false;
  }
  return true;
}

// Function to actually construct the steps needed to transform s into t in x operations
void construct(int x) {
  cout << x << '\n';
  // We process from x down to 1 to generate the sequence of transformations
  for (; x >= 1; x--) {
    string s1 = s; // Create new string s1 as a copy of s
    for (int i = 0, j = -1; i < n; i++) {
      // Similar logic as in check()
      while (j + 1 < n && j + 1 - i <= x && t[j + 1] == s[i])
        j++;
      // If j is greater than i, it indicates that s[i] can be replaced by s[i+1] which is the same as s[i+1]
      if (j > i)
        s1[i + 1] = s[i];
    }
    s = s1;
    cout << s << "\n";
  }
}

void solve() {
  cin >> n >> k >> s >> t;
  // Try all possible numbers of operations from 0 to k
  for (int i = 0; i <= k; i++)
    if (check(i)) {
      // If solution found, construct the steps
      construct(i);
      return;
    }
  // If no solution found within k operations
  cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/