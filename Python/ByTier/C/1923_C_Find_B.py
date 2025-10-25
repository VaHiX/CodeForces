# Problem: CF 1923 C - Find B
# https://codeforces.com/contest/1923/problem/C

"""
Algorithm: 
- For each query, we check if a subarray can form a "good" array b.
- A good array b exists if:
  1. The sum of elements in b equals the sum of elements in a.
  2. Each element in b is positive.
  3. Each element in b is different from the corresponding element in a.
- Key insight:
  - If all elements in the subarray are 1, it's impossible to make a good array.
    Because we'd require sum = m (where m is length), but we must also have b[i] != a[i], 
    and since a[i] = 1, b[i] must be >= 2. So the minimum sum is 2 * m, which contradicts sum = m.
  - Otherwise, if the total sum of the subarray is at least (m + count of 1s), a good array is possible.
    - Because we can try to make all elements 1 except where a[i] = 1, in which case b[i] should be at least 2.
    - This leads to a lower bound of m + count_of_1s for the sum.

Time Complexity: O(n + q) per test case
Space Complexity: O(n) for prefix arrays
"""

import sys


def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n, q = int(input[ptr]), int(input[ptr + 1])
        ptr += 2
        c = list(map(int, input[ptr : ptr + n]))
        ptr += n
        # Precompute prefix sum and prefix count of 1s
        prefix_sum = [0] * (n + 1)
        prefix_ones = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix_sum[i] = prefix_sum[i - 1] + c[i - 1]
            prefix_ones[i] = prefix_ones[i - 1] + (1 if c[i - 1] == 1 else 0)
        res = []
        for __ in range(q):
            l = int(input[ptr])
            r = int(input[ptr + 1])
            ptr += 2
            m = r - l + 1
            # If length is 1, impossible to make good array if value is 1
            if m == 1:
                res.append("NO")
            else:
                sum_sub = prefix_sum[r] - prefix_sum[l - 1]
                count_1 = prefix_ones[r] - prefix_ones[l - 1]
                # Minimum possible sum for array b
                sum_min = m + count_1
                if sum_sub >= sum_min:
                    res.append("YES")
                else:
                    res.append("NO")
        print("\n".join(res))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/