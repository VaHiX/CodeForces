// Problem: CF 1015 D - Walking Between Houses
// https://codeforces.com/contest/1015/problem/D

/*
D. Walking Between Houses
Algorithm: Greedy construction of moves to achieve exact distance s in k steps
Time Complexity: O(k)
Space Complexity: O(1)

The problem asks to find a sequence of k moves between houses numbered 1 to n,
starting from house 1, such that total Manhattan distance is exactly s.
Each move must go to a different house than current.

Approach:
1. Check if it's possible to achieve s distance in k moves:
   - Minimum possible distance is k (each move goes to adjacent house)
   - Maximum possible distance is (n-1)*k (each move maximizes distance by going to far end)

2. Construct the path greedily:
   - Start at house 1
   - At each step, try to use maximum possible distance (up to n-1) but not exceed remaining s
   - Alternate direction between left and right to maximize distance when needed

3. Output YES and the sequence of houses visited.

Sample Input/Output:
Input: 10 2 15
Output: YES
        10 4 

Input: 10 9 45
Output: YES
        10 1 10 1 2 1 2 1 6 
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n, k, s;
  scanf("%lld %lld %lld", &n, &k, &s);
  
  // Check feasibility: minimum k steps, maximum (n-1)*k steps
  if ((s < k) || ((n - 1) * k < s)) {
    puts("NO");
    return 0;
  }
  
  puts("YES");
  ll step = 1;  // Current position, starts at house 1

  while (k--) {
    // Calculate maximum possible distance for this move
    ll rm = (s - k < n - 1) ? (s - k) : (n - 1);
    s -= rm;  // Reduce remaining distance needed
    
    // Move in direction that maximizes total distance
    if (step + rm <= n) {
      step += rm;
    } else {
      step -= rm;
    }
    
    printf("%lld ", step);
  }
  
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/