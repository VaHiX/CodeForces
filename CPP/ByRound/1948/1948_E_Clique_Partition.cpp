// Problem: CF 1948 E - Clique Partition
// https://codeforces.com/contest/1948/problem/E

/*
Purpose: This code solves the "Clique Partition" problem by assigning integers to vertices of a graph such that the resulting graph can be partitioned into the minimum number of cliques. The assignment is such that an edge exists between vertices i and j if |i-j| + |a_i - a_j| <= k.

Algorithms/Techniques:
- Greedy assignment of labels to minimize clique number.
- Special handling for k = 0 and k = 1.
- Use of a custom ordering to group vertices into cliques based on how they are assigned.

Time Complexity: O(N) per test case, where N is the number of vertices.
Space Complexity: O(N) for storing the labels and partition result.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

// Template to update maximum value
template <class T> bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

// Template to update minimum value
template <class T> bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define mp make_pair
#define si(x) int(x.size())
const int mod = 998244353, MAX = 5005, INF = 1 << 30;

int main() {
  std::ifstream in("text.txt");
  std::cin.rdbuf(in.rdbuf());
  cin.tie(0);
  ios::sync_with_stdio(false);
  int Q;
  cin >> Q;
  while (Q--) {
    int N, K;
    cin >> N >> K;
    if (K == 0 || K == 1) {
      // For k = 0 or 1, assign vertices in order to avoid any edges
      for (int i = 0; i < N; i++) {
        if (i)
          cout << " ";
        cout << i + 1;
      }
      cout << "\n";
      cout << N << "\n";
      for (int i = 0; i < N; i++) {
        if (i)
          cout << " ";
        cout << i + 1;
      }
      cout << "\n";
    } else {
      // For k >= 2, construct a specific labeling to minimize cliques
      vector<int> ans;
      for (int i = 0; i < N; i += K) {
        int s = i, t = min(N - 1, i + K - 1);
        int len = t - s + 1;
        if (len == 1)
          ans.push_back(s);
        else if (len == 2) {
          ans.push_back(s);
          ans.push_back(t);
        } else if (len & 1) {
          // Odd length: arrange in a zigzag pattern to keep cliques minimal
          int x = len / 2, y = len - x;
          for (int j = s + x - 1; j >= s; j--)
            ans.push_back(j);
          for (int j = t; j > s + x - 1; j--)
            ans.push_back(j);
        } else {
          // Even length: again, use a zigzag pattern for optimization
          int x = len / 2 - 1, y = len - x;
          for (int j = s + x - 1; j >= s; j--)
            ans.push_back(j);
          for (int j = t; j > s + x - 1; j--)
            ans.push_back(j);
        }
      }
      // Output the assignment
      for (int i = 0; i < N; i++) {
        if (i)
          cout << " ";
        cout << ans[i] + 1;
      }
      cout << "\n";
      // Number of cliques needed
      cout << (N + K - 1) / K << "\n";
      // Assign vertices to cliques
      for (int i = 0; i < N; i++) {
        if (i)
          cout << " ";
        cout << i / K + 1;
      }
      cout << "\n";
    }
  }
}


// https://github.com/VaHiX/CodeForces/