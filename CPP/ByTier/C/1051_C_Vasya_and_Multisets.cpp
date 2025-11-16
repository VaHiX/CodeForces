// Problem: CF 1051 C - Vasya and Multisets
// https://codeforces.com/contest/1051/problem/C

/*
Algorithm: Greedy split of multiset into two parts such that both parts have equal number of nice elements.
Techniques: 
- Count frequency of each element in the multiset.
- Identify "nice" elements (elements appearing exactly once).
- Assign nice elements to alternating groups (A, B) to balance the count.
- If there is an imbalance, reassign one element from a group with more than 2 occurrences to balance.

Time Complexity: O(n), where n is the size of input multiset. We iterate through the array constant number of times.
Space Complexity: O(1), since we use fixed-size arrays regardless of input size (up to 100 elements).

*/
#include <iostream>
using namespace std;
int i, n, m = 0, a[100], b[101] = {0}, c[100];  // b[] stores frequency, c[] stores group assignment (1=A, 2=B)
int main() {
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> a[i];
    ++b[a[i]];  // count frequency of each element
  }
  m = 1;  // flag to alternate between A and B for nice elements
  for (i = 0; i < n; i++)
    if (b[a[i]] == 1) {  // if element is nice (appears once)
      if (m)
        c[i] = 1;  // assign to group A
      else
        c[i] = 2;  // assign to group B
      m = 1 - m;   // toggle flag for next nice element
    }
  i = 0;
  if (!m) {  // if we have odd number of nice elements, we must balance
    for (i = 0; i < n; i++)
      if (!c[i] && b[a[i]] > 2) {  // find an element not yet assigned and appearing more than twice
        c[i] = 2;  // assign to group B
        break;
      }
  }
  if (i == n) {  // no element found to reassign, impossible to balance
    cout << "NO";
    return 0;
  }
  cout << "YES" << endl;
  for (i = 0; i < n; i++)
    if (c[i] == 2)
      cout << "B";  // print B if element assigned to group B
    else
      cout << "A";  // otherwise A
}


// https://github.com/VaHiX/CodeForces/