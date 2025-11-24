// Problem: CF 1913 C - Game with Multiset
// https://codeforces.com/contest/1913/problem/C

// Problem: Given a series of operations on a set of numbers, determine if a
// number can be formed
//          using existing numbers (like subset sum with bit manipulation)

// Approach:
// 1. For operation 1 (add number): increment count of that number in sum array
// 2. For operation 2 (query): check if given number can be formed from existing
// numbers
//    - Using bit manipulation: we process each bit from LSB to MSB
//    - For each bit position, we simulate the carry propagation
//    - If we encounter a set bit in query number, we need at least one
//    available number at that bit position
//    - We maintain a running sum and propagate carries appropriately
//    - If at any point we don't have enough numbers to satisfy a set bit,
//    return "NO"

// Time Complexity: O(n * 30) where n is number of operations and 30 is number
// of bits Space Complexity: O(1) since we use fixed size array (max 30 bits)

// Optimization: Use bit manipulation to propagate carries efficiently
// We simulate a binary addition process where we check if we can form the
// target

// Key insight: For the query, we want to know if target number can be made from
// existing numbers Think of it as a subset sum problem where each number
// contributes to its bit positions When we process from LSB to MSB:
//   - We accumulate existing numbers
//   - If target has a bit set at current position, we must have at least one
//   number to 'consume' it
//   - Carry propagation simulates how numbers can combine to form higher values

#include <iostream>
using namespace std;
#define REP(i, a, b) for (int i = (a); i <= (b); i++)
const int MAXN = 1e5 + 5;
int n;
int sum[100]; // sum[i] = count of numbers with only bit i set (i.e., 2^i)

int main() {
  cin >> n;
  int opt, v;
  REP(i, 1, n) {
    cin >> opt >> v;
    if (opt == 1) {
      sum[v]++;
    } else {
      int s = 0, flag = 1;
      REP(i, 0, 30) {
        s = (s / 2) + sum[i]; // s /= 2 to shift right + add current bit's sum
        if (v & (1 << i)) {   // if target has bit set at position i
          flag &= s > 0;      // we need at least one unit to satisfy this bit
          s -= 1;             // use one unit
        }
        if (!flag) { // early termination if impossible
          break;
        }
      }
      cout << (flag ? "YES" : "NO") << endl;
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/