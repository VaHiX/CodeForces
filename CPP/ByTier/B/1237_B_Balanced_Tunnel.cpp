// Problem: CF 1237 B - Balanced Tunnel
// https://codeforces.com/contest/1237/problem/B

/*
B. Balanced Tunnel
Algorithms/Techniques: Greedy, Set
Time complexity: O(n log n)
Space complexity: O(n)

Consider a tunnel on a one-way road. During a particular day, n cars numbered from 1 to n entered and exited the tunnel exactly once.
A traffic enforcement camera is mounted at the tunnel entrance. Another traffic enforcement camera is mounted at the tunnel exit.
Traffic regulations prohibit overtaking inside the tunnel. If car i overtakes any other car j inside the tunnel, car i must be fined.
Formally, let's say that car i definitely overtook car j if car i entered the tunnel later than car j and exited the tunnel earlier than car j.
Then, car i must be fined if and only if it definitely overtook at least one other car.
Find the number of cars that must be fined.

The approach uses a greedy method:
- Iterate through the exit order (b array)
- For each car exiting, check if it can be fined
- Use a set to track which cars have already entered the tunnel
- Skip cars that are already in the tunnel
- If a car is not the expected one (i.e., a[ind] != b[p]), it means there is an overtaking event
- Count those overtaking events for fineable cars

*/

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read entrance order
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]); // Read exit order
  }
  std::set<long> s; // Set to track cars already entered the tunnel
  long ind(0), cnt(0); // ind: index in entrance sequence, cnt: count of fines
  for (long p = 0; p < n; p++) {
    // Skip cars that are already in the tunnel (already entered)
    while (ind < n && s.count(a[ind])) {
      ++ind;
    }
    // If current car exiting is not the one expected to be at front,
    // then there was overtaking -> fine this car
    if (ind < n && b[p] != a[ind]) {
      ++cnt;
    }
    s.insert(b[p]); // Mark this car as entered the tunnel
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/