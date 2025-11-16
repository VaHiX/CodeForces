// Problem: CF 871 A - Maximum splitting
// https://codeforces.com/contest/871/problem/A

// Problem: Maximum splitting into composite numbers
// Algorithm: 
// - Composite numbers are integers > 1 that are not prime
// - We want to split a number n into the maximum number of composite summands
// - All composite numbers >= 4 can be written as sum of 4s and 6s (since 4 = 2*2, 6 = 2*3, 8 = 2*2*2, etc.)
// - Key observations:
//   - If n < 4, impossible to split (no composite number < 4)
//   - If n is divisible by 4, maximum number of summands = n/4
//   - If n % 4 == 1 or n % 4 == 3, we can use one 9 (or 6+3, but 3 is not composite) and rest in 4s
//     - So we subtract 1 to get 4s (since we need at least 1 composite number in the form of 4 or 6 + others)
//   - If n is even and not divisible by 4, we use 6 and rest in 4s (but we need to ensure each summand is composite)
// - This approach works because minimal composite numbers are 4, 6, 8, 9, ...
// Time Complexity: O(q), where q is number of queries
// Space Complexity: O(1)

#include <iostream>
#include <utility>

#define bupol __builtin_popcount
#define ll long long
#define fi first
#define se second
#define pb push_back
using namespace std;
const ll MAXN = 2e5 + 10;
const int MAXS = 1e6 + 10;
const int INF = 1e9 + 10;
const ll MOD = 998244353;
const ll LOG = 30;
typedef pair<int, int> pii;
typedef pair<pii, ll> ipii;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    // If n is less than 4 or is a prime number <= 11 (since primes like 2, 3, 5, 7, 11 are less than 4)
    if (n == 1 || n == 2 || n == 3 || n == 5 || n == 7 || n == 11)
      cout << -1;
    // If n % 4 == 1 or n % 4 == 3, we can express using n/4 - 1 parts of 4 and one 9
    else if (n % 4 == 1 || n % 4 == 3)
      cout << n / 4 - 1;
    else
      cout << n / 4;
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/