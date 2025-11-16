// Problem: CF 1945 B - Fireworks
// https://codeforces.com/contest/1945/problem/B

/*
B. Fireworks
time limit per test1 second
memory limit per test256 megabytes

Algorithm/Techniques: Mathematical analysis to compute maximum overlapping fireworks.
Time Complexity: O(t), where t is the number of test cases. Each test case is processed in constant time.
Space Complexity: O(1). Only a few variables are used regardless of input size.

The problem asks for the maximum number of fireworks visible at the same time.
Each firework from installation 1 (launching every 'a' minutes) is visible for (m+1) minutes,
and similarly for installation 2 (launching every 'b' minutes).

We calculate how many fireworks from each installation are visible in the interval [0, L],
where L is the least common multiple of a and b.
Then we compute the total number as:
  - Number of fireworks from first installation: (m + a) / a
  - Number of fireworks from second installation: (m + b) / b
This ensures that all overlaps are counted correctly without needing to simulate them.

Input:
Each test case contains integers a, b, m.
Output:
Maximum number of fireworks visible at the same time.

Example:
For a=6, b=7, m=4:
First installation launches at: 0, 6, 12, 18, ...
Second installation launches at: 0, 7, 14, 21, ...
Fireworks are visible for 5 minutes.
At time 7 (after first installation), one firework from each is visible => answer = 2
*/
#include <cstdio>
typedef long long ll;

int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll a, b, m; // frequencies and visibility time
    scanf("%lld %lld %lld", &a, &b, &m);
    // Calculate fireworks from each installation that can be seen at the same time
    printf("%lld\n", (m + a) / a + (m + b) / b); // Total maximum fireworks visible simultaneously
  }
}


// https://github.com/VaHiX/codeForces/