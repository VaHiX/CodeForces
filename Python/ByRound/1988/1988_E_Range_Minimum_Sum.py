# Problem: CF 1988 E - Range Minimum Sum
# https://codeforces.com/contest/1988/problem/E

"""
Algorithm: Range Minimum Sum
Technique: Monotonic Stack, Difference Array, Prefix Sum

Time Complexity: O(n)
Space Complexity: O(n)

This solution computes the sum of minimum elements over all subarrays for a given permutation,
after removing each element one by one. It uses two passes with monotonic stacks to find
the range in which each element is the minimum, then applies a difference array technique
to efficiently compute the contribution of each element to the total sum.
"""

def solve():

    n = int(input())
    a = list(map(int, input().split()))

    # stk[0] and stk[1] are used to maintain indices in increasing order (monotonic stack)
    # left[i][j] stores the index of previous smaller element for j=0, and next smaller for j=1
    # right[i][j] stores the index of next smaller element for j=0, and previous smaller for j=1
    stk = [[], []]
    left = [[-1, -1] for _ in range(n)]
    right = [[n, n] for _ in range(n)]

    # First pass: compute left and right boundaries using monotonic stacks
    for i in range(n):
        for j in range(1, -1, -1):
            tmp = []
            # Pop elements from stack while current element is smaller
            while stk[j] and a[i] < a[stk[j][-1]]:
                if j == 0:
                    tmp.append(stk[j][-1])
                right[stk[j][-1]][j] = i
                stk[j].pop()
            if j == 0:
                # Reverse tmp and push to second stack for next stage
                stk[1].extend(reversed(tmp))
        stk[0].append(i)

    # Clear stacks for second pass
    stk[0].clear()
    stk[1].clear()

    # Second pass: same as before but in reverse direction
    for i in range(n - 1, -1, -1):
        for j in range(1, -1, -1):
            tmp = []
            while stk[j] and a[i] < a[stk[j][-1]]:
                if j == 0:
                    tmp.append(stk[j][-1])
                left[stk[j][-1]][j] = i
                stk[j].pop()
            if j == 0:
                stk[1].extend(reversed(tmp))
        stk[0].append(i)

    # Arrays to store contributions
    f = [0] * n
    g = [0] * n

    # Compute contributions of each element to the function f
    for i in range(n):
        l = left[i][0]   # Left boundary where a[i] is minimal
        r = right[i][0]  # Right boundary where a[i] is minimal
        g[0] += (i - l) * (r - i) * a[i]  # Base contribution
        f[i] -= (i - l) * (r - i) * a[i]  # Subtracting self-contribution
        # Update difference array for ranges
        if l + 1 < n:
            g[l + 1] -= (r - i) * a[i]
        g[i] += (r - i) * a[i]
        if i + 1 < n:
            g[i + 1] -= (i - l) * a[i]
        if r < n:
            g[r] += (i - l) * a[i]
            f[r] += (right[i][1] - r - 1) * (i - l) * a[i]
        if l >= 0:
            f[l] += (l - left[i][1] - 1) * (r - i) * a[i]

    # Compute prefix sum of g array
    for i in range(1, n):
        g[i] += g[i - 1]

    # Final result is sum of f and g arrays
    result = [f[i] + g[i] for i in range(n)]
    for i in result:
        print(i, end=" ")
    print()


T = int(input())

while T:
    solve()
    T -= 1


# https://github.com/VaHiX/CodeForces/