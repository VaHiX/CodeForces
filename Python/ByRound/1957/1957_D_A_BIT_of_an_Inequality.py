# Problem: CF 1957 D - A BIT of an Inequality
# https://codeforces.com/contest/1957/problem/D

"""
Algorithm: Efficient Counting of Triplets Satisfying XOR Inequality

The problem is to count the number of tuples (x, y, z) such that:
1. 1 ≤ x ≤ y ≤ z ≤ n
2. f(x, y) ⊕ f(y, z) > f(x, z)

Where f(l, r) = a[l] ⊕ a[l+1] ⊕ ... ⊕ a[r], i.e. XOR of subarray from l to r.

Key Observations:
- f(x, y) = P[y] ⊕ P[x-1], where P is prefix XOR array.
- f(y, z) = P[z] ⊕ P[y]
- f(x, z) = P[z] ⊕ P[x-1]
- Substituting these into the inequality:
  (P[y] ⊕ P[x-1]) ⊕ (P[z] ⊕ P[y]) > (P[z] ⊕ P[x-1])
  Simplifies to:
  P[x-1] ⊕ P[z] > P[z] ⊕ P[x-1]
  Which is always false unless we consider bit-by-bit analysis.

A more effective approach:
- Fix y, and analyze bits from most significant to least significant.
- For any specific bit k at which a[y] has a 1, we consider:
  - How many x < y have P[x-1] having a 1 at bit k
  - How many z > y have P[z] having a 1 at bit k
  - If both are 1 or both 0, the contribution adds to valid triplets.
  - If one is 1 and other is 0, this causes an inequality.

Time Complexity: O(32 * n) per test case = O(n)
Space Complexity: O(32 * n) for cumulative prefix bit counts = O(n)

"""

import sys


def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        # Compute prefix XOR array
        P = [0] * (n + 1)
        for i in range(1, n + 1):
            P[i] = P[i - 1] ^ a[i - 1]
        # Precompute cumulative count of 1s at each bit position
        cumulative = [[0] * (n + 1) for _ in range(32)]
        for k in range(32):
            count = 0
            for i in range(n + 1):
                if (P[i] >> k) & 1:
                    count += 1
                cumulative[k][i] = count
        total_triplets = 0
        # Iterate through all possible y positions
        for y in range(1, n + 1):
            num = a[y - 1]
            if num == 0:
                continue
            # Get highest bit set in a[y]
            k = num.bit_length() - 1
            # Count of 1s in prefix P[0..y-1] at bit k
            left_ones = cumulative[k][y - 1]
            # Count of 0s in prefix P[0..y-1] at bit k
            left_zeros = y - left_ones
            # Count of 1s in suffix P[y..n] at bit k
            right_ones = cumulative[k][n] - cumulative[k][y - 1]
            # Count of 0s in suffix P[y..n] at bit k
            right_zeros = (n - y + 1) - right_ones
            # Add valid combinations to total
            total_triplets += left_ones * right_ones + left_zeros * right_zeros
        results.append(str(total_triplets))
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/