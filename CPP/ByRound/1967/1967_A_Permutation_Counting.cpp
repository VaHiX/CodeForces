// Problem: CF 1967 A - Permutation Counting
// https://codeforces.com/contest/1967/problem/A

/*
 * Problem: Maximum Score from Card Permutations
 *
 * Algorithms/Techniques: Sorting, Greedy, Binary Search on Answer, Prefix Sum
 *
 * Time Complexity: O(n log n + n * log(max(a[i])))
 * Space Complexity: O(n)
 *
 * Description:
 * We are given n types of cards, where a[i] represents how many cards of type i we have.
 * We can buy up to k additional cards (can be of any type). After buying, we arrange all
 * cards in a line and count subarrays of length n that form a permutation of [1, 2, ..., n].
 * Goal is to maximize this score.
 *
 * Approach:
 * - Sort the array of card counts.
 * - Try to make all elements equal up to some point using greedy strategy.
 * - When we can't fully equalize, use remaining coins to increment values and compute final answer.
 */

#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
const int N = 2e5 + 10;
int n, k, a[N];

void work() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1); // Sort the array to apply greedy approach
  a[n + 1] = 2e13;       // Set a large value at end to handle boundary
  for (int i = 1; i <= n; i++) {
    int cha = a[i + 1] - a[i]; // Difference from next element
    if (k - cha * i >= 0) {    // Can we afford to set all elements up to now equal?
      k -= cha * i;
    } else {
      // Not enough coins to fully equalize; calculate increment and remainder
      int zj = a[i];
      zj += k / i;
      int zengj = (k % i + (n - i));
      cout << zj * n + zengj - n + 1 << endl;
      return;
    }
  }
  return;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/