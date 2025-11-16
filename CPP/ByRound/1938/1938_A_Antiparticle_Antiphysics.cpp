// Problem: CF 1938 A - Antiparticle Antiphysics
// https://codeforces.com/contest/1938/problem/A

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define fi first
#define se second
#define pb push_back
const int N = 1e5 + 5;
char S[N], E[N];
int n, m, i, j, a, p, T, s1, s2, e1, e2;
vector<pair<string, int>> ans;

/*
 * Adds a new particle around the specified index.
 * For proton (P): inserts APA around it (Operation 1).
 * For antiproton (A): inserts PAP around it (Operation 2).
 * Time Complexity: O(n) where n is current string length.
 * Space Complexity: O(1) additional space.
 */
void add(int x) {
  int len = strlen(S);
  if (S[x] == 'A') {
    ans.pb({"+A", x + 1});
    while (len > x)
      S[len + 2] = S[len], --len;
    S[x] = S[x + 2] = 'P', S[x + 1] = 'A';
  } else {
    ans.pb({"+P", x + 1});
    while (len > x)
      S[len + 2] = S[len], --len;
    S[x] = S[x + 2] = 'A', S[x + 1] = 'P';
  }
}

/*
 * Removes contiguous particles from the specified index.
 * For antiproton (A): removes 'a' consecutive antiprotons (Operation 3).
 * For proton (P): removes 'p' consecutive protons (Operation 4).
 * Time Complexity: O(n) where n is current string length.
 * Space Complexity: O(1) additional space.
 */
void sub(int x) {
  int len = strlen(S);
  if (S[x] == 'A') {
    ans.pb({"-A", x + 1});
    while (x + a <= len)
      S[x] = S[x + a], ++x;
  } else {
    ans.pb({"-P", x + 1});
    while (x + p <= len)
      S[x] = S[x + p], ++x;
  }
}

/*
 * Checks if transformation is possible and performs transformation.
 * Uses rules derived from invariants to ensure valid transformation.
 * Uses greedy method for operations.
 * Time Complexity: O(n^2) due to checking for inversions and nested loops.
 * Space Complexity: O(1) additional space, not counting output.
 */
bool Wrk() {
  s1 = s2 = e1 = e2 = 0;
  for (i = 0; i < n; i++)
    S[i] == 'A' ? ++s1 : ++s2;
  for (i = 0; i < m; i++)
    E[i] == 'A' ? ++e1 : ++e2;
  if (!(a % 2) && (s1 - e1) & 1)
    return false;
  if (!(p % 2) && (s2 - e2) & 1)
    return false;
  if (!(a % 4) && !(p % 4)) {
    int cnt = 0;
    for (i = 0; i < n; i++)
      for (j = i + 1; j < n; j++)
        cnt += (S[i] == 'P' && S[j] == 'A');
    for (i = 0; i < m; i++)
      for (j = i + 1; j < m; j++)
        cnt += (E[i] == 'P' && E[j] == 'A');
    if ((cnt + (s1 - e1) / 2 + (s2 - e2) / 2) & 1)
      return false;
  }
  for (i = 0; i < m; i++)
    if (S[i] != E[i]) {
      if (S[i] != 0)
        add(i);
      else
        add(i - 1), add(i - 1), --i;
    }
  n = strlen(S), s1 = s2 = 0;
  for (i = m; i < n; i++)
    S[i] == 'A' ? ++s1 : ++s2;
  if (s1 || s2) {
    if (!s1 || !s2)
      add(m), (!s1) ? s1 = 2 : s2 = 2;
    if (a % 4) {
      for (i = m;; i++)
        if (S[i] == 'A')
          break;
      while (s2 % p)
        add(i), ++i, s2 += 2;
      for (i = m; S[i]; i++)
        if (S[i] == 'A') {
          j = i;
          while (S[j] == 'A')
            ++j;
          if (S[j] == 0)
            break;
          while ((j - i) % a)
            add(j), ++j;
          while (j - i > 0)
            sub(i), j -= a;
        }
      if (S[i] == 'A') {
        while (j - i >= a)
          sub(i), j -= a;
        while ((j - i) % 4) {
          for (int k = 0; k < a; k++)
            add(i - 1 + k);
          sub(i - 1), j += a;
        }
        for (int t = 0; t < (j - i) / 4; t++) {
          for (int k = 0; k < p - 1; k++)
            add(i + 2 * t + k);
          sub(i + 2 * t - 1), add(i + 2 * t + p - 1), sub(i + 2 * t);
        }
        j = i - 1 + (j - i) / 2, --i;
        while ((j - i) % a)
          add(j), ++j;
        while (j - i >= a)
          sub(j + 1), sub(i), j -= a;
      }
      while (s2)
        sub(m), s2 -= p;
    } else {
      for (i = m;; i++)
        if (S[i] == 'P')
          break;
      while (s1 % a)
        add(i), ++i, s1 += 2;
      for (i = m; S[i]; i++)
        if (S[i] == 'P') {
          j = i;
          while (S[j] == 'P')
            ++j;
          if (S[j] == 0)
            break;
          while ((j - i) % p)
            add(j), ++j;
          while (j - i > 0)
            sub(i), j -= p;
        }
      if (S[i] == 'P') {
        while (j - i >= p)
          sub(i), j -= p;
        while ((j - i) % 4) {
          for (int k = 0; k < p; k++)
            add(i - 1 + k);
          sub(i - 1), j += p;
        }
        for (int t = 0; t < (j - i) / 4; t++) {
          for (int k = 0; k < a - 1; k++)
            add(i + 2 * t + k);
          sub(i + 2 * t - 1), add(i + 2 * t + a - 1), sub(i + 2 * t);
        }
        j = i - 1 + (j - i) / 2, --i;
        while ((j - i) % p)
          add(j), ++j;
        while (j - i >= p)
          sub(j + 1), sub(i), j -= p;
      }
      while (s1)
        sub(m), s1 -= a;
    }
  }
  return true;
}

/*
 * Driver solution for a test case.
 * Parses input and calls Wrk() to perform transformation.
 * Time Complexity: Depends on call to Wrk, overall O(n^2).
 * Space Complexity: O(n) for storing output operations.
 */
void sol() {
  scanf("%d%d%s%s", &a, &p, S, E);
  n = strlen(S), m = strlen(E);
  ans.clear();
  if (!Wrk())
    return puts("-1"), void();
  printf("%d\n", (int)ans.size());
  for (auto i : ans)
    cout << i.fi << ' ' << i.se << '\n';
}

/*
 * Main function to process all test cases.
 * Time Complexity: O(T * n^2) where T is number of test cases.
 * Space Complexity: O(1) for variables excluding input/output.
 */
int main() {
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/