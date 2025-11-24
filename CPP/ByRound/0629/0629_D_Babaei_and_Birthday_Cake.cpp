// Problem: CF 629 D - Babaei and Birthday Cake
// https://codeforces.com/contest/629/problem/D

#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;
int main() {
  const double PI = 3.14159265358979;
  long n;
  scanf("%ld", &n);
  std::map<ll, ll> M;
  M[0] = 0;
  while (n--) {
    ll radius, height;
    scanf("%lld %lld", &radius, &height);
    ll prod = radius * radius * height;
    std::map<ll, ll>::iterator left, right;
    left = M.lower_bound(prod);
    right = left;
    ll cnt =
        (--right)->second + prod; // Get the maximum volume achievable before
                                  // this cake and add current cake volume
    right = left;
    while (right != M.end() && (right->second <= cnt)) {
      ++right;
    }
    M.erase(left, right); // Remove dominated entries
    M[prod] = cnt;        // Insert the new entry
  }
  printf("%.8lf\n", PI * (--M.end())->second);
  return 0;
}

// ### Algorithm/Technique:
// - **Dynamic Programming with Map-based Optimization**: The solution uses a
// map to maintain the maximum volume that can be achieved for a given cake
// volume (cylinder volume). For each cake, it determines the best previous cake
// that can support it using `lower_bound`, and then prunes any dominated
// entries in the map.

// ### Time Complexity:
// - O(n log n): Each insertion and deletion in the map takes O(log n), and each
// of the n cakes is processed once.

// ### Space Complexity:
// - O(n): The space required to store the map entries, proportional to the
// number of cakes.

// https://github.com/VaHiX/CodeForces/