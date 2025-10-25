// Problem: CF 1887 A1 - Dances (Easy version)
// https://codeforces.com/contest/1887/problem/A1

/*
 * Problem: A1. Dances (Easy version)
 * 
 * Algorithm/Technique: Greedy + Sorting
 * 
 * Time Complexity: O(n log n) per test case due to sorting and one pass scan
 * Space Complexity: O(n) for storing the arrays
 * 
 * Approach:
 * 1. For each test case, we generate array c[i] from array a where c[i][0] = i and c[i][j] = a[j] for j > 0.
 * 2. Since m = 1, we only process one such array.
 * 3. We sort both arrays a and b in ascending order to apply greedy matching.
 * 4. We use a two-pointer technique to match elements from a and b such that a[i] < b[i].
 *    - For each element in a, we find the smallest element in b that is greater than a[i].
 *    - Count how many such pairs can be formed.
 * 5. The number of operations needed is n minus the count of valid pairs.
 * 
 * Sample Input:
 * 4
 * 2 1
 * 1
 * 3 2
 * 4 1
 * 5 1 5
 * 3 8 3 3
 * 8 1
 * 4 3 3 2 2 1 1
 * 1 1 1 1 3 3 3 3
 * 9 1
 * 9 2 8 3 7 4 6 5
 * 1 2 3 2 1 4 5 6 5
 * 
 * Sample Output:
 * 0
 * 1
 * 4
 * 4
 */

#include <stdio.h>

typedef long long LL;
#include <algorithm>

using namespace std;

// Comparator for sorting in descending order (used for array b)
bool rcmp(int a, int b) { return a > b; }

// Comparator for sorting in ascending order (used for array a)
class mypcmp {
public:
  bool operator()(const int &a, const int &b) { return a < b; }
};

int as[100004];  // Array a (adjusted for 0-indexing)
int bs[100004];  // Array b

int main() {
  int n, m, i, j;
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d %d", &n, &m);
    
    // Read elements of array a starting from index 1
    for (i = 1; i < n; i++)
      scanf("%d", &as[i]);
    
    // Set first element of c[i] to 1 as per problem definition
    as[0] = 1;
    
    // Sort array a in ascending order
    sort(as, as + n);
    
    // Read elements of array b
    for (i = 0; i < n; i++)
      scanf("%d", &bs[i]);
    
    // Sort array b in ascending order
    sort(bs, bs + n);
    
    // Two-pointer approach to count how many elements in a can be matched with b
    for (i = 0, j = 0; i < n; i++) {
      // Move j until we find an element in b that is greater than current element in a
      while (j < n && as[i] >= bs[j])
        j++;
        
      // If no such element exists in b, break
      if (j >= n)
        break;
        
      // Move j to next element in b (since we matched as[i] with bs[j])
      j++;
    }
    
    // Number of operations required = total elements - matched pairs
    printf("%d\n", n - i);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/