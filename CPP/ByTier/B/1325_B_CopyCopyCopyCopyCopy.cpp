// Problem: CF 1325 B - CopyCopyCopyCopyCopy
// https://codeforces.com/contest/1325/problem/B

/*
B. CopyCopyCopyCopyCopy
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task: Given an array of length n, create a new array by concatenating it n times.
Find the length of the longest increasing subsequence (LIS) in this new array.

Algorithms/Techniques:
- Use a set to store unique elements from the original array.
- The LIS of the repeated array is equal to the number of unique elements in the original array,
  because each unique element can contribute once to the increasing subsequence.
- This works because after repeating the array n times, we can still only pick one instance
  of each unique value for the LIS.

Time Complexity: O(n log n) per test case due to set insertion operations.
Space Complexity: O(n) for storing elements in the set.

*/
#include <cstdio>
#include <set>
std::set<int> s; // Set to store unique elements
int main() {
  int T;
  scanf("%d", &T); // Read number of test cases
  while (T--) {
    int n, x;
    scanf("%d", &n); // Read array length
    while (n--) // Read all elements of the array
      scanf("%d", &x), s.insert(x); // Insert element into set
    printf("%d\n", s.size()); // Print number of unique elements (LIS length)
    s.clear(); // Clear the set for next test case
  }
}


// https://github.com/VaHiX/codeForces/