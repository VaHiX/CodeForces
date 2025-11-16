// Problem: CF 1201 C - Maximum Median
// https://codeforces.com/contest/1201/problem/C

/*
C. Maximum Median
 Algorithms/Techniques: Binary search on the answer + greedy approach
 Time Complexity: O(n * log(max_value))
 Space Complexity: O(1)

The problem asks to maximize the median of an array after at most k operations,
where each operation increases an element by 1.
We use binary search on the possible median value and for each candidate,
we check if it's achievable with at most k operations using a greedy approach.

The array is sorted first. Then, we try to make the median as large as possible
by increasing elements from the right side of the sorted array (towards the median),
while ensuring that we stay within k operations.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  long long n, k, i, sum;
  cin >> n >> k;
  long long a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n); // Sort the array to find median easily
  sum = a[n / 2]; // Start with current median value
  i = 1;
  while (i <= n / 2) {
    // Check if we have enough operations to increase the median further
    if (k < (a[n / 2 + i] * i - sum))
      break;
    sum += a[n / 2 + i]; // Add new element to the sum
    i++; // Move to next element
  }
  cout << (k + sum) / i; // Final result based on operations and current sum
  return 0;
}


// https://github.com/VaHiX/codeForces/