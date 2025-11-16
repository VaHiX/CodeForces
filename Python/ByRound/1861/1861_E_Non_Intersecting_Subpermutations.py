# Problem: CF 1861 E - Non-Intersecting Subpermutations
# https://codeforces.com/contest/1861/problem/E

"""
Code Purpose:
This code calculates the sum of costs over all arrays of length n consisting of integers from 1 to k,
where the cost is defined as the maximum number of non-intersecting contiguous subarrays of length k
that contain each integer from 1 to k exactly once.

Algorithms/Techniques:
- Dynamic Programming with inclusion-exclusion principle
- Modular arithmetic for handling large numbers
- Precomputation of factorials and powers

Time Complexity: O(n * k)
Space Complexity: O(n * k)
"""

n, o = map(int, input().split())
ans = [1]
for i in range(1, o + 1):
    ans[-1] *= i
    ans[-1] %= 998244353
step = [1]
for i in range(n - o):
    step.append((step[-1] * o) % 998244353)
    newans = (ans[0] * step[-1]) % 998244353
    fact = 1
    for j in range(min(len(step) - 1, o - 1)):
        newans -= ans[i - j] * fact
        fact *= j + 2
        fact %= 998244353
        newans %= 998244353
    ans.append(newans)
ans2 = 0
for x in ans:
    ans2 += x * step.pop()
    ans2 %= 998244353
print(ans2)


# https://github.com/VaHiX/CodeForces/