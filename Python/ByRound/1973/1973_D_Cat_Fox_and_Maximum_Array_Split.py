# Problem: CF 1973 D - Cat, Fox and Maximum Array Split
# https://codeforces.com/contest/1973/problem/D

"""
Algorithm: Binary search on the answer to find the maximum value m such that the array can be split into k subarrays,
each having f(l, r) = m. For each candidate m, we simulate the splitting process using queries.

Time Complexity: O(n^2 * log(n)) in worst case due to the nested loops and binary search on answer.
Space Complexity: O(1) - only using a few variables for computation.
"""

import sys

input = sys.stdin.readline


def ask(i, x):
    # Query the minimum r such that f(i, r) = x
    print(f"? {i + 1} {x}", flush=True)
    return int(input())


def answer(ans):
    # Output the final answer
    print(f"! {ans}", flush=True)
    ok = int(input())
    if ok == -1:
        exit()
    return


def solve():
    n, k = map(int, input().split())

    # Find the maximum value in the array by querying f(l, r) = i * n for decreasing i
    mx = 1
    for i in range(n, 1, -1):
        r = ask(0, i * n)
        if r == n:
            mx = i
            break

    if k == 1:
        # If k is 1, the whole array forms one subarray and the maximum value is the answer
        answer(n * mx)
        return

    # Binary search on the answer (max value m) to check feasibility for k splits
    for i in range(n // k, 0, -1):
        x = mx * i  # Consider this value as the candidate for maximum f(l, r)
        t = 0       # Number of subarrays formed so far
        l = 0       # Start index of current subarray
        
        while l < n and t < k:
            r = ask(l, x)  # Get the minimal r for f(l, r) = x
            if r == n + 1:
                # No such r exists for this value, so this candidate is infeasible
                break
            else:
                # Move to next segment
                l = r
                t += 1

        # If we've formed exactly k subarrays and exhausted the array
        if l == n and t == k:
            answer(x)
            return

    # No feasible value of m found
    answer(-1)
    return


T = int(input())
for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/