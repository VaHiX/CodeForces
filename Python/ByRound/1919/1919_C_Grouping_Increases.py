# Problem: CF 1919 C - Grouping Increases
# https://codeforces.com/contest/1919/problem/C

"""
Algorithm: Greedy approach to minimize the number of increasing transitions in two subsequences.
Time Complexity: O(n) where n is the length of the array
Space Complexity: O(1) - only using a few variables

This problem asks to split an array into two subsequences such that the sum of penalties (number of increasing transitions)
in both subsequences is minimized. The key insight is to greedily assign each element to one of the two subsequences such
that we maintain the smallest possible "tail" values for both subsequences. This helps minimize the number of times
we need to start a new increasing sequence in either subsequence.
"""

from sys import stdin

INF = float("inf")
input = stdin.readline


def read_str():
    return input().rstrip()


def read_int():
    return int(input().rstrip())


def read_lst():
    return list(map(int, input().rstrip().split()))


def read_map():
    return map(int, input().rstrip().split())


def ok(b):
    print("YES" if b else "NO")


def solve():
    read_int()
    a = read_lst()
    l1 = l2 = INF  # l1 and l2 represent the smallest and second smallest tails of the two subsequences
    p = 0  # penalty counter
    for i in a:
        # Swap l1 and l2 if l1 > l2 to ensure l1 <= l2
        if l1 > l2:
            l1, l2 = l2, l1
        # If current element can be appended to the first subsequence (l1)
        if i <= l1:
            l1 = i
        # If current element can be appended to the second subsequence (l2)
        elif i <= l2:
            l2 = i
        # If current element cannot be appended to either subsequence, we must start a new sequence
        else:
            l1 = i
            p += 1  # increment penalty because we start a new increasing chain
    print(p)


def main():
    for _ in range(read_int()):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/