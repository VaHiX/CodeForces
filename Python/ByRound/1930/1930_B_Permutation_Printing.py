# Problem: CF 1930 B - Permutation Printing
# https://codeforces.com/contest/1930/problem/B

"""
Algorithm: Permutation Printing
Techniques: Constructive Algorithm, Greedy

Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to construct a permutation of length n such that there are no two pairs
(i,j) where both p[i] divides p[j] and p[i+1] divides p[j+1]. 

The solution approach:
1. Separate odd and even numbers into two lists.
2. Reverse the odd list to ensure larger odds come first.
3. Interleave the reversed odds with evens.
4. If n is odd, append the last element of odd list to avoid conflicts.

This greedy interleaving ensures that no consecutive elements form a divide relationship
in both positions of the pair, satisfying the problem constraints.
"""

import sys

input = sys.stdin.readline
print = sys.stdout.write


def solve():
    n = int(input())
    odd = [*range(1, n + 1, 2)]
    odd.reverse()
    even = [*range(2, n + 1, 2)]

    ans = []
    for x in zip(odd, even):
        ans.extend(x)
    if n % 2:
        ans.append(odd[-1])

    return " ".join(map(str, ans))


print("\n".join(solve() for _ in range(int(input()))))


# https://github.com/VaHiX/CodeForces/