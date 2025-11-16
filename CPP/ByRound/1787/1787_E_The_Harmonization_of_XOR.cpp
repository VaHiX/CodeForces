// Problem: CF 1787 E - The Harmonization of XOR
// https://codeforces.com/contest/1787/problem/E

#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int n, k, x;
int used[200001];
int tid;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    ++tid;
    cin >> n >> k >> x;
    vector<pair<int, int>> group; // Store pairs of numbers that XOR to x
    vector<int> others;           // Store numbers whose XOR with x is > n
    int other_xor = 0;            // XOR of all numbers in 'others'

    // If x is in range [1, n], include it as a single-element group
    if (x <= n)
      group.emplace_back(x, 0);

    for (int i = 1; i <= n; ++i) {
      if (i == x) {
        continue; // Skip x since it's already considered
      }

      // If (x ^ i) > n, then it cannot be part of a valid subsequence
      if ((x ^ i) > n) {
        others.push_back(i); // Add to 'others' array
        other_xor ^= i;      // XOR all elements in others
        continue;
      }

      // Skip if i or (x ^ i) is already used in a group
      if (used[i] == tid || used[x ^ i] == tid)
        continue;

      // Mark both elements as used
      used[i] = tid, used[x ^ i] = tid;
      group.emplace_back(i, x ^ i); // Add pair (i, x^i) to group
    }

    // If XOR of all 'others' is 0, then we can form valid partitions
    if (other_xor == 0) {
      // Check if sufficient groups exist and the parity condition holds
      if (group.size() >= k && !(group.size() - k & 1)) {
        cout << "YES\n";
        // Calculate the initial group size
        int init_size =
            others.size() + (group.size() - k) * 2 + 1 + !!group[0].second;
        cout << init_size << ' ';
        cout << group[0].first << ' '; // First element of first group
        if (group[0].second)
          cout << group[0].second
               << ' '; // Second element of first group if exists
        for (int i = 0; i < others.size(); ++i) {
          cout << others[i] << ' '; // Output other numbers
        }
        for (int i = k; i < group.size(); ++i) {
          cout << group[i].first << ' ' << group[i].second
               << ' '; // Output extra pairs
        }
        cout << '\n';
        // Print remaining groups (each of size 2)
        for (int i = 1; i < k; ++i) {
          cout << 2 << ' ' << group[i].first << ' ' << group[i].second << '\n';
        }
      } else {
        cout << "NO\n";
      }
    } else {
      cout << "NO\n";
    }
  }
}

// https://github.com/VaHiX/CodeForces/