// Problem: CF 1718 A2 - Burenka and Traditions (hard version)
// https://codeforces.com/contest/1718/problem/A2

/*
Code Purpose:
This solution computes the minimum time required to reduce all elements of an array to zero using a specific XOR operation on subarrays.
The approach uses a prefix XOR technique to detect when a subarray can be XORed with a value to make its elements zero.
It calculates the number of independent segments that require operations and uses that to determine the total time.

Algorithms/Techniques:
- Prefix XOR
- Hash map for tracking seen prefix XORs
- Greedy segment selection based on prefix XOR properties

Time Complexity:
O(n) per test case, where n is the size of the array.
The loop processes each element once and hash map operations are amortized O(1).

Space Complexity:
O(n) for the hash map in the worst case, storing all unique prefix XOR values.
*/

#include <iostream>
#include <map>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    map<int, int> mp;  // Map to store prefix XOR values and their occurrence
    mp[0] = 1;  // Initialize with 0 to handle cases starting from index 1
    int pre = 0, cnt = 0, a;  // 'pre' is prefix XOR, 'cnt' counts operations, 'a' reads array elements
    for (int i = 2; i <= n + 1; i++) {  // Loop from 2 to n+1 (1-indexed logic)
      cin >> a;
      pre = pre ^ a;  // Compute prefix XOR
      if (mp[pre] > 0) {  // If this prefix XOR was seen before, a segment can be processed
        cnt++;  // Increment operation count
        mp.clear();  // Clear the map to start fresh for next segment
      }
      mp[pre] = 1;  // Mark current prefix XOR as seen
    }
    cout << n - cnt << endl;  // Output the minimum time
  }
}


// https://github.com/VaHiX/CodeForces/