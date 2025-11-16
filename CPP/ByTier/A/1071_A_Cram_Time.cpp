// Problem: CF 1071 A - Cram Time
// https://codeforces.com/contest/1071/problem/A

/*
Algorithm: Greedy approach to maximize the number of lecture notes read.
Steps:
1. For each day, determine the maximum number of notes that can be read.
   - Notes take 1, 2, 3, ..., k hours respectively.
   - So if we read notes 1, 2, ..., k, total time = 1 + 2 + ... + k = k*(k+1)/2.
   - Find the largest k such that k*(k+1)/2 <= available hours.
2. For the first day:
   - Compute maximum notes (n) as above.
   - Output the note numbers (1 to n-1) excluding the one that causes leftover hours.
3. For the second day:
   - Adjust the leftover hours to be used in second day (if any).
   - Use another greedy pass to determine the maximum notes readable in second day.

Time Complexity: O(sqrt(a) + sqrt(b)) - since we compute sum of arithmetic series.
Space Complexity: O(1) - only a few variables used, no extra space for arrays.
*/

#include <iostream>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int a, b;
  cin >> a >> b;
  int n = 0, k = 1;
  // Greedily calculate maximum number of notes for first day
  while (a > 0) {
    a -= k++;  // subtract time needed to read note k
    ++n;       // increment count of notes
  }
  // If there's leftover time, adjust the count
  if (a != 0) {
    --n;
    a = -a;   // 'a' holds the leftover time now
  }
  cout << n << '\n';
  for (int i = 1; i < k; i++)
    if (i != a)   // skip the note that caused the overflow
      cout << i << ' ';
  cout << '\n';
  n = 0;
  int tmp = k;   // store the starting point for second day
  if (b < a) {   // if second day doesn't have enough time for leftover of first
    cout << "0\n";
    return 0;
  }
  if (a != 0) {
    b -= a;   // subtract leftover from second day
    ++n;
  }
  // Greedily compute maximum notes for second day
  while (b > 0) {
    b -= k;
    ++k;
    ++n;
  }
  // Adjust if there's a leftover in second day
  if (b != 0) {
    --k;
    --n;
  }
  cout << n << '\n';
  if (a != 0)
    cout << a << ' ';   // print the note that caused overflow in first day
  for (int i = tmp; i < k; i++)
    cout << i << ' ';   // print all the rest notes for second day
  cout << '\n';
}


// https://github.com/VaHiX/CodeForces/