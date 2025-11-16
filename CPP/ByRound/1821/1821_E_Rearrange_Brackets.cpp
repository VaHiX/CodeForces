// Problem: CF 1821 E - Rearrange Brackets
// https://codeforces.com/contest/1821/problem/E

/*
Purpose: This program computes the minimum cost of a regular bracket sequence after performing at most k operations.
         Each operation allows extracting and reinserting a bracket to minimize the cost.
         The cost is defined as the sum of the number of closing brackets to the right of each opening bracket,
         when processing the sequence from right to left.

Algorithms/Techniques:
- Greedy approach: At each step, find the pair of brackets that contributes the highest cost and remove it.
- Suffix sum calculation for efficient cost computation.
- Stack-based matching of brackets.
- Right-to-left pass to compute the final cost.

Time Complexity: O(k * n^2), where n is the length of the string and k is the maximum allowed operations.
Space Complexity: O(n), for storing prefix sums and stack.
*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define trace(x) cerr << #x << " = " << x << endl
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = s.size();
    vector<int> psum(n + 1); // Prefix sum array to quickly calculate number of '(' in a range
    for (int it = 0; it < k; ++it) {
      int best = -1; // Best cost among all pairs
      pair<int, int> p = {-1, -1}; // Indices of the pair to remove
      fill(psum.begin(), psum.end(), 0); // Reset prefix sum array on each iteration
      for (int i = 0; i < n; ++i) {
        psum[i + 1] = psum[i] + (s[i] == '('); // Build prefix sum of opening brackets
      }
      stack<int> stk; // Stack to store indices of opening brackets
      for (int i = 0; i < n; ++i) {
        if (s[i] == '.')
          continue; // Skip removed brackets
        if (s[i] == '(') {
          stk.push(i); // Push index of opening bracket
        } else {
          int l = stk.top(); // Get index of matching '('
          stk.pop();
          int cost = psum[i] - psum[l + 1]; // Calculate cost of removing pair (l, i)
          if (cost > best) {
            best = cost;
            p = {l, i};
          }
        }
      }
      if (best > 0) {
        s[p.first] = s[p.second] = '.'; // Mark the pair as removed
      }
    }
    long long ans = 0, op = 0; // op is the balance of unmatched brackets
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == '.')
        continue; // Skip removed brackets
      if (s[i] == ')') {
        op++; // Increase balance on closing bracket
      } else {
        op--; // Decrease balance on opening bracket
        ans += op; // Add the current balance to the total cost
      }
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/