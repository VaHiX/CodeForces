// Problem: CF 1152 B - Neko Performs Cat Furrier Transform
// https://codeforces.com/contest/1152/problem/B

#include <cstdio>
#include <vector>
const long N = 35;
int main() {
  long x;
  scanf("%ld", &x);
  std::vector<int> v(N, 0); // Store binary representation of x
  for (long p = 0; p < N; p++) {
    v[p] = x % 2; // Extract least significant bit
    x /= 2;       // Move to next bit
  }
  std::vector<long> pos; // Store positions where operation A is applied
  long cnt(0);           // Count total operations
  long idx(N - 1);       // Start from most significant bit
  // Skip leading zeros to find the highest set bit
  while (!v[idx]) {
    --idx;
  }
  // Process bits from highest to lowest
  for (; idx >= 0; idx--) {
    if (v[idx]) {
      continue; // Skip if this bit is already 1
    }
    ++cnt; // Operation A: flip all bits from current position to end
    pos.push_back(idx + 1); // Record the operation
    for (long p = 0; p <= idx; p++) {
      v[p] = 1 - v[p]; // Flip bits
    }
    if (idx == 0) {
      break; // No more operations possible
    }
    bool done(true);
    for (long p = 0; p < idx; p++) {
      if (v[p] == 0) {
        done = false;
        break;
      }
    }
    if (done) {
      break; // All previous bits are 1, transformation complete
    }
    ++cnt; // Operation B: increment x
    bool carry = 1;
    for (long p = 0; p < idx; p++) {
      v[p] += carry;
      carry = (v[p] > 1);
      v[p] %= 2;
    }
  }
  printf("%ld\n", cnt); // Print number of operations
  for (long p = 0; p < pos.size(); p++) {
    printf("%ld ", pos[p]); // Print positions for operation A
  }
  puts(""); // New line
  return 0;
}


// https://github.com/VaHiX/codeForces/