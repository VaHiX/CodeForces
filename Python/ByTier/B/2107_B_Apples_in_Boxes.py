# Problem: CF 2107 B - Apples in Boxes
# https://codeforces.com/contest/2107/problem/B

"""
B. Apples in Boxes

Purpose:
This code determines the winner of a game between Tom and Jerry where they take turns picking apples from boxes,
with specific rules about when a player loses. The game ends when no valid move remains or after a move causes 
the difference between max and min apples in boxes to exceed k.

Algorithm/Techniques:
- Greedy strategy analysis
- Mathematical condition check for winner prediction
- Optimized input processing using lambda and tuple unpacking

Time Complexity: O(n) per test case, where n is the number of boxes.
Space Complexity: O(1) additional space (excluding input storage).

The key insight is that if the difference between max and min apples exceeds k after any move,
the current player loses. Therefore, we simulate a condition based on the starting array:
- If the difference (after accounting for one apple) is already > k, Tom loses immediately.
- Otherwise, the result depends on whether the sum of apples is odd or even.
"""

I = lambda: (*map(int, input().split()),)  # Inline function to read and unpack two integers


def s():
    n, k = I()  # Read n (number of boxes) and k (threshold difference)
    a = I()     # Read the apples in each box
    R = (m := max(a)) - min(a) - (not (a.count(m) - 1))  # Calculate adjusted max-min diff
    return 0 if R > k else sum(a) & 1  # Return 0 if Tom loses; otherwise use parity of total apples


print("\n".join("Tom" if s() else "Jerry" for ti in int(input()) * (1,)))


# https://github.com/VaHiX/codeForces/