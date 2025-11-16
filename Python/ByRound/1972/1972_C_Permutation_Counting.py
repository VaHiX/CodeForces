# Problem: CF 1972 C - Permutation Counting
# https://codeforces.com/contest/1972/problem/C

"""
Purpose: 
This code solves the problem of maximizing the number of permutations of [1, 2, ..., n] in contiguous subarrays of length n,
after buying up to k additional cards. The solution uses binary search to find the optimal number of copies of each card type,
then calculates the maximum score based on how many valid permutations can be formed.

Algorithms/Techniques:
- Binary Search: To find the optimal number of cards of each type (l) such that total cost <= k.
- Greedy Rearrangement: After determining optimal counts, greedily arrange to maximize permutation subarrays.

Time Complexity: O(n * log(10^18)) due to binary search over a large range and linear operations in each step.
Space Complexity: O(1) as we use only a few variables and the input array is modified in place.
"""

for i in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    l = 0
    r = 10**18

    # Binary search for the maximum number of copies we can have for each card type
    while r - l > 1:
        m = (l + r) // 2

        y = 0
        flag = True
        for i in a:
            if i < m:
                y += m - i
            if y > k:
                flag = False
                r = m
                break
        if flag:
            l = m

    # Initial score calculation based on number of full permutations we can form
    ans = l * n - (n - 1)

    # Adjust available cards after buying to support at least 'l' copies of each
    for i in range(n):
        if a[i] >= l:
            a[i] -= l
        else:
            k -= l - a[i]
            a[i] = 0

    # Add additional 1s to score if we still have coins left (can form one extra valid subarray)
    for i in a:
        if i > 0:
            ans += 1

    print(ans + k)


# https://github.com/VaHiX/CodeForces/