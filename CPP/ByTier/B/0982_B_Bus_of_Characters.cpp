/*
 * Problem URL : https://codeforces.com/contest/982/problem/B
 * Submit Date : 2025-09-12
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int main() {

  std::ios_base::sync_with_stdio(false);

  long n;
  std::cin >> n;
  std::vector<std::pair<long, long>> w(n);
  for (long p = 0; p < n; p++) {
    std::cin >> w[p].first;
    w[p].second = p;
  }
  sort(w.begin(), w.end());

  std::string s;
  std::cin >> s;
  std::stack<long> st;
  long ind(0);

  for (long p = 0; p < 2 * n; p++) {
    if (s[p] == '0') {
      std::cout << (w[ind].second + 1) << " ";
      st.push(ind);
      ++ind;
    } else if (s[p] == '1') {
      long u = st.top();
      st.pop();
      std::cout << (w[u].second + 1) << " ";
    }
  }

  puts("");

  return 0;
}
