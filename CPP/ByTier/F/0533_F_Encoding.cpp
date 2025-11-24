// Problem: CF 533 F - Encoding
// https://codeforces.com/contest/533/problem/F

/*
Purpose: This code finds all starting positions in string S where a substring of length |T| can be encoded to form string T using a pairing of letters.
Algorithms/Techniques: Rolling hash technique with precomputed hashes for efficient substring comparisons and a mapping of characters in T to their positions. The algorithm checks for valid encodings by comparing rolling hash values of characters in S and T.
Time Complexity: O(n + m) where n is the length of S and m is the length of T.
Space Complexity: O(n + m) for storing hashes and auxiliary arrays.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 10, C = 27, B = 273;
unsigned long long H[C], cnt[C], RH[C], tv[MAXN], A[MAXN];
int faq[C], n, m, ans;
vector<int> res;
string s, t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> s >> t;
  tv[0] = 1;
  A[0] = 1;
  // Precompute powers of base B for rolling hash
  for (int i = 1; i < MAXN; i++)
    tv[i] = tv[i - 1] * B;
  for (int i = 1; i < MAXN; i++)
    A[i] = A[i - 1] * B + 1;
  // Initialize frequency array
  for (int i = 0; i < C; i++)
    faq[i] = -1;
  // Process string T to record positions of characters
  for (int i = 0; i < m; i++) {
    faq[t[i] - 'a'] = max(faq[t[i] - 'a'], i);
    RH[t[i] - 'a'] *= B;
    RH[t[i] - 'a'] += i + 1;
  }
  // Process first m-1 characters of S
  for (int i = 0; i < m - 1; i++) {
    H[s[i] - 'a'] *= B;
    H[s[i] - 'a'] += i + 1;
    cnt[s[i] - 'a']++;
  }
  // Sliding window over S to check encodings
  for (int i = m - 1; i < n; i++) {
    // Remove character going out of window
    if (i - m >= 0) {
      for (int j = 0; j < C; j++)
        if (cnt[j] > 0)
          H[j] -= A[cnt[j] - 1];
      cnt[s[i - m] - 'a']--;
    }
    // Add new character entering window
    H[s[i] - 'a'] *= B;
    H[s[i] - 'a'] += m;
    cnt[s[i] - 'a']++;
    bool ok = true;
    // Check if current window matches encoding pattern
    for (int j = 0; j < C; j++) {
      if (faq[j] == -1)
        continue;
      char tm = s[i - m + 1 + faq[j]];
      if (H[tm - 'a'] != RH[j] || RH[tm - 'a'] != H[j])
        ok = false;
    }
    ans += ok;
    if (ok)
      res.push_back(i - m + 2);
  }
  cout << ans << endl;
  for (int i = 0; i < res.size(); i++)
    cout << res[i] << ' ';
}


// https://github.com/VaHiX/CodeForces/