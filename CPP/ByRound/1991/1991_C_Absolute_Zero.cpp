// Problem: CF 1991 C - Absolute Zero
// https://codeforces.com/contest/1991/problem/C

/*
Algorithm/Technique: Bit manipulation, Greedy
Time Complexity: O(n + 30) = O(n) where n is the size of array
Space Complexity: O(1) excluding the output array

This problem asks us to reduce all elements of an array to 0 using at most 40 operations,
where each operation replaces each element ai with |ai - x| for some chosen x.

The key insight is that if we have both odd and even numbers in the array, it's impossible
to make all elements 0 because the operations preserve parity (odd numbers stay odd, even stay even).
Otherwise, we can use bit manipulation to systematically zero out all elements.

The approach:
1. Check if there are both odd and even numbers. If so, return -1.
2. For the case where all numbers have the same parity:
   - Generate operations using powers of 2 from 2^29 down to 2^0
   - If all numbers are even, add one final operation with x=1 (this will make all elements 0)
   - If all numbers are odd, we don't need the extra operation because the powers of 2
     operations will reduce them to 0 directly

This works because for any number, applying operations using powers of 2 effectively
decomposes the number into its binary representation, allowing us to gradually reduce it to 0.
*/

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define nl "\n"
#define spc " "
#define INF_INT 2e9
#define INF_LL 2e18
#define matmax 25
#define mod 1000000007
#define mp make_pair
#define pb push_back
#define pi pair<int, int>
#define pip pair<int, pi>
#define pl pair<ll, ll>
#define plp pair<ll, pl>
#define vi vector<int>
#define vl vector<ll>
#define all(x) x.begin(), x.end()
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(q) (int)(q.size())
using namespace std;
typedef long long int ll;
typedef long int li;
typedef double ld;
#define for0(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i < (int)(n); ++i)
#define fo(a, b) for (auto i = a; i < b; ++i)
#define nfo(a, b) for (auto i = a; i >= b; --i)
#define jfo(a, b) for (auto j = a; j < b; ++j)
#define njfo(a, b) for (auto j = a; j >= b; --j)
#define tt                                                                     \
  ll t;                                                                        \
  cin >> t;                                                                    \
  while (t--)
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl
#define Yes cout << "Yes" << nl
#define No cout << "No" << nl
void swap(ll &x, ll &y) {
  ll temp = y;
  y = x;
  x = temp;
}
ll powa(ll a, ll b, ll m = mod) {
  if (b == 0)
    return 1ll;
  else if (b == 1)
    return a;
  else {
    ll x = powa(a, b / 2, m);
    x *= x;
    if (b % 2) {
      x *= a;
    }
    return x;
  }
}
int ReverseNum(int n) {
  int reverse = 0;
  while (n != 0) {
    int digit = n % 10;
    reverse = reverse * 10 + digit;
    n /= 10;
  }
  return reverse;
}
int findGcd(int a, int b) {
  while (a > 0 && b > 0) {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }
  if (a == 0) {
    return b;
  }
  return a;
}
int sum(int k) {
  int ans = 0;
  while (k) {
    ans += k % 10;
    k /= 10;
  }
  return ans;
}
bool isPrime(int num) {
  if (num <= 1)
    return false;
  if (num == 2 || num == 3)
    return true;
  if (num % 2 == 0 || num % 3 == 0)
    return false;
  for (int i = 5; i * i <= num; i += 6) {
    if (num % i == 0 || num % (i + 2) == 0)
      return false;
  }
  return true;
}
void leftrotate(string &s, ll d) {
  reverse(s.begin(), s.begin() + d);
  reverse(s.begin() + d, s.end());
  reverse(s.begin(), s.end());
}
void rightrotate(string &s, ll d) { leftrotate(s, s.length() - d); }
void solve() {
  int n;
  cin >> n;
  vi a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  bool has_odd = false, has_even = false;
  for (int i = 0; i < n; i++)
    if (a[i] % 2 == 1)
      has_odd = true;
    else
      has_even = true;
  if (has_even && has_odd)
    cout << -1 << nl;
  else {
    vi operations;
    for (int i = 29; i >= 0; i--)
      operations.push_back(1 << i);
    if (has_even)
      operations.push_back(1);
    cout << operations.size() << nl;
    for (int x : operations)
      cout << x << ' ';
    cout << nl;
  }
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/