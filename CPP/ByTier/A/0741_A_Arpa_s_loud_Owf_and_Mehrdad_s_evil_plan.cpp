// Problem: CF 741 A - Arpa's loud Owf and Mehrdad's evil plan
// https://codeforces.com/contest/741/problem/A

/*
 * Purpose: This code solves a problem involving finding the smallest value of `t` such that 
 *          for every person in a directed graph (represented by crush relationships), 
 *          if x starts a round and y becomes the Joon-Joon, then starting from y, x 
 *          also becomes the Joon-Joon. This is a cycle detection and LCM computation problem.
 *
 * Algorithm:
 * 1. Read input to build a crush relationship graph.
 * 2. Check if all nodes are reachable (i.e., every person has someone to call).
 * 3. Find cycles in the graph and compute their lengths.
 * 4. For each cycle, compute a modified length based on parity.
 * 5. Compute LCM of all such computed lengths.
 * 6. Return the LCM as the answer.
 *
 * Time Complexity: O(n^2) in worst case due to cycle detection and LCM computation.
 * Space Complexity: O(n) for storing crush relationships, visited flags, and cycle lengths.
 */

#include <iostream>
#include <vector>
long long gcd(long long a, long long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<int> crush(n + 1, 0); // Stores crush relationship for each person
  std::vector<bool> in(n + 1, 0);   // Tracks which nodes are still in use (visited)
  for (int p = 1; p <= n; p++) {
    int a;
    std::cin >> a;
    crush[p] = a;
    in[a] = 1;
  }
  bool possible(true);
  for (int p = 1; p <= n; p++) {
    possible &= in[p]; // Check if every node is reachable
  }
  if (!possible) {
    std::cout << "-1" << std::endl;
    return 0;
  }
  std::vector<int> len; // Stores cycle length adjustments
  for (int p = 1; p <= n; p++) {
    if (in[p] == 0) {
      continue; // Skip already processed nodes
    }
    int start = p;
    int t(0);
    do {
      p = crush[p];   // Follow the crush relationship
      in[p] = 0;      // Mark as visited
      ++t;
    } while (p != start); // Loop until we return to start
    len.push_back((t % 2) ? t : (t / 2)); // Adjust length for odd/even cycles
  }
  long long lcm = len[0]; // Start computing LCM
  for (int p = 1; p < len.size(); p++) {
    long long u = lcm * len[p];
    long long v = gcd(lcm, len[p]);
    lcm = u / v; // Compute LCM using GCD
  }
  std::cout << lcm << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/