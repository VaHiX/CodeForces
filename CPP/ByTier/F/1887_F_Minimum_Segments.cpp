// Problem: CF 1887 F - Minimum Segments
// https://codeforces.com/contest/1887/problem/F

/*
 * Problem: F. Minimum Segments
 * 
 * Algorithm/Technique:
 * - Validate if a sequence exists that matches the given characteristic array r.
 * - Use a greedy approach to construct the sequence:
 *   - First check for invalid conditions based on r values.
 *   - Use prefix sums to track how many unique numbers are seen up to each index.
 *   - Use a queue to manage positions where new numbers should be introduced.
 *   - Construct the actual sequence by assigning values based on previous assignments or new ones.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the sequence.
 * Space Complexity: O(n) for storing arrays and queues.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>

#define rgall(arr) (arr).begin(), (arr).end()
#define rgcnt(arr, cnt) (arr).begin(), (arr).begin() + (cnt)
#define rgo1(arr, cnt) (arr).begin() + 1, (arr).begin() + 1 + (cnt)
#define rgany(arr, cnt, offset)                                                \
  (arr).begin() + (offset), (arr).begin() + (offset) + (cnt)
using namespace std;
array<int, 200002> vals, presum, precol, answer;
queue<int> posque;

int main(int argc, char *argv[], char *envp[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  precol.fill(-1); // Initialize precol to -1
  int testcnt;
  cin >> testcnt;
  while (testcnt--) {
    int cnt;
    cin >> cnt;
    for (int i = 1; i <= cnt; i++) {
      cin >> vals[i], presum[vals[i]] = 1; // Mark presence of value in presum
      if (precol[vals[i]] == -1)
        precol[vals[i]] = i - 1; // Track first occurrence of each value
    }
    // Build prefix sum for tracking counts of numbers
    for (int i = 1; i <= cnt + 1; i++)
      presum[i] += presum[i - 1];
    bool flag = vals[1] <= cnt; // Check if first r value is valid
    int maxc = 1e9, minc = 0;
    for (int i = 1; i <= cnt; i++) {
      if (vals[i] <= cnt)
        maxc = min(maxc, vals[i] - i + 1); // Compute maximum possible segment size
      minc = max(minc, presum[vals[i]] - presum[i] + 1); // Compute minimum needed distinct elements
      if (vals[i] < i || vals[i] < vals[i - 1]) // Check for invalid r values
        flag = false;
    }
    int curc = 0;
    if (!flag || maxc < minc) { // If impossible to construct
      cout << "No";
      goto nextcase;
    }
    // Fill queue with initial positions to start assigning numbers
    for (int i = 1; i < minc; i++)
      posque.push(0);
    for (int i = 1; i <= cnt; i++) {
      // Assign position of current number based on precol or use current front of queue
      if (precol[i] == -1)
        precol[i] = posque.front(), posque.pop();
      if (vals[i] == vals[i + 1])
        posque.push(i); // Push next position to assign to new number
    }
    cout << "Yes\n";
    // Construct sequence based on precol
    for (int i = 1; i <= cnt; cout << answer[i++] << ' ')
      if (!precol[i])
        answer[i] = ++curc; // Start new number
      else
        answer[i] = answer[precol[i]]; // Copy from precol
  nextcase:
    cout << '\n';
    // Reset data structures for next test case
    for (int i = 0; i <= cnt + 1; i++)
      presum[i] = 0, precol[i] = -1;
    while (!posque.empty())
      posque.pop();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/