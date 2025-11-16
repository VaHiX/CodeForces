// Problem: CF 817 C - Really Big Numbers
// https://codeforces.com/contest/817/problem/C

/*
 * Problem: C. Really Big Numbers
 * 
 * Algorithm: Binary Search on Answer
 * 
 * Approach:
 * - We want to count how many numbers x in [1, n] satisfy: x - digitSum(x) >= s
 * - This can be rewritten as: digitSum(x) <= x - s
 * - To efficiently find the count, we use binary search to find the smallest number
 *   that satisfies the condition. Then the answer is n - smallest + 1.
 * 
 * Time Complexity: O(log n * log n), where log n is due to binary search and
 *                  the digit sum calculation for each check.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
typedef long long ll;

// Function to check if a number x is "really big" with respect to s
// A number x is really big if x - digitSum(x) >= s
bool check(ll x, ll s) {
  ll y(x), digitSum(0);
  while (y > 0) {
    digitSum += y % 10;  // Add the last digit to the sum
    y /= 10;             // Remove the last digit
  }
  if (digitSum + s <= x) {  // Check if the condition is met
    return true;
  }
  return false;
}

int main() {
  ll n, s;
  scanf("%lld %lld", &n, &s);
  ll left(0), right(n), smallest(n + 1);  // Binary search bounds and result tracker

  // Binary search for the smallest "really big" number
  while (left <= right) {
    ll mid = (left + right) / 2;
    if (check(mid, s)) {
      smallest = mid;      // Found a valid number, try to find smaller
      right = mid - 1;
    } else {
      left = mid + 1;      // Not valid, search higher
    }
  }

  // Output the count of really big numbers from smallest to n
  printf("%lld\n", n - smallest + 1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/