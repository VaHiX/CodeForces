// Problem: CF 2146 A - Equal Occurrences
// https://codeforces.com/contest/2146/problem/A

/*
Problem: Equal Occurrences
Algorithm/Technique: Frequency counting and greedy approach
Time Complexity: O(n^2) where n is the size of input array (due to nested loops)
Space Complexity: O(n) for storing frequencies in maps

Task: Find the length of the longest balanced subsequence in a non-decreasing array.
A balanced subsequence has all elements appearing with the same frequency.
*/

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

void solve() {
  int n;
  cin >> n;
  map<int, int> mp1;  // Tracks frequency of each element
  map<int, int> mp2;  // Tracks how many elements have a certain frequency
  int a;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    mp1[a]++;           // Increment frequency of current element
    mp2[mp1[a]]++;      // Increment count of elements having that frequency
  }
  int ans = 0;
  for (int i = 1; i <= 100; i++) {
    ans = max(ans, mp2[i] * i);  // For each possible frequency i, 
                                 // compute how many elements can form a balanced subsequence of that freq
  }
  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/