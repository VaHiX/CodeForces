// Problem: CF 521 A - DNA Alignment
// https://codeforces.com/contest/521/problem/A

/*
 * Code Purpose: This program computes the number of DNA strings t of length n 
 * such that the Vasya distance ρ(s, t) is maximized, where s is a given DNA string.
 * 
 * Algorithm: 
 * 1. Count frequency of each nucleotide ('A', 'C', 'G', 'T') in input string s.
 * 2. Find the maximum frequency among the nucleotides.
 * 3. Count how many nucleotides have this maximum frequency.
 * 4. The result is (number of max frequency nucleotides) ^ n mod (10^9 + 7),
 *    because for each position in the string t, we can choose any of the nucleotides 
 *    that occur most frequently to maximize h(s, t) for all rotations.
 * 
 * Time Complexity: O(n) - We iterate through the string once to count frequencies, 
 *                      and then iterate over fixed-size ACGT characters.
 * Space Complexity: O(1) - We use only a fixed-size array of size 256 for character counts.
 */

#include <stddef.h>
#include <iostream>
#include <string>

#define lli long long
#define x first
#define y second
#define maxi(a, b) a = max(a, b)
#define mize(a, b) a = min(a, b)
#define getbit(a, i) ((a) >> (i) & 1)
#define FOR(i, a, b) for (int i = a, _n = b; i <= _n; ++i)
#define FORD(i, a, b) for (int i = a, _n = b; i >= _n; --i)
#define REP(i, _n) for (int i = 0; i < _n; ++i)
#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define pb push_back
#define mp make_pair
using namespace std;
int n;
string s, ACGT = "ACGT";
int cnt[256];
const int MOD = 1e9 + 7;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> n;
  cin >> s;
  REP(i, n) cnt[s[i]] += 1;
  int ma = 0, ans = 0;
  for (char &c : ACGT)
    if (cnt[c] >= ma) {
      if (cnt[c] > ma)
        ma = cnt[c], ans = 1;
      else
        ans += 1;
    }
  lli res = 1;
  REP(i, n) res = (res * ans) % MOD;
  cout << res;
}


// https://github.com/VaHiX/CodeForces/