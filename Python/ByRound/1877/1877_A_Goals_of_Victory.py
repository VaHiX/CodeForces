# Problem: CF 1877 A - Goals of Victory
# https://codeforces.com/contest/1877/problem/A

"""
Code Purpose:
This code solves the problem of determining the efficiency of a missing team in a football tournament.
Each team plays every other team exactly once, and the efficiency of a team is defined as the 
difference between the total goals it scored and the total goals scored by its opponents in all matches.

The key insight is that the sum of all team efficiencies must equal zero because each goal scored by 
a team contributes +1 to that team's efficiency and -1 to the opponent's efficiency, canceling out across all matches.

Algorithm:
- For each test case, read the number of teams n and the list of efficiencies for n-1 teams.
- Compute the sum of the given efficiencies.
- The missing team's efficiency is the negative of this sum.

Time Complexity: O(n) per test case, where n is the number of teams.
Space Complexity: O(n) for storing the list of efficiencies.

Techniques:
- Prefix sum concept applied to match outcomes
- Mathematical property: sum of all efficiencies = 0
"""

from sys import stdin, stdout


def read_str() -> str:
    return stdin.readline().strip()


def read_int() -> int:
    return int(stdin.readline().strip())


def read_list():
    return list(map(int, stdin.readline().split()))


def write(*args, **kwargs):
    sep = kwargs.get("sep", " ")
    end = kwargs.get("end", "\n")
    stdout.write(sep.join(str(a) for a in args) + end)


def ok(val: bool):
    write("YES") if val else write("NO")


for _ in range(read_int()):
    n = read_int()
    a = read_list()
    # The missing team's efficiency is the negative of the sum of known efficiencies
    write(0 - sum(a))


# https://github.com/VaHiX/CodeForces/