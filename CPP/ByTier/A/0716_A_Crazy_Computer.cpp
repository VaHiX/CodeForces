// Problem: CF 716 A - Crazy Computer
// https://codeforces.com/contest/716/problem/A

/*
 * Problem: Crazy Computer
 * 
 * Purpose: Determine how many words remain on the screen after all n words are typed,
 *          considering that if the time gap between two consecutive words exceeds 'c',
 *          everything disappears.
 * 
 * Algorithm: 
 *   - Iterate through the array of word typing times.
 *   - For each pair of consecutive words, check if the time difference exceeds 'c'.
 *   - If yes, reset the count of words on screen to 0.
 *   - If no, increment the count.
 *   - Add 1 at the end because the last word is always counted.
 * 
 * Time Complexity: O(n) - Single pass through the array of n elements.
 * Space Complexity: O(n) - Storage for the array of n word times.
 * 
 * Techniques: Linear scan with conditional state update.
 */

#include <iostream>

using namespace std;
int main() {
  long long int i, j, k;
  long long int n, c, count = 0;
  cin >> n >> c;
  long long int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  for (i = 0; i < n - 1; i++) {
    if (a[i + 1] - a[i] > c)  // If time gap exceeds 'c', screen clears
      count = 0;
    else
      count++;  // Otherwise, we keep counting words
  }
  cout << count + 1;  // Add 1 for the last word that's always present
  return 0;
}


// https://github.com/VaHiX/CodeForces/