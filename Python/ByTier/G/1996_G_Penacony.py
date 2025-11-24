# Problem: CF 1996 G - Penacony
# https://codeforces.com/contest/1996/problem/G

"""
Algorithm: Randomized Hashing + Prefix XOR
Purpose: 
    Determine the minimum number of roads to maintain in a circular graph such that 
    all given friend pairs can be connected through maintained roads. 
    The solution uses a randomized approach with prefix XOR to detect cycles in the 
    friendship graph and compute the minimum number of edges required.

Time Complexity: O(n + m) per test case, where n is the number of houses and m is the number of friendships.
Space Complexity: O(n) for storing XOR values and hash map.
"""

from random import randint
from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
print = lambda *x, sep=" ", end="\n": stdout.write(sep.join(map(str, x)) + end)


def out(l):
    print(" ".join(map(str, l)))


def yes():
    print("Yes")


def no():
    print("No")


def alice():
    print("Alice")


def bob():
    print("Bob")


def solve():
    n, m = map(int, input().split())
    # Initialize XOR array to store random hashes for each node
    xor = [0] * n
    for i in range(m):
        a, b = map(int, input().split())
        # Assign a random hash to both nodes of the friendship edge
        num = randint(1, 10**12)
        xor[a - 1] ^= num  # XOR the hash with node a
        xor[b - 1] ^= num  # XOR the hash with node b
    # Dictionary to count occurrences of prefix XOR values
    d = {}
    ans = 0
    cur = 0  # Current prefix XOR value
    for i in xor:
        cur ^= i  # Update prefix XOR
        if cur in d:
            d[cur] += 1  # Increment count if value exists
        else:
            d[cur] = 1  # Initialize count if value does not exist
        ans = max(ans, d[cur])  # Track maximum frequency of any prefix XOR
    # The answer is total nodes minus the maximum frequency of prefix XOR
    print(n - ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/