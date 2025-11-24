# Problem: CF 2002 E - Cosmic Rays
# https://codeforces.com/contest/2002/problem/E

"""
E. Cosmic Rays

Purpose:
This code solves a problem where we simulate the removal of elements from an array based on specific rules. Given a sequence described as pairs (a_i, b_i), representing 'a_i' copies of value 'b_i', we compute the number of seconds it takes to reduce each prefix of the sequence to empty. The simulation uses a stack-based approach to efficiently manage and process consecutive elements that can be removed together.

Algorithms/Techniques:
- Stack-based simulation
- Efficient processing using merge operations on adjacent identical values

Time Complexity: O(n) where n is the number of pairs in the input.
Space Complexity: O(n) for storing intermediate results and stack.

Each pair (a_i, b_i) describes a block of a_i copies of value b_i. 
The algorithm maintains a stack to simulate how elements are merged and removed over time.
"""

import sys

input = sys.stdin.readline


def ri():
    return int(input())


def rl(v_type=int):
    return list(map(v_type, input().split()))


def rs():
    return input().rstrip()


def out(x, sep=" "):
    return sep.join(map(str, x))


def solve_case():
    n = ri()
    stk = []  # Stack to hold [value, count] pairs
    res = []  # Result list for each prefix
    ans = 0   # Total seconds taken so far
    for _ in range(n):
        a, b = rl()  # Read next pair (count, value)
        l = 0  # Local count of elements to be removed in this step
        # While stack is not empty and conditions allow merging:
        while stk and (a > 0 or stk[-1][0] == b):
            if stk[-1][0] == b:  # If current value matches top of stack
                l += stk.pop()[1]  # Merge counts
            else:
                take = min(a, stk[-1][1])  # Take minimum of remaining a and stack count
                a -= take  # Reduce a by taken amount
                l += take  # Add to local count
                stk[-1][1] -= take  # Reduce stack count
                if stk[-1][1] == 0:  # If stack count becomes zero, pop it
                    stk.pop()
        ans += a  # Add remaining a to total seconds
        l += a  # Merge remaining a into local count
        stk.append([b, l])  # Push new block onto stack
        res.append(ans)  # Store result for current prefix
    return out(res)


if __name__ == "__main__":
    T = int(input())
    ret = [solve_case() for ti in range(1, T + 1)]
    print(out(ret, "\n"))


# https://github.com/VaHiX/codeForces/