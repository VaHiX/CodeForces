# Problem: CF 1898 D - Absolute Beauty
# https://codeforces.com/contest/1898/problem/D

"""
Code Purpose:
This solution computes the maximum possible absolute beauty of array b after at most one swap of two elements.
It uses a greedy approach to determine whether swapping two elements can improve the result.

Algorithm:
1. Initially, for each pair (a[i], b[i]), ensure a[i] <= b[i] by swapping if needed.
2. Calculate the initial absolute beauty as sum of (b[i] - a[i]).
3. Find the minimum value in array b and maximum value in array a.
4. If min_b < max_a, then swapping can potentially improve the beauty.
   In such case, we greedily swap the extremes to maximize the difference.

Time Complexity: O(n), where n is the length of arrays.
Space Complexity: O(1), only using a constant amount of extra space.

Techniques:
- Greedy approach
- Single pass optimizations
"""

def calculate_max_absolute_beauty():
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        absolute_beauty = 0
        for i in range(n):
            if a[i] > b[i]:
                a[i], b[i] = b[i], a[i]
            absolute_beauty += b[i] - a[i]
        min_b = min(b)
        max_a = max(a)
        if min_b < max_a:
            absolute_beauty += (max_a - min_b) * 2
        print(absolute_beauty)


calculate_max_absolute_beauty()


# https://github.com/VaHiX/CodeForces/