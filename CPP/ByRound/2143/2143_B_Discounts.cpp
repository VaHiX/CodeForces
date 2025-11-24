// Problem: CF 2143 B - Discounts
// https://codeforces.com/contest/2143/problem/B

/*
B. Discounts

Algorithm: Greedy with sorting
- Sort products by price in ascending order
- Sort vouchers by price in descending order
- For each voucher, apply it to the last (most expensive) available products
- The cheapest product in a group is free, so we subtract its cost from result
Time Complexity: O(n log n + k log k)
Space Complexity: O(1)

Input:
Each test contains multiple test cases. The first line contains the number of test cases t (1 ≤ t ≤ 10^4).
The first line contains two integers n and k (1 ≤ n, k ≤ 2*10^5) — the number of products and the number of available discount vouchers.
The second line contains n integers a_1, a_2, ..., a_n (1 ≤ a_i ≤ 10^9) — the prices of the products.
The third line contains k integers b_1, b_2, ..., b_k (1 ≤ b_i ≤ n) — the values of the discount vouchers.

Output:
Print t lines. The i-th line should contain the answer for the i-th test case — the minimum total cost required to purchase all products in that test case.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(NULL); // Disable sync with C stdio for faster I/O
  cin.tie(0);                 // Untie cin from cout
  cout.tie(0);                // Untie cout from cin

  int t;
  cin >> t;
  while (t--) {
    int n, k, a[200001], b[200001]; // Arrays to store product prices and voucher values
    cin >> n >> k;
    long long res = 0; // Initialize total cost to 0
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      res += a[i]; // Add all products' price to the total (baseline cost)
    }
    for (int i = 1; i <= k; i++)
      cin >> b[i];

    sort(a + 1, a + n + 1);       // Sort product prices in ascending order
    sort(b + 1, b + k + 1);       // Sort voucher values (not yet sorted by descending)

    long long j = n + 1;          // Pointer to the last unassigned product
    for (int i = 1; i <= k; i++) {
      j -= b[i];                  // Move pointer back by voucher value (size of group)
      if (j >= 1)                 // If valid index
        res -= a[j];              // Subtract cheapest item in current group (free item)
    }
    cout << res << endl;          // Output the minimum total cost
  }
}


// https://github.com/VaHiX/codeForces/