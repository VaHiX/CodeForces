// Problem: CF 529 A - And Yet Another Bracket Sequence
// https://codeforces.com/contest/529/problem/A

/*
Algorithm: This solution attempts to find the lexicographically smallest correct
bracket sequence that can be formed from the given sequence using cyclic shifts
and additions. It uses suffix array and LCP (Longest Common Prefix) techniques
to efficiently compute optimal shifts.

Time Complexity: O(n log n) where n is the length of the input string due to
suffix array construction. Space Complexity: O(n) for storing the input, suffix
array, LCP array, and auxiliary arrays.
*/

#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <string.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORD(i, a, b) for (int i = (a); i > (b); i--)
#define PPC(x) __builtin_popcount(x)
#define MSB(x) (63 - __builtin_clzll(x))
#define SZ(x) ((int)(x).size())
#define HASK(S, x) (S.find(x) != S.end())
#define pb push_back
#define ALL(x) (x).begin(), (x).end()
#define ithBit(m, i) ((m) >> (i) & 1)
#define ft first
#define sd second
#define kw(a) ((a) * (a))

using namespace std;
template <typename T1, typename T2> inline void remin(T1 &a, T2 b) {
  a = min(a, (T1)b);
}
const int maxN = 1 << 21;
namespace SuffixArray {
int temp[maxN], inds[maxN], C[maxN], T[maxN * 4], *R, *P;
bool cmp(int i, int j) {
  while (P[i] == P[j])
    i++, j++;
  return P[i] < P[j];
}
void brut(int n, int *T, int *res) {
  iota(res, res + n, 0);
  P = T;
  sort(res, res + n, cmp);
}
int cntSort(int n, int *T, int k) {
  int m = 0;
  if (k == 0) {
    for (int i = 0; i < n; i += 3)
      temp[m++] = i;
    for (int i = 1; i < n; i += 3)
      temp[m++] = i;
  } else
    for (int i = 2; i < n; i += 3)
      temp[m++] = i;
  FORD(j, 2 - k, -1) {
    FOR(i, 0, m) {
      int ind = temp[i];
      int v = j & k ? R[ind + 1] : T[ind + j];
      C[v]++;
    }
    for (int i = 1; C[i - 1] != m; i++)
      C[i] += C[i - 1];
    FORD(i, m - 1, -1) {
      int ind = temp[i];
      int v = j & k ? R[ind + 1] : T[ind + j];
      inds[--C[v]] = ind;
    }
    fill(C, C + n + 1, 0);
    if (j != 0)
      copy(inds, inds + m, temp);
  }
  return m;
}
inline bool differ(int *T, int i, int j) {
  return T[i + 2] ^ T[j + 2] | T[i + 1] ^ T[j + 1] | T[i] ^ T[j];
}
inline int newInd(int i, int p) { return i / 3 + i % 3 * p; }
void calcRanks(int *sa, int n, int d = 0) { FOR(i, 0, n) R[sa[i]] = i + d; }
bool cmpMerge(int i, int j) {
  for (; true; i++, j++) {
    if (P[i] != P[j])
      return P[i] < P[j];
    if (i % 3 != 2 and j % 3 != 2)
      return R[i] < R[j];
  }
}
void ks(int n, int *T, int *res) {
  if (n < 6) {
    brut(n, T, res);
    return;
  }
  int m = cntSort(n, T, 0), p = (n + 2) / 3 + 1, ctr = 2;
  int *A = T + n + 2, *S = res + n / 3;
  A[p - 1] = 1, A[m + 1] = A[m + 2] = 0;
  FOR(i, 0, m) {
    if (i != 0 and differ(T, inds[i - 1], inds[i]))
      ctr++;
    A[newInd(inds[i], p)] = ctr;
  }
  ks(m + 1, A, S - 1);
  FOR(i, 0, m)
  S[i] = S[i] < p ? S[i] * 3 : (S[i] - p) * 3 + 1;
  calcRanks(S, m, 1);
  R[n] = 0;
  int k = cntSort(n, T, 1);
  P = T;
  merge(S, S + m, inds, inds + k, res, cmpMerge);
}
void run(char *Tin, int n, int *sa, int *lcp, int *ranks) {
  R = ranks;
  FOR(i, 0, n) T[i] = (int)Tin[i] + 1;
  T[n] = T[n + 1] = 0;
  n < 256 ? brut(n, T, sa) : ks(n, T, sa);
  calcRanks(sa, n);
  for (int i = 0, q = 0; i < n; i++) {
    if (R[i] == n - 1)
      continue;
    int j = sa[R[i] + 1];
    while (T[i + q] == T[j + q])
      q++;
    lcp[R[i]] = q;
    if (q != 0)
      q--;
  }
}
} // namespace SuffixArray
char T[maxN], S[maxN];
int sum[maxN], pref[maxN], suf[maxN];
int sa[maxN], R[maxN], lcp[maxN];
void solve() {
  scanf("%s", T + 1);
  int n = strlen(T + 1);
  FOR(i, 1, n + 1)
  sum[i] = sum[i - 1] + (T[i] == '(' ? 1 : -1);
  pref[0] = suf[n + 1] = maxN;
  FOR(i, 1, n + 1)
  pref[i] = min(pref[i - 1], sum[i]);
  FORD(i, n, -1)
  suf[i] = min(suf[i + 1], sum[i]);
  copy(T + 1, T + n + 1, S);
  copy(S, S + n, S + n);
  SuffixArray::run(S, n * 2, sa, lcp, R);
  pref[0] = 0;
  int opt = maxN * 3, ind = 0;
  FOR(i, 1, n + 1) {
    int mn = min(suf[i] - sum[i - 1], (sum[n] - sum[i - 1]) + pref[i - 1]);
    int prop = sum[n];
    if (mn < 0)
      prop -= mn * 2;
    if (opt > prop or (opt == prop and R[i - 1] < R[ind - 1]))
      opt = prop, ind = i;
  }
  int mn =
      min(suf[ind] - sum[ind - 1], (sum[n] - sum[ind - 1]) + pref[ind - 1]);
  FOR(_, 0, -mn)
  printf("(");
  printf("%s", T + ind);
  T[ind] = 0;
  printf("%s", T + 1);
  sum[n] -= min(mn, 0);
  FOR(_, 0, sum[n])
  printf(")");
  printf("\n");
}
int main() {
  int t = 1;
  FOR(tid, 1, t + 1) { solve(); }
  return 0;
}

// https://github.com/VaHiX/CodeForces/