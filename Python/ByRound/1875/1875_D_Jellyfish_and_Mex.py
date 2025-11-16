# Problem: CF 1875 D - Jellyfish and Mex
# https://codeforces.com/contest/1875/problem/D

"""
Created on Fri Dec  8 21:06:44 2023
@author: Lenovo
"""

# Flowerbox describing the code purpose, algorithms, time and space complexity
"""
Problem: Jellyfish and Mex
Algorithm: Dynamic Programming with Greedy Strategy
Time Complexity: O(n^2) in worst case, where n is the size of the array
Space Complexity: O(n) for the auxiliary arrays used in the solution
Approach:
- The MEX of an array is the smallest non-negative integer not present in the array.
- At each step, we remove one element from the array and add the MEX of the current array to the result.
- To minimize the final sum 'm', we need to strategically remove elements to keep the MEX as small as possible.
- We use a frequency count of elements in the range [0, n] to determine the MEX.
- A dynamic programming solution is used to determine the optimal removal order.
"""

for _ in range(int(input())):
    n = int(input())
    l = list(map(int, input().split()))
    check, flag = [0] * (n + 1), [True] * (n + 1)
    # Count occurrences of elements in range [0, n]
    for i in l:
        if i <= n:
            check[i] += 1
    # If 0 is not in the array, MEX is 0
    if not check[0]:
        print(0)
        continue
    minn = float("inf")
    # Determine the minimum frequency of elements that form a continuous sequence starting from 0
    for i in range(n + 1):
        if not check[i]:
            break
        elif check[i] < minn:
            minn = check[i]
        else:
            flag[i] = False
    # Initialize DP array with infinity, except the last index which is 0
    dp = [float("inf")] * i + [0]
    # Dynamic Programming from the end to the beginning
    for j in range(i, -1, -1):
        if not flag[j]:
            continue
        # For each valid j, compute minimum cost to reach state 0
        for k in range(j, i + 1):
            if not flag[k]:
                continue
            # Update dp[j] with the minimum value
            dp[j] = min(dp[j], dp[k] + k * (check[j] - 1) + j)
    print(dp[0])


# https://github.com/VaHiX/CodeForces/