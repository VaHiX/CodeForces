// Problem: CF 1510 K - King's Task
// https://codeforces.com/contest/1510/problem/K

/*
K. King's Task
time limit per test
3 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output
The brave Knight came to the King and asked permission to marry the princess. The King knew that the Knight was brave, but he also wanted to know if he was smart enough. So he asked him to solve the following task.
There is a permutation p_i of numbers from 1 to 2n. You can make two types of operations. 

Swap p_1 and p_2, p_3 and p_4, ..., p_{2n-1} and p_{2n}. 
Swap p_1 and p_{n+1}, p_2 and p_{n+2}, ..., p_n and p_{2n}. 
The task is to find the minimal number of operations required to sort the given permutation.
The Knight was not that smart actually, but quite charming, so the princess asks you to help him to solve the King's task.

Algorithms/Techniques: BFS (Breadth-First Search) with state enumeration
Time Complexity: O(n * 2^(2n)) in worst case, but optimized by early termination and cycle detection
Space Complexity: O(2^n) for storing states and visited combinations
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <set>

using namespace std;
int n, a[2005];
signed main() {
  cin >> n;
  for (int i = 0; i < n + n; i++)
    cin >> a[i];
  int cyc = (n % 2 == 0 ? 4 : 2 * n), pos = -1;
  // Try up to 'cyc' operations to see if we can reach sorted state
  for (int i = 0; i < cyc; i++) {
    if (is_sorted(a, a + n + n)) {
      pos = i;
      break;
    }
    // Apply operation 1: swap adjacent pairs (1,2), (3,4), ...
    if (i % 2)
      for (int j = 0; j < n; j++)
        swap(a[j], a[j + n]);
    // Apply operation 2: swap elements at positions i and (i+n) 
    else
      for (int j = 0; j < n + n; j += 2)
        swap(a[j], a[j + 1]);
  }
  cout << min(pos, cyc - pos);
}


// https://github.com/VaHiX/codeForces/