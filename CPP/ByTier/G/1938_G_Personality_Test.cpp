// Problem: CF 1938 G - Personality Test
// https://codeforces.com/contest/1938/problem/G

/*
 * Problem: Personality Test
 * 
 * Purpose:
 *   Find a pair of students (a, b) such that a < b and they are similar. Two students are similar 
 *   if they answered at least k questions with the same answer. If multiple such pairs exist, 
 *   choose the one with the smallest b. If there are still multiple, choose the one with the largest a.
 * 
 * Algorithm:
 *   - For each student, maintain a data structure to track which other students answered the same 
 *     questions with the same answer.
 *   - For each new student, count how many previous students answered the same questions with the same answers.
 *   - If the count meets the threshold k, output the pair.
 * 
 * Time Complexity: O(n^2 * m) in worst case, but optimized with early termination.
 * Space Complexity: O(n * m) for storing the student answers and auxiliary structures.
 */

#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define ll long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define f first
#define s second
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define For(i, a) FOR(i, 0, a)
#define trav(a, b) for (auto &a : b)
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define vb vector<bool>
#define vl vector<ll>
#define ins insert
#define bk back()
#define sz(x) (int)x.size()
int n, m, k;
vi a[3005][26]; // Store indices of students who answered each question with each letter (A-Z)
vector<string> tmp; // Store all the student answers for reference

// Function to find the earliest previous student similar to current student S
int go(int x, string S) {
  vi zz(x + 1, 0); // Count how many questions each previous student matches with S
  For(j, m) if (S[j] != '.') { // For each answered question
    For(i, x) if (tmp[i][j] == S[j]) { zz[i]++; } // Count matching answers
  }
  int lst = -1;
  For(i, x) if (zz[i] >= k) { lst = i; } // Find the first similar student
  if (lst == -1)
    assert(false); // Should not happen if solution exists
  return lst;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  if (fopen("input.in", "r")) {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
  }
  cin >> n >> m >> k;
  For(i, n) {
    string S;
    cin >> S;
    int szs = 0;
    For(j, m) {
      if (S[j] == '.') {
        continue; // Skip unanswered questions
      }
      int x = S[j] - 'A'; // Convert letter to index
      szs += sz(a[j][x]); // Track total entries for optimization check
      a[j][x].pb(i); // Add current student to list of those answering this question with this letter
    }
    // Optimization check: if number of matches is too high, calculate early
    if (szs >= 5 * m * (i + 1)) {
      cout << go(i, S) + 1 << " " << i + 1 << endl;
      return 0;
    }
    vi v(i + 1, 0); // v[j] = count of questions student j matches with current student
    For(j, m) if (S[j] != '.') {
      int x = S[j] - 'A'; // Question with answer letter
      trav(y, a[j][x]) if (y != i) { v[y]++; } // For each student who answered same question with same letter
    }
    int lst = -1;
    For(j, i) if (v[j] >= k) { lst = j; } // Find a previous student matching at least k questions
    if (lst != -1) {
      cout << lst + 1 << " " << i + 1 << endl; // Output result (1-indexed)
      return 0;
    }
    tmp.pb(S); // Store current student's answer
  }
  cout << -1 << endl; // No similar pair found
}


// https://github.com/VaHiX/CodeForces/