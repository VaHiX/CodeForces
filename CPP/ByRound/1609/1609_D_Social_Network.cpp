// Problem: CF 1609 D - Social Network
// https://codeforces.com/contest/1609/problem/D

/*
Code Purpose:
This code solves a problem related to a social network where people are introduced to each other based on given conditions. 
It uses Union-Find (Disjoint Set Union) data structure to efficiently manage groups of connected people and track the maximum number of acquaintances a person can have after each introduction.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression and union by size
- Simulation of introductions and tracking maximum connections

Time Complexity: O(d * α(n)) where d is the number of conditions and n is the number of people, α is the inverse Ackermann function (nearly constant)
Space Complexity: O(n) for storing parent and size arrays

*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1e6;
int n, m, f[N], c[N], a[N], x, y, s = 1, A;
int F(int x) { return f[x] == x ? x : x = F(f[x]); } // Find with path compression
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    f[i] = i, c[i] = 1; // Initialize each person as their own parent with size 1
  while (m-- && cin >> x >> y) {
    x = F(x), y = F(y), A = 0;
    if (x != y) // If x and y are in different groups
      f[y] = x, c[x] += c[y]; // Union the two groups and update size
    else
      s++; // Increment s if already in same group (for tracking in sorting)
    for (int i = 1; i <= n; i++)
      a[i] = (i == F(i)) * c[i]; // Store size of each group (only for root nodes)
    sort(a + 1, a + n + 1); // Sort group sizes in ascending order
    for (int i = 1; i <= s; i++)
      A += a[n - i + 1]; // Sum up the largest s group sizes
    cout << A - 1 << '\n'; // Output total connections minus one (max number of acquaintances)
  }
}


// https://github.com/VaHiX/CodeForces/