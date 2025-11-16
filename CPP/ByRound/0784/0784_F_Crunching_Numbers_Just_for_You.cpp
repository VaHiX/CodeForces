// Problem: CF 784 F - Crunching Numbers Just for You
// https://codeforces.com/contest/784/problem/F

/*
 * Algorithm: Sorting an array of integers in non-descending order
 * Techniques: Standard library sort function (typically implemented as introsort - hybrid of quicksort, heapsort and insertion sort)
 * 
 * Time Complexity: O(n log n) where n is the size of the array
 * Space Complexity: O(1) - sorting is done in-place, only using a constant amount of extra memory
 * 
 * The code reads an array of integers, sorts them in ascending order using std::sort,
 * and outputs the sorted array elements separated by spaces.
 */

#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long l;
l n, a[15], b[2000];
int main() {
  cin >> n;  // Read the size of the array
  while (clock() / CLOCKS_PER_SEC <= 1.00)  // Busy waiting loop (likely for timing purposes, but not necessary for functionality)
    ;
  for (int i = 1; i <= n; i++)  // Read all elements of the array
    cin >> a[i];
  sort(a + 1, a + 1 + n);  // Sort the array from index 1 to n (using 1-based indexing)
  for (int i = 1; i <= n; i++)  // Output the sorted array elements
    cout << a[i] << ' ';
  return 0;
}


// https://github.com/VaHiX/CodeForces/