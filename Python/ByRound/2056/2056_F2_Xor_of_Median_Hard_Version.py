# Problem: CF 2056 F2 - Xor of Median (Hard Version)
# https://codeforces.com/contest/2056/problem/F2

"""
F2. Xor of Median (Hard Version)
Algorithms/Techniques: 
- Bit manipulation and prefix sum techniques with XOR properties
- Dynamic Programming with bitmasking
- Fast bit operations and mathematical optimizations

Time Complexity: O(k * 2^k) where k is the number of bits in n, due to DP on states.
Space Complexity: O(2^k) for storing dp array.

This problem involves calculating the XOR of medians of all "good" sequences of length n,
with elements bounded by m. A good sequence satisfies a specific ordering condition
on occurrence counts of elements. Efficient bitwise operations and bitmask DP are used
to compute results.
"""

def S(n, k):
    # Returns boolean indicating if (n - k) & ((k - 1) >> 1) is false
    return not (n - k) & ((k - 1) >> 1)


def get(n, m):
    L = n.bit_length()  # number of bits in n
    up = 1 << L         # 2^L - upper bound for bitmasks
    dp = [0] * up       # DP array to store intermediate results
    
    # Initialize first part of DP table based on S function
    for i in range(n):
        dp[i] = S(n, i + 1)
    
    # Apply transformation using XOR and bit manipulation
    for j in range(L):
        for i in range(up):
            if (i >> j) & 1:  # Check if j-th bit is set
                dp[i] ^= dp[i ^ (1 << j)]  # XOR with flipped bit value
    
    ans = 0
    # Iterate through all valid states up to m
    for lst in range(up):
        if lst >= m:
            break
        if not dp[lst]:
            continue  # Skip invalid states
        
        cnt = (m - 1 - lst) >> L  # Compute cnt from bit shift and subtraction
        
        # Apply branching logic based on mod 4 of cnt
        if not (cnt & 1):         # if even cnt
            ans ^= lst
        if cnt % 4 == 0:
            ans ^= cnt << L       # Left shift by L bits and XOR
        elif cnt % 4 == 1:
            ans ^= 1 << L
        elif cnt % 4 == 2:
            ans ^= (cnt + 1) << L
        else:
            ans ^= 0              # No change for mod 4 == 3
    
    return ans


def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    results = []
    for _ in range(t):
        k = int(data[idx])      # number of bits
        m = int(data[idx + 1])
        s = data[idx + 2]
        idx += 3
        n = sum(int(c) & 1 for c in s)  # count set bits in binary string
        ans = get(n, m)
        results.append(ans)
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/