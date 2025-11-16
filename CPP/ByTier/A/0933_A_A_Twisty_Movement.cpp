// Problem: CF 933 A - A Twisty Movement
// https://codeforces.com/contest/933/problem/A

/*
 * Problem: A Twisty Movement
 * Algorithm: Dynamic Programming
 * 
 * We are given a sequence of 1s and 2s, and we can reverse any subsegment to maximize 
 * the length of the longest non-decreasing subsequence.
 * 
 * This solution uses a dynamic programming approach:
 * - For each element in the sequence, we maintain a state array `d` where d[j] represents 
 *   the maximum length of a non-decreasing subsequence ending with value j (where j can be 1 or 2).
 * - Since we only care about the last two elements of the subsequence (as values are only 1 or 2),
 *   we can optimize space and track the best subsequence ending in 1 or 2.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;
int n, x, j, d[6];  // d[0..5] is used to store dp states
int main() {
  cin >> n;
  while (n--) {
    cin >> x;
    // Update dp states: for each incoming element x,
    // we calculate the new maximum lengths of subsequences ending in 1 or 2
    for (j = 2; j < 6; ++j)
      d[j] = max(d[j - 1], d[j] + (j % 2 + 1 == x));
  }
  cout << d[5];  // Output the maximum length of non-decreasing subsequence
}


// https://github.com/VaHiX/CodeForces/