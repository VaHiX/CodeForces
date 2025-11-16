// Problem: CF 936 A - Save Energy!
// https://codeforces.com/contest/936/problem/A

/*
 * Problem: A. Save Energy!
 * 
 * Algorithm/Technique:
 * This problem involves simulating the cooking process of a chicken with a stove that turns off after k minutes,
 * and Julia turning it back on every d minutes. The chicken cooks at different rates depending on whether the stove
 * is on or off. We need to compute total time required to cook the chicken.
 * 
 * The key insight is to model one full cycle of stove on/off, then simulate partial cycles to calculate total time.
 * 
 * Time Complexity: O(1) - Constant time operations
 * Space Complexity: O(1) - Only using a few variables
 */

#include <cstdio>
typedef long long ll;
int main() {
  ll k, d;
  double t;
  scanf("%lld %lld %lf", &k, &d, &t);
  if (d < k) {
    // Adjust d to be at least k, so that Julia can turn on the stove before it turns off
    ll u = (k + d - 1) / d;
    d *= u;
  }
  // Calculate effective cooking speed per cycle: k minutes at full speed + (d-k) minutes at half speed
  double sp = k + 0.5 * (d - k);
  // Determine how many complete cycles are needed to cook the chicken
  ll periods = t / sp;
  // Initial time is d * number of complete cycles
  double res = d * periods;
  // Remaining cooking time after complete cycles
  t -= periods * sp;
  // If remaining time is less than k, the stove is on for that time
  if (t < k) {
    res += t;
  } else if (t <= sp) {
    // The stove is on for k minutes, and then off for the rest of the time at half speed,
    // which is equivalent to 2*(t-k) additional time for cooking
    res += k + 2 * (t - k);
  }
  printf("%.1lf\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/