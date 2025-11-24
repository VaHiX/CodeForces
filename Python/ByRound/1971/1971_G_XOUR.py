# Problem: CF 1971 G - XOUR
# https://codeforces.com/contest/1971/problem/G

"""
Problem: G. XOUR
Algorithm: Grouping and Sorting
Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing the grouped elements

The problem involves rearranging an array such that the result is lexicographically smallest,
where swapping between two elements is allowed if their XOR is less than 4.
The key insight is that two numbers can be swapped if their XOR is less than 4, i.e., 
they differ in at most 2 bits.

To solve this:
1. Group numbers by their quotient when divided by 4 (since 4 = 2^2, we consider values mod 4)
2. Within each group, sort the elements in descending order
3. For the final array, take the smallest element from each group in order of original elements

This greedy approach works because:
- Numbers in the same group can be freely rearranged among themselves
- We assign the smallest available number from each group to the corresponding position
"""

import sys

input = lambda: sys.stdin.readline().strip()
write = sys.stdout.write

t = int(input())
res = [0] * t


def to_hashable(x):
    return -x * 4


for ti in range(t):
    n = int(input())
    la = list(map(int, input().split()))

    save = {}
    for i in la:
        var_i = to_hashable(i // 4)  # Group numbers by quotient when divided by 4
        if var_i not in save:
            save[var_i] = []
        save[var_i].append(i)

    for i in save:
        save[i].sort(reverse=True)  # Sort each group in descending order

    ans = [save[to_hashable(i // 4)].pop() for i in la]  # Greedily pick smallest from each group
    res[ti] = ans

write("\n".join(map(lambda t: " ".join(map(str, t)), res)))


# https://github.com/VaHiX/CodeForces/