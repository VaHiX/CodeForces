# Problem: CF 1746 C - Permutation Operations
# https://codeforces.com/contest/1746/problem/C

"""
Problem: C. Permutation Operations
Algorithms/Techniques: Greedy approach with reindexing
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The solution uses a greedy strategy to minimize inversions. 
By transforming the array into a new indexing system and assigning operations 
based on how elements are reordered, we can ensure the final array is sorted 
with minimal inversions. 

Key insight:
- We map each value to its position in a sorted order.
- Then, we assign suffix operations based on this mapping.
"""

for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [0] * n
    for i in range(n):
        # Map each element to its "reversed rank" in the original array
        # This effectively reindexes the positions to guide operation selection
        b[n - a[i]] = i + 1
    print(*b)


# https://github.com/VaHiX/CodeForces/