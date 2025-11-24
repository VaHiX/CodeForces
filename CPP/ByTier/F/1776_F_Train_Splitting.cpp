// Problem: CF 1776 F - Train Splitting
// https://codeforces.com/contest/1776/problem/F

/*
Code Purpose:
This program solves the train splitting problem where we need to assign m train routes to k private companies such that:
1. Each company operates at least one route.
2. For any single company, there exist two cities that cannot reach each other using only that company's routes.
3. For any two companies combined, all cities are reachable from each other.
The approach is to find a node with degree less than n-1, and then assign routes based on whether they involve this node.

Algorithms/Techniques:
- Graph representation using adjacency list counting
- Greedy assignment of routes to companies
- Degree-based analysis to determine k

Time Complexity: O(n + m)
Space Complexity: O(n + m)

*/
#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
#define ll long long
ll a[51], b[3003], c[3003];
int main() {
  ll t, n, m, x, k, esp, f;
  scanf("%lld", &t);
  while (t--) {
    memset(a, 0, sizeof(a)); // Initialize degree array to 0
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++) {
      scanf("%lld", &b[i]); // Read first city of route i
      a[b[i]]++; // Increment degree of first city
      scanf("%lld", &c[i]); // Read second city of route i
      a[c[i]]++; // Increment degree of second city
    }
    k = 3; // Default number of companies
    esp = 0; // Special node index (node with degree < n-1)
    for (ll i = 1; i <= n; i++) {
      if (a[i] != n - 1) { // If node has degree less than n-1
        k = 2; // Only 2 companies needed
        esp = i; // Mark this node
        break;
      }
    }
    printf("%lld\n", k); // Print number of companies
    if (esp != 0) { // If there exists a node with degree < n-1
      for (ll i = 1; i <= m; i++) {
        if (b[i] == esp || c[i] == esp) // If route involves special node
          printf("1 "); // Assign to company 1
        else
          printf("2 "); // Assign to company 2
      }
      printf("\n");
    } else { // If all nodes have degree n-1 (complete graph)
      printf("1 "); // First route to company 1
      esp = b[1]; // Use first node of first route
      for (ll i = 2; i <= m; i++) {
        if (b[i] == esp || c[i] == esp) // If route involves first node
          printf("2 "); // Assign to company 2
        else
          printf("3 "); // Assign to company 3
      }
      printf("\n");
    }
  }
}


// https://github.com/VaHiX/CodeForces/