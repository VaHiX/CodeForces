# Problem: CF 2057 H - Coffee Break
# https://codeforces.com/contest/2057/problem/H

"""
Algorithm: Coffee Break
Purpose: To determine the maximum number of students that can be gathered around each coffee machine after a series of light-switching operations.
Techniques:
- Simulation with efficient handling of student redistribution
- Two-pass approach: right-to-left and left-to-right pass
- Prefix and suffix processing for optimal student gathering

Time Complexity: O(n) per test case, where n is the number of coffee machines
Space Complexity: O(n) for storing intermediate results and arrays

The solution computes for each position the maximum number of students that can be gathered there by redistributing students from adjacent positions
using the light-switching mechanism.
"""

from typing import List


def get_right_out(a: List[int], res: List[int]) -> List[int]:
    n = len(a)
    st = []
    res = [0] * (n + 1)

    for i in range(n):
        x = a[i] + res[i]  # Current students at position i, including those moved from previous operations
        st.append(i)

        while x != 0:
            if not st:  # If stack is empty, we must distribute all remaining students
                length = i + 1
                cnt = x // (length + 1)
                res[i + 1] += cnt * length  # Distribute students optimally to next room
                x -= cnt * (length + 1)  # Subtract the distributed students

                if x != 0:
                    res[i + 1] += x
                    st.append(x - 1)
                    x = 0
            else:
                j = st[-1]  # Get the top element from stack (previous room index)
                if x > i - j:  # If more students than space available between j and i
                    res[i + 1] += i - j  # Move students from room j to room i+1
                    st.pop()  # Remove the processed index
                    x -= i - j + 1  # Subtract count of students moved plus one for self
                else:  # If x <= i - j, move x students and update stack
                    res[i + 1] += x
                    st[-1] += x
                    x = 0

    return res


def get_left_out(a: List[int], b: List[int]) -> List[int]:
    # Reverse the input array to simulate left to right pass as right to left
    a = a[::-1]
    b = get_right_out(a, b)  # Apply right pass on reversed input
    b = b[::-1]  # Reverse result back to original direction
    a = a[::-1]  # Reverse input back
    return b


def solve():
    n = int(input())
    a = list(map(int, input().split()))

    lhs = []
    rhs = []

    lhs = get_right_out(a, lhs)
    rhs = get_left_out(a, rhs)

    # Compute final answer by combining results from both directions
    result = [lhs[i] + a[i] + rhs[i + 1] for i in range(n)]
    print(*result)


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/