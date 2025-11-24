// Problem: CF 1858 E1 - Rollbacks (Easy Version)
// https://codeforces.com/contest/1858/problem/E1

/*
Problem: E1. Rollbacks (Easy Version)
Algorithm/Techniques: 
- Stack-based rollback mechanism to track changes
- Prefix sum technique to efficiently calculate distinct elements
- Vector tracking of minimum positions for each element to detect duplicates

Time Complexity: O(q) amortized per query, where q is the number of queries
Space Complexity: O(q) for storing the array, stack, and auxiliary structures

This implementation maintains an array with support for:
1. Adding elements to the end (+)
2. Removing last k elements (-)
3. Rolling back the last change (!)
4. Counting distinct elements (?)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct STEP {
  int x, posx, r, posr, pfx;
  STEP(int X, int PX, int R, int PR, int S) {
    x = X;
    posx = PX;
    r = R;
    posr = PR;
    pfx = S;
  };
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  char cmd;
  int q, ind = 0, Ln = 10000000;
  cin >> q;
  stack<STEP> STK;
  STEP ret(0, 0, 0, 0, 0);
  vector<int> arr(q + 1), pfx(q + 1), minpos(1000005, Ln), c_pfx(q + 1);
  
  for (int i = 1; i <= q; i++) {
    cin >> cmd;
    if (cmd == '?') {
      // Output the number of distinct elements at current state
      cout << pfx[ind] << "\n";
    } else if (cmd == '!') {
      // Rollback the last operation
      ret = STK.top();
      STK.pop();
      if (ret.x < 0) {
        // If rollback was a removal, adjust index
        ind -= ret.x;
      } else {
        // Restore previous state for addition
        pfx[ind] = ret.pfx;
        arr[ind] = ret.r;
        if (ret.posx > ind) {
          // Reset the count if element was added at a later position
          c_pfx[ind] = 0;
          minpos[ret.x] = ret.posx;
          if (ret.posx != Ln) {
            c_pfx[ret.posx] = 0;
          }
        }
        if (ret.posr == ind) {
          // Mark the element as removed from current position
          minpos[ret.r] = ind;
          c_pfx[ind] = 1;
        }
        ind--;
      }
    } else if (cmd == '+') {
      // Add an element to the array
      ind++;
      int n;
      cin >> n;
      // Store the state before this change
      STK.push(STEP(n, minpos[n], arr[ind], minpos[arr[ind]], pfx[ind]));
      if (minpos[arr[ind]] == ind) {
        // If previous element is at current index, reset its count
        c_pfx[ind] = 0;
        minpos[arr[ind]] = Ln;
      }
      if (minpos[n] > ind) {
        // If element was not in previous positions, mark new occurrence
        if (minpos[n] != Ln) {
          c_pfx[minpos[n]] = 0;
        }
        minpos[n] = ind;
        c_pfx[ind] = 1;
      }
      arr[ind] = n;
      pfx[ind] = pfx[ind - 1] + c_pfx[ind];
    } else {
      // Remove k elements from the end
      int b;
      cin >> b;
      STK.push(STEP(-b, 0, 0, 0, 0));
      ind -= b;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/