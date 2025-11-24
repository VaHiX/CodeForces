// Problem: CF 659 B - Qualifying Contest
// https://codeforces.com/contest/659/problem/B

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<ll, string> pp;
struct Compare {
  bool operator()(const pp &a, const pp &b) { return a.first < b.first; }
};
int main() {
  ll n, m;
  cin >> n >> m;
  vector<priority_queue<pp, vector<pp>, Compare>> pq(m);
  for (ll i = 0; i < n; i++) {
    string nam;
    ll r, p;
    cin >> nam >> r >> p;
    pq[r - 1].push({p, nam}); // Store each participant in their region's priority queue sorted by score
  }
  for (ll i = 0; i < m; i++) {
    if (pq[i].size() < 2) {
      cout << "?" << endl;
      continue;
    }
    pp a = pq[i].top(); // Get the highest scoring participant
    pq[i].pop();
    pp b = pq[i].top(); // Get the second highest scoring participant
    pq[i].pop();
    if (!pq[i].empty() && b.first == pq[i].top().first) {
      // If the second highest score is tied with another participant,
      // then the team is not uniquely determined
      cout << "?" << endl;
    } else {
      cout << a.second << " " << b.second << endl; // Output the two participants forming the team
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/