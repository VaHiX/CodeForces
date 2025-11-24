// Problem: CF 996 A - Hit the Lottery
// https://codeforces.com/contest/996/problem/A

/*
Code Purpose:
This code solves the "Hit the Lottery" problem where we need to find the minimum number of bills to withdraw a given amount n.
The denominations available are 1, 5, 10, 20, and 100 dollars.
We use a greedy approach: always take the largest denomination possible first, then move to smaller ones.

Algorithms/Techniques:
- Greedy Algorithm: Always pick the largest possible bill denomination at each step to minimize total bills.

Time Complexity: O(1) - Since there are only a fixed number of denominations (5), and we perform a constant number of operations.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 200100
#define inf 100000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;

int main() {
  int i, j, k;
  int n, m, r;
  m = 0; // Initialize count of bills
  cin >> n; // Read the total amount
  
  // Greedily use the largest denomination first
  if (n / 100) // If we can use at least one 100-dollar bill
    m += (n / 100), n -= (n / 100) * 100; // Add number of 100s to bill count and reduce n accordingly
  
  if (n / 20) // If we can use at least one 20-dollar bill
    m += (n / 20), n -= (n / 20) * 20; // Add number of 20s to bill count and reduce n accordingly
  
  if (n / 10) // If we can use at least one 10-dollar bill
    m += (n / 10), n -= (n / 10) * 10; // Add number of 10s to bill count and reduce n accordingly
  
  if (n / 5) // If we can use at least one 5-dollar bill
    m += (n / 5), n -= (n / 5) * 5; // Add number of 5s to bill count and reduce n accordingly
  
  m += n; // Remaining amount is made up of 1-dollar bills
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/