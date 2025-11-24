// Problem: CF 1079 A - Kitchen Utensils
// https://codeforces.com/contest/1079/problem/A

/*
Problem: Minimum Stolen Utensils
Algorithm/Techniques: Greedy, Counting
Time Complexity: O(n)
Space Complexity: O(1)

The problem involves determining the minimum number of utensils stolen 
based on the remaining utensils and the number of guests. The key insight is:
- Each guest must receive a complete set of utensils (same types, but not necessarily all present)
- For each type of utensil, we compute how many full sets it can contribute to
- We use a greedy approach: find the maximum count of a single utensil type, 
  then calculate minimum total utensils needed and subtract remaining.

The solution:
1. Count frequency of each utensil type.
2. Find maximum frequency among all types.
3. Calculate number of complete sets required (ceil(max_freq / k)).
4. Compute total utensils needed = sets * k * unique_types.
5. Result = total_needed - remaining_utensils.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int a[110]; // Array to store count of each utensil type
int t, n, k, i, x, res = 0, mx = 0; // Variables for computation
int main() {
  cin >> n >> k; // Read number of remaining utensils and guests
  for (i = 1; i <= n; i++) { // Process each remaining utensil
    cin >> x;
    if (!a[x]) // If this utensil type hasn't been seen before
      res++; // Increment unique types counter
    a[x]++; // Increment count for this utensil type
    mx = max(mx, a[x]); // Update maximum frequency
  }
  t = mx / k; // Calculate how many full sets can be formed from the most frequent type
  if (mx % k) // If there's remainder, we need one more set
    t++;
  cout << t * res * k - n << endl; // Output minimum stolen utensils
}


// https://github.com/VaHiX/codeForces/