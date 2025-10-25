# Problem: CF 1931 E - Anna and the Valentine's Day Gift
# https://codeforces.com/contest/1931/problem/E

"""
Code Purpose:
This code solves the problem where Anna and Sasha play a game on a list of integers.
Anna reverses one number on her turn, and Sasha concatenates two numbers on his turn.
The game ends when only one number remains. Sasha wins if that number is >= 10^m, otherwise Anna wins.
The solution uses a greedy approach to determine the winner with optimal play.

Algorithms/Techniques:
- Greedy strategy for minimizing the final number's length
- Counting trailing zeros to estimate impact on number length
- Sorting to decide optimal pairing for Sasha

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the list of trailing zeros
"""

for _ in range(int(input())):
    n, m = map(int, input().split())  # Read n and m
    a = input().split()  # Read list of numbers as strings
    zeros = []
    ln = 0
    for x in a:
        ln += len(x)  # Add total length of all numbers
        zeros.append(len(x) - len(x.rstrip("0")))  # Count trailing zeros in x
    zeros.sort(reverse=True)  # Sort trailing zeros in descending order
    ln -= sum(zeros[::2])  # Subtract contribution of paired zeros (Anna's moves affect this)
    print("Sasha" if ln > m else "Anna")  # Determine winner based on final length


# https://github.com/VaHiX/CodeForces/