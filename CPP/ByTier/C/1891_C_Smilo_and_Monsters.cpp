// Problem: CF 1891 C - Smilo and Monsters
// https://codeforces.com/contest/1891/problem/C

/*
Algorithm: Greedy with Deque
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for the deque storage

This solution uses a greedy approach to minimize the number of attacks.
We sort the horde sizes and use a deque to efficiently access both ends.
The combo counter 'com' tracks how many monsters we can eliminate with ultimate attack.
We process the smallest horde first, using regular attacks to build up combo,
and use ultimate attack when beneficial to reduce total attack count.
*/
#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
int t, n;
void solve() {
  cin >> n;
  deque<int> deq(n);
  for (int &e : deq)
    cin >> e;
  sort(deq.begin(), deq.end()); // Sort the horde sizes
  int com = 0; // Combo counter
  long long sum = 0; // Total number of attacks
  while (deq.size()) { // Continue until all hordes are cleared
    if (deq.size() == 1) { // If only one horde left
      if (deq.front() == 1) {
        sum++; // One regular attack
        break;
      }
      if (deq.front()) // If there are monsters in the last horde
        sum++; // One regular attack to reduce it to 1
      if (com < deq.front()) // If combo can help reduce attack count
        sum += (deq.front() - com + 1) / 2; // Calculate minimum attacks needed
      deq.pop_back(); // Remove the last horde
    } else { // Multiple hordes remain
      if (com + deq.front() < deq.back()) { // If combo+smallest < largest
        sum += deq.front(); // Attack smallest horde completely
        com += deq.front(); // Increase combo by number of monsters attacked
        deq.pop_front(); // Remove smallest horde
      } else { // If combo is sufficient to trigger ultimate attack
        deq.front() -= (deq.back() - com); // Reduce monsters in smallest horde
        sum += deq.back() - com + 1; // Count of attacks to use ultimate
        com = 0; // Reset combo counter
        deq.pop_back(); // Remove largest horde
      }
    }
  }
  cout << sum << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/