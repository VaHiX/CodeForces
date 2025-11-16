# Problem: CF 1599 A - Weights
# https://codeforces.com/contest/1599/problem/A

"""
Algorithm: Greedy approach to assign weights to balance sides
Time Complexity: O(N * log(N)) due to sorting
Space Complexity: O(N) for storing the weights and processing

The problem requires placing weights one by one such that after placing each weight,
the left or right side of the balance is heavier according to the given string S.
We use a greedy approach:
1. Sort the weights in ascending order.
2. Identify the first position where the string S changes from 'L' to 'R' or vice versa.
3. Distribute the weights to satisfy the constraints by assigning them to the correct sides.
4. For each step, if the current instruction matches the previous one, we continue with same side;
   otherwise we switch sides.

The code handles the assignment of weights based on the transitions in the string S.
The key insight is to process the transitions and assign weights accordingly.
"""

import sys

inf = float("inf")
buffer = open(1, "w", 10**6)


def print(*args, sep=" ", end="\n"):
    buffer.write(sep.join(str(arg) for arg in args) + end)


def flush():
    buffer.flush()


def input():
    return sys.stdin.readline()


def read_ints(index=None):
    return [int(x) for x in input().split()]


def read_ints_indexed(index):
    return [(int(x), i + index) for i, x in enumerate(input().split())]


def solve():
    n = int(input())
    a = read_ints()  # Read weights
    s = input()      # Read the string of instructions
    sides = ["L", "R"]  # Possible sides of balance
    a.sort()         # Sort weights in ascending order for greedy assignment

    # Count number of transitions in the string S
    x = 0
    for i in range(n - 1):
        if s[i] != s[i + 1]:
            x += 1

    # Determine how many weights to place on left and right sides
    left = n - x - 1
    left_side = sides.index(s[0])  # Initial side for left
    right = n - x - 1
    right_side = sides.index(s[0])  # Initial side for right

    # Place the first weight on the required side
    print(a[left], s[0])

    # Process remaining weights
    for i in range(1, n):
        if s[i] == s[i - 1]:
            # If current instruction is same as previous, continue with same side
            left -= 1
            left_side ^= 1  # Toggle the side using XOR
            print(a[left], sides[left_side])
        else:
            # If instruction changes, switch sides
            right += 1
            right_side ^= 1  # Toggle the side using XOR
            print(a[right], sides[right_side])


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/