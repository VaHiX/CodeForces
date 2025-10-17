// Problem: CF 2133 B - Villagers
// https://codeforces.com/contest/2133/problem/B

/*
B. Villagers
======================================
Task: Minimize the total number of emeralds given to make all villagers friends.
Algorithm:
- Greedily pair villagers with highest grumpiness values.
- For each pair (i, j), give max(g[i], g[j]) emeralds.
- Each pairing reduces grumpiness by min(g[i], g[j]).
- To connect all villagers into one component, we need exactly n - 1 operations.
- Sort grumpiness in descending order and pick every second element to minimize cost.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for input array storage
======================================
*/
using System.Data;
using System.Net.Http.Headers;
using System.Runtime.Intrinsics.Arm;
using static System.Console;

int t = int.Parse(Console.ReadLine());
while (t-- > 0) {
  int n = int.Parse(Console.ReadLine());
  int[] nums = ReadLine().Split(' ').Select(int.Parse).ToArray();
  Array.Sort(nums); // Sort in ascending order
  long ans = 0;
  for (int i = nums.Length - 1; i >= 0; i -= 2) {
    // Take the largest remaining element and add it to total (greedy)
    ans += nums[i];
  }
  WriteLine(ans);
}


// https://github.com/VaHiX/codeForces/