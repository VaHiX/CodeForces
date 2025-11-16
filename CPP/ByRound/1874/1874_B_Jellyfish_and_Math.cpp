// Problem: CF 1874 B - Jellyfish and Math
// https://codeforces.com/contest/1874/problem/B

/*
 * Problem: Jellyfish and Math
 * Purpose: Find minimum number of operations to transform (a,b) to (c,d) using bitwise operations.
 * 
 * Algorithms/Techniques:
 * - Bitwise state compression and BFS on the 8-bit states (each bit position is a state transition)
 * - Each bit position is encoded as 0,1,2,3,4 representing possible combinations of (x,y,m) bits
 * - BFS to find shortest path from initial state to target state
 * 
 * Time Complexity: O(5^8) = O(390625) for precomputing all states, and O(1) per query
 * Space Complexity: O(5^8) = O(390625) for storing BFS distances
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <deque>
#include <vector>

int a, b, c, d, m;
int S[55], tar[1 << 10], dis[400004];

void solve() {
  scanf("%d%d%d%d%d", &a, &b, &c, &d, &m);
  // Encode each bit position as a value from 0 to 4 representing combinations of (x,y,m)
  for (int i = 0; i < 30; ++i) {
    int c1 = (a >> i) & 1;
    int c2 = (b >> i) & 1;
    int c3 = (m >> i) & 1;
    S[i] = c3 * 4 + c1 * 2 + c2;
  }
  // Check if target states are compatible
  memset(tar, -1, sizeof(tar));
  for (int i = 0; i < 30; ++i) {
    int c1 = (c >> i) & 1;
    int c2 = (d >> i) & 1;
    if (tar[S[i]] == -1) {
      tar[S[i]] = c1 * 2 + c2;
    } else if (tar[S[i]] != c1 * 2 + c2) {
      puts("-1");
      return;
    }
  }
  // Convert target state to a base-5 number for BFS lookup
  int T1 = 0;
  for (int i = 7; i >= 0; i--) {
    T1 = T1 * 5;
    if (tar[i] == -1)
      T1 = T1 + 4;
    else
      T1 = T1 + tar[i];
  }
  printf("%d\n", dis[T1]);
}

// Operation OR(x, y): x := x | y
int OR(int u) {
  int pw = 1, v = 0;
  for (int i = 0; i < 8; ++i) {
    int s = u % 5;
    u /= 5;
    int t;
    if (s == 4)
      t = 4;
    else {
      t = (s & 1) + 2 * (((s >> 1) & 1) | (s & 1));
    }
    v += pw * t;
    pw *= 5;
  }
  return v;
}

// Operation AND(x, y): x := x & y
int AND(int u) {
  int pw = 1, v = 0;
  for (int i = 0; i < 8; ++i) {
    int s = u % 5;
    u /= 5;
    int t;
    if (s == 4)
      t = 4;
    else {
      t = (s & 1) + 2 * (((s >> 1) & 1) & (s & 1));
    }
    v += pw * t;
    pw *= 5;
  }
  return v;
}

// Operation XOR(x, y): y := x ^ y
int XY(int u) {
  int pw = 1, v = 0;
  for (int i = 0; i < 8; ++i) {
    int s = u % 5;
    u /= 5;
    int t;
    if (s == 4)
      t = 4;
    else {
      t = 2 * ((s >> 1) & 1) + (((s >> 1) & 1) ^ (s & 1));
    }
    v += pw * t;
    pw *= 5;
  }
  return v;
}

// Operation XOR(y, m): y := y ^ m
int XM(int u) {
  int pw = 1, v = 0;
  for (int i = 0; i < 8; ++i) {
    int s = u % 5;
    u /= 5;
    int t;
    int m = (i >> 2) & 1;  // Get corresponding bit from m
    if (s == 4)
      t = 4;
    else {
      t = 2 * ((s >> 1) & 1) + ((s & 1) ^ m);
    }
    v += pw * t;
    pw *= 5;
  }
  return v;
}

// Operation FIX(u, y): Set y-th bit to 4 (invalid state)
int FIX(int u, int y) {
  int pw = 1, v = 0;
  for (int i = 0; i < 8; ++i) {
    int s = u % 5;
    u /= 5;
    int t = s;
    if (y == i) {
      t = 4;
    }
    v += pw * t;
    pw *= 5;
  }
  return v;
}

int main() {
  // Initialize the starting state (0,0,0,0,0,0,0,0) as base-5 number
  int S = 0;
  for (int i = 7; i >= 0; i--) {
    int c2 = i & 1;
    int c1 = (i / 2) & 1;
    S = S * 5 + c1 * 2 + c2;
  }
  // BFS Initialization - Set distance to starting state as 0
  memset(dis, -1, sizeof(dis));
  dis[S] = 0;
  std::deque<int> q;
  q.push_back(S);
  
  // Compute all possible reachable states using BFS
  while (!q.empty()) {
    int u = q.front();
    q.pop_front();
    
    // Apply operations that change x or y
    std::vector<int> trans1 = {OR(u), AND(u), XY(u), XM(u)};
    
    // Apply operations that don't change x/y but modify bit position
    std::vector<int> trans0;
    for (int i = 0; i < 8; ++i)
      trans0.push_back(FIX(u, i));
    
    // Process FIX operations (no change in number of steps)
    for (int T : trans0) {
      if (dis[T] != -1 && dis[T] <= dis[u])
        continue;
      dis[T] = dis[u];
      q.push_front(T);  // Place at front to prioritize these operations
    }
    
    // Process OR, AND, XY, XM operations (1 step increment)
    for (int T : trans1) {
      if (dis[T] != -1 && dis[T] <= dis[u] + 1)
        continue;
      dis[T] = dis[u] + 1;
      q.push_back(T);  // Place at back for normal BFS behavior
    }
  }
  
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/