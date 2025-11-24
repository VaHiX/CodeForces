# Problem: CF 1740 C - Bricks and Bags
# https://codeforces.com/contest/1740/problem/C

"""
Algorithm: Bricks and Bags
Techniques: Sorting, Two Pointers, Optimization

Time Complexity: O(n * log(n)) due to sorting
Space Complexity: O(1) if we don't count input storage, otherwise O(n)

This solution uses sorting and a sliding window approach to find the maximum possible score.
The key insight is that to maximize |w1 - w2| + |w2 - w3|, we need to consider the arrangement
of weights in bags such that the differences between the largest and smallest elements 
in each bag are maximized. By sorting and trying various splits, we compute the maximum
score for optimal distribution.
"""

for _ in range(int(input())):  # Iterate through each test case
    n = int(input())           # Read number of bricks
    a = list(map(int, input().split()))  # Read brick weights
    ans = 0                    # Initialize maximum score
    a.sort()                   # Sort weights to facilitate optimization
    
    # Loop through possible splits to maximize the score
    for i in range(n - 1):
        # Compute two potential scores:
        # 1. When we take maximum from bag1, minimum from bag2 and bag3
        # 2. When we take maximum from bag3, minimum from bag1 and bag2
        ans = max(ans, a[n - 1] + a[i] - 2 * a[i - 1], 2 * a[i + 1] - a[i] - a[0])
    
    print(ans)  # Output the maximum achievable score


# https://github.com/VaHiX/CodeForces/