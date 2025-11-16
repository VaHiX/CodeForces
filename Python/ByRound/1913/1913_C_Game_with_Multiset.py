# Problem: CF 1913 C - Game with Multiset
# https://codeforces.com/contest/1913/problem/C

"""
Algorithm: Game with Multiset
Techniques: Greedy, Bit Manipulation, Multiset Subset Sum

The problem uses a greedy approach to represent numbers in terms of powers of 2.
We maintain a count of how many times each power of 2 (from 2^0 to 2^29) appears in the multiset.
For each GET query, we try to form the target value using available powers of 2 in a greedy way:
- Start from the highest power of 2 and try to use as many as possible.
- If the remaining value becomes zero, then it's possible to form the sum.
- Otherwise, it's not possible.

Time Complexity: O(m * log(max_val)) where m is number of operations and max_val is up to 10^9
Space Complexity: O(1) since we maintain fixed-size arrays for 32 powers of 2
"""

from sys import stdin, stdout


def solve(): ...


def main():
    m = int(stdin.buffer.readline().decode())
    # powers[i] = [2^i, count] to store power of 2 and its count
    powers = [[2**i, 0] for i in range(32)]
    # access maps 2^i to its index in powers array for fast lookup
    access = {2**i: i for i in range(32)}
    answers = list()

    for _ in range(m):
        t, v = map(int, stdin.buffer.readline().decode().split())
        if t == 1:
            # Add a new element 2^v to the multiset
            powers[access[2**v]][1] += 1
        else:
            # Check if we can form sum v using current multiset
            # Greedy approach: try to subtract largest possible powers first
            remaining = v
            for i in range(31, -1, -1):
                # Use as many of this power as possible without exceeding remaining value
                count_used = min(remaining // powers[i][0], powers[i][1])
                remaining -= powers[i][0] * count_used
            answers.append("Yes" if remaining == 0 else "No")

    stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/