# Problem: CF 1416 A - k-Amazing Numbers
# https://codeforces.com/contest/1416/problem/A

"""
Problem: k-Amazing Numbers

Algorithm:
This solution uses a sliding window approach combined with preprocessing to determine
the minimum number that appears in all subsegments of length k for each k from 1 to n.

Approach:
1. For each element, we track the maximum distance between consecutive occurrences.
2. We use a greedy method to assign answers for all possible lengths up to n.
3. The key idea is that if an element appears at positions p1, p2, ..., pm in the array,
   its influence covers subsegments of length at most (min(p_i - p_{i-1}, n - p_m + 1)).

Time Complexity: O(n) per test case
Space Complexity: O(n)

"""
import sys

tt = int(sys.stdin.readline().strip())
for _ in range(tt):
    n = int(sys.stdin.readline().strip())
    f = [0] * (n + 1)
    last = [0] * (n + 1)
    ans = [-1] * (n + 1)
    arr = [0] + list(map(int, sys.stdin.readline().split()))
    for i in range(1, n + 1):
        x = arr[i]
        # Update the maximum gap for element x
        f[x] = max(f[x], i - last[x])
        last[x] = i
    for x in range(1, n + 1):
        # Handle the case where element x appears at the end of array
        f[x] = max(f[x], n - last[x] + 1)
        # Greedily assign answer values from length f[x] onwards
        for i in range(f[x], n + 1):
            if ans[i] == -1:
                ans[i] = x
            else:
                break
    print(" ".join(map(str, ans[1:])))


# https://github.com/VaHiX/codeForces/