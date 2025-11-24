# Problem: CF 461 A - Appleman and Toastman
# https://codeforces.com/contest/461/problem/A

"""
Purpose: 
    This code solves the problem of maximizing the score in a game between Appleman and Toastman.
    The approach uses sorting and a greedy strategy to compute the maximum possible score.
    
Algorithms/Techniques:
    - Sorting the array to process elements in ascending order
    - Greedy selection of elements to maximize contribution to the score
    - Mathematical formula to calculate final score efficiently

Time Complexity: O(n log n) due to sorting; the loop is O(n), so overall is O(n log n)
Space Complexity: O(1) as we use only a constant amount of extra space (excluding input)

The key insight is that when splitting groups, the sum of each group is added to the score.
To maximize the score, larger elements should contribute more times — hence, we sort and
use a formula that accumulates contributions optimally.
"""

n = int(input())
a = list(map(int, input().split()))
a.sort()

if n == 1:
    print(a[0])
else:
    s = a[-1] * n  # Add the largest element's full contribution (n times)
    for i in range(n - 1):
        # For each of the remaining elements, multiply by how many times it will be counted
        s += (i + 2) * a[i]
    print(s)


# https://github.com/VaHiX/CodeForces/