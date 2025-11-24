// Problem: CF 1794 C - Scoring Subsequences
// https://codeforces.com/contest/1794/problem/C

/*
 * Problem: C. Scoring Subsequences
 * 
 * Algorithm/Techniques: 
 * - Greedy approach with a queue to track the maximum score of subsequences
 * - For each new element in the sequence, we determine the cost (maximum length of subsequence with maximum score)
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the sequence
 * Space Complexity: O(n) for storing the input and auxiliary data structures
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
typedef long long ll;
typedef pair<int, int> pir;
const int mod = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  vector<int> ans(n + 1);
  queue<int> st; // Queue to maintain elements for calculating cost
  ans[0] = 0; // Base case: cost of empty sequence is 0
  
  for (int i = 1; i <= n; i++) {
    st.push(a[i]); // Add current element to the queue
    
    // If the front element of the queue is less than the previous cost + 1, 
    // it means we can't extend the subsequence, so we pop it
    if (st.front() < ans[i - 1] + 1) {
      st.pop();
      ans[i] = ans[i - 1]; // Cost remains the same
    } else {
      ans[i] = ans[i - 1] + 1; // Extend the subsequence, increase cost
    }
  }
  
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/