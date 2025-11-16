// Problem: CF 1186 D - Vus the Cossack and Numbers
// https://codeforces.com/contest/1186/problem/D

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<double> a(n);
  std::vector<ll> b(n);
  ll sum(0);
  for (ll p = 0; p < n; p++) {
    scanf("%lf", &a[p]);
    b[p] = a[p]; // Initialize b[i] to the floor of a[i]
    if (b[p] > a[p]) {
      --b[p]; // Adjust to ceiling if needed
    }
    sum += b[p]; // Accumulate the sum of floor values
  }
  for (ll p = 0; p < n; p++) {
    if (a[p] <= b[p]) {
      continue; // If a[i] is already less than or equal to b[i], no adjustment needed
    } else if (sum < 0) {
      ++b[p]; // If sum is negative, increase b[i] to adjust the total sum
      ++sum;  // Update the sum
    } else {
      break;  // If sum is non-negative, stop since we're balancing towards zero
    }
  }
  for (ll p = 0; p < n; p++) {
    printf("%lld\n", b[p]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/