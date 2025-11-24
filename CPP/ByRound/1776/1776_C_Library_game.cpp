// Problem: CF 1776 C - Library game
// https://codeforces.com/contest/1776/problem/C

/*
 * Problem: Library game
 * 
 * Algorithm:
 * - Determine whether Alessia or Bernardo should win based on game theory:
 *   - If there exists a subject such that at least (m/i + 1) passes of length i are available,
 *     then Bernardo can guarantee a match. Otherwise, Alessia can guarantee distinct subjects.
 * - The strategy for each player:
 *   - If playing as Alessia: Choose passes to cover all distinct sections to avoid repetition.
 *   - If playing as Bernardo: Try to find a section that was already chosen in the same subject.
 * 
 * Time Complexity: O(n log n + m^2)
 * Space Complexity: O(m)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> x(n);
  vector<int> a(m + 1);
  for (int i = 0; i < n; ++i)
    cin >> x[i];
  for (int i = 0; i < n; ++i)
    a[x[i]]++; // Count frequency of each pass length
  sort(x.begin(), x.end());
  reverse(x.begin(), x.end()); // Sort pass lengths in descending order
  int s = 0;
  int winL = 0;
  // Find the largest length i such that at least (m/i + 1) passes of length i are available
  for (int i = m; i >= 1; --i) {
    s += a[i];
    int Lx = m / i;
    if (s >= Lx + 1) {
      winL = i;
      break;
    }
  }
  if (winL) {
    // Bernardo wins
    cout << "Bernardo\n" << flush;
    vector<int> taken(m + 1);
    for (int h = 0; h < n; ++h) {
      int y, A;
      cin >> y >> A; // Read pass length and interval start
      int q = 0;
      // Try to select a section that's already taken in this subject
      for (int i = A; i <= y + A - 1; ++i) {
        if (taken[i]) {
          cout << i << '\n';
          q = 1;
          break;
        }
      }
      if (q == 0) {
        // If no previously selected section, select one based on modulus
        for (int i = A; i <= y + A - 1; ++i) {
          if (i % winL == 0) {
            cout << i << '\n';
            taken[i] = 1;
            q = 1;
            break;
          }
        }
      }
      if (q == 0) {
        // If all else fails, take the first section
        cout << A << '\n';
        taken[A] = 1;
        q = 1;
      }
      cout << flush;
    }
  } else {
    // Alessia wins
    cout << "Alessia\n";
    vector<int> taken(m + 1);
    for (int h = 0; h < n; ++h) {
      int y = x[h]; // Pick pass length
      // Find a valid interval that doesn't include any taken sections
      for (int i = 1; i <= m - y + 1; ++i) {
        bool ok = 1;
        for (int j = i; j <= i + y - 1; ++j) {
          if (taken[j]) {
            ok = 0;
            i = j; // Skip to next potential start
            break;
          }
        }
        if (ok) {
          cout << y << ' ' << i << '\n' << flush;
          break;
        }
      }
      int b;
      cin >> b; // Read Bernardo's choice
      taken[b] = 1; // Mark as taken
    }
  }
}


// https://github.com/VaHiX/CodeForces/