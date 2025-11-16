// Problem: CF 1924 F - Anti-Proxy Attendance
// https://codeforces.com/contest/1924/problem/F

/*
Algorithm: Adaptive Binary Search with Strategy Handling
Purpose: Find the absent student in a class of n students, where students may lie in their responses to queries.
         The strategy ensures that students cannot lie 3 times in a row or tell the truth 3 times in a row.

Time Complexity: O(n * log n) where n is the number of students. This accounts for the recursive queries and 
                 building of the search space using dynamic programming to determine optimal splits.

Space Complexity: O(n) due to the dp and sp arrays used for precomputing optimal split points.

The code uses a dynamic programming approach to determine how to split the student list for queries in an optimal way,
ensuring that in the worst-case scenario, the absent student is identified.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define fi first
#define se second
const ll mod = 1e9 + 7;
const int N = 2e6 + 5;
int n;
int dp[N], sp[N]; // dp represents the minimum depth of recursion needed for a group of size i
                  // sp represents the optimal split size for group of size i

// Ask a query from index l to r and return whether the number of students who raised
// their hands is equal to the actual number of students in that range.
int ask(vector<int> &v) {
  cout << "? " << v.front() << ' ' << v.back() << endl;
  int res;
  cin >> res;
  return res == (v.back() - v.front()); // Returns true if the count matches actual number of students
}

// Recursively narrow down the search space by intelligently splitting the list and asking queries.
vector<int> boom(vector<int> v) {
  int m = v.size();
  if (m < 3)
    return v; // Base case: if less than 3 students, return directly

  vector<int> nv;
  int p = sp[m]; // Get optimal split point from precomputed data
  vector<int> a, b, c;

  // Split the vector into three parts based on the split point p
  for (int i = 0; i < m; i++) {
    if (a.size() < p)
      a.push_back(v[i]);
    else if (b.size() < p)
      b.push_back(v[i]);
    else
      c.push_back(v[i]);
  }

  int r1 = ask(a); // Query first subset
  int r2 = ask(b); // Query second subset

  // If first two results are the same, we are safe to proceed
  if (r1 == r2) {
    r1 = ask(a); // Re-query to ensure consistency
    if (r1 == r2) {
      // If consistent, combine a and b and recurse (they're likely both honest or dishonest)
      for (auto p : a)
        nv.push_back(p);
      for (auto p : b)
        nv.push_back(p);
      return boom(nv);
    }
  }

  // If different, make decision based on third query on c
  {
    int r3 = ask(c); // Query third subset
    if (r1 == r3) {
      // Combine a and c
      for (auto p : a)
        nv.push_back(p);
      for (auto p : c)
        nv.push_back(p);
    } else {
      // Combine b and c
      for (auto p : b)
        nv.push_back(p);
      for (auto p : c)
        nv.push_back(p);
    }
    return boom(nv); // Recurse on the narrowed set
  }
}

// Solve one test case by finding the absent student
void solve() {
  cin >> n;
  vector<int> v(n);
  for (int i = 1; i <= n; i++)
    v[i - 1] = i; // Fill the vector with student roll numbers
  auto res = boom(v); // Start the recursive search
  for (auto x : res) {
    cout << "! " << x << endl; // Output the suspected absent student
    int res;
    cin >> res;
    if (res == 1)
      break; // If confirmed absent, exit
  }
  cout << "#" << endl; // Mark the end of test case
}

// Precompute the optimal split sizes using dynamic programming
int main() {
  ios::sync_with_stdio(false);
  sp[2] = 1;
  for (int i = 3; i <= 100000; i++) {
    sp[i] = sp[i - 1];
    dp[i] = max(4 + dp[i - sp[i]], 3 + dp[2 * sp[i]]);
    while (2 * (sp[i] + 1) < i) {
      int np = sp[i] + 1;
      int ndp = max(4 + dp[i - np], 3 + dp[2 * np]);
      if (ndp <= dp[i])
        sp[i] = np, dp[i] = ndp;
      else
        break;
    }
  }
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/