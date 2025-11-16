# Problem: CF 1743 G - Antifibonacci Cut
# https://codeforces.com/contest/1743/problem/G

"""
Algorithm: Dynamic Programming with Rolling Hash and Optimization
Time Complexity: O(n * L * log L) where n is number of strings and L is average length
Space Complexity: O(L) for the rolling hash and dp arrays

This code computes the number of ways to cut a Fibonacci string into non-Fibonacci substrings.
It uses rolling hash technique with dynamic programming where:
- dp1 stores information about Fibonacci string prefixes
- dp2 stores extended information for longer strings
- The algorithm maintains a sliding window of computed values
- Hash-based optimizations help in quickly identifying Fibonacci prefixes
"""

import gc
import sys

input = sys.stdin.buffer.readline

n = int(input())
mod = 998244353
# Precompute Fibonacci numbers up to 32
f = [1, 1]
for _ in range(32):
    f.append(f[-1] + f[-2])

# Initialize dp1 array with 2^8 bit offset
dp1 = [0] * (1 << 12)
dp1[0] = 1 << 8
dp2 = dict()
k = []
n1, n2, s0, v = 0, 0, 1, 16
ans = [0] * n

for t in range(n):
    s = input()
    n2 += len(s) - 2
    # Update the rolling hash array
    dp1[n1 & 0xFFF] = (dp1[n1 & 0xFFF] & 0xFFFFFFFF00) ^ (s[0] & 1)
    for i in range(n1 + 1, n2):
        dp1[i & 0xFFF] = s[(i - n1) & 0xFFF] & 1
    dp1[n2 & 0xFFF] = 1
    
    # Process potential Fibonacci strings from current window
    for i in range(n2 - 1, max(n2 - 0xFFF - 1, -1), -1):
        if not dp1[i & 0xFFF] & 0xFF or dp1[(i + 1) & 0xFFF] & 0xFF:
            continue
        l = max(dp1[i & 0xFFF] & 0xFF, 2)
        # Extend Fibonacci length while possible
        while i + f[l + 1] <= n2 and dp1[(i + f[l]) & 0xFFF] & 0xFF >= l - 1:
            l += 1
        dp1[i & 0xFFF] = (dp1[i & 0xFFF] & 0xFFFFFFFF00) ^ l
        if l >= v:
            if not i in dp2:
                k.append(i)
            dp2[i] = dp1[i & 0xFFF]
    
    # Sort and process dp2 entries
    k.sort(reverse=True)
    for i in k:
        l = dp2[i] & 0xFF
        if l == v:
            continue
        # Extend if possible
        while i + f[l + 1] <= n2 and i + f[l] in dp2 and dp2[i + f[l]] & 0xFF >= l - 1:
            l += 1
        dp2[i] = (dp2[i] & 0xFFFFFFFF00) ^ l
    
    # Calculate answer for current prefix
    for i in range(n1 + 1, n2 + 1):
        # Compute base value from previous answer
        ans0 = s0 - (dp1[(i - 1) & 0xFFF] >> 8)
        for j in range(2, 33):
            if i - f[j] < 0:
                break
            # Check if valid Fibonacci prefix
            if j <= v:
                if dp1[(i - f[j]) & 0xFFF] & 0xFF >= j:
                    ans0 -= dp1[(i - f[j]) & 0xFFF] >> 8
            else:
                if i - f[j] in dp2 and dp2[i - f[j]] & 0xFF >= j:
                    ans0 -= dp2[i - f[j]] >> 8
        ans0 %= mod
        dp1[i & 0xFFF] = (dp1[i & 0xFFF] & 0xFF) ^ (ans0 << 8)
        s0 += ans0
    ans[t] = ans0
    n1 = n2
    gc.collect()
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/