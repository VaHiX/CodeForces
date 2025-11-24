# Problem: CF 2078 F - Binary Subsequence Value Sum
# https://codeforces.com/contest/2078/problem/F

# F. Binary Subsequence Value Sum
# Purpose:
#   This code solves the problem of computing the sum of scores over all non-empty subsequences
#   after a series of bit flips on a binary string. Each query modifies one bit and requires
#   updating the total score efficiently.
#
# Algorithms/Techniques:
#   - Precomputation of powers of 2 modulo MOD for fast exponentiation
#   - Efficient calculation using mathematical formula derived from F(v,l,r) function
#   - Modular arithmetic with inverse elements for division
#
# Time Complexity: O(n + q) per test case (linear time preprocessing, queries)
# Space Complexity: O(n) for storage of powers and input data

import sys

MOD = 998244353
M = 200005
pt = [1] * M  # Precompute powers of 2 mod MOD
for i in range(1, M):
    pt[i] = (pt[i - 1] * 2) % MOD
inv4 = pow(4, MOD - 2, MOD)  # Modular inverse of 4 mod MOD (using Fermat's Little Theorem)

data = sys.stdin.buffer.read().split()
if not data:
    sys.exit()

t = int(data[0])
p = 1
res_list = []

for _ in range(t):
    n = int(data[p])
    p += 1
    q = int(data[p])
    p += 1
    s = data[p].decode()
    p += 1

    # Convert string to list of integers (0s and 1s)
    arr = [1 if c == "1" else 0 for c in s]
    z = arr.count(0)  # Count of zeros in current array

    for _ in range(q):
        pos = int(data[p])
        p += 1
        pos -= 1  # Convert to 0-based index

        # Flip the value at position 'pos'
        if arr[pos] == 0:
            arr[pos] = 1
            z -= 1  # Reduce zero count
        else:
            arr[pos] = 0
            z += 1  # Increase zero count

        # Special case when n=1, sum of scores is always 0
        if n == 1:
            res_list.append("0")
        else:
            # Compute score formula: (n*(n+1) - 4*n*z + 4*z*z)
            X = (n * (n + 1) - 4 * n * z + 4 * z * z) % MOD
            # Apply recurrence based on powers of 2 and modular inverse
            r = (pt[n - 2] * X - pt[n - 1]) % MOD
            r = (r * inv4) % MOD
            res_list.append(str(r))

sys.stdout.write("\n".join(res_list))


# https://github.com/VaHiX/codeForces/