# Problem: CF 1864 C - Divisor Chain
# https://codeforces.com/contest/1864/problem/C

"""
Purpose: This code solves the "Divisor Chain" problem where we need to reduce a given integer x to 1 by repeatedly subtracting a divisor of the current value, with the constraint that each divisor can be used at most twice.

Algorithm:
1. For a given number x, we decompose it using binary representation principles to find a sequence of divisors.
2. The algorithm uses bit manipulation to find a binary decomposition of the number and then generates a chain of operations.
3. The sequence of operations is tracked and output in the required format.

Time Complexity: O(log x) per test case, since we're doing bit operations on the number.
Space Complexity: O(log x) for storing the sequence of operations.

Techniques:
- Bit manipulation
- Greedy approach based on binary decomposition
"""

def pl(li):
    for i in li:
        print(i, end=" ")


def solve():
    n = int(input())
    now = n
    li = []
    bit = 1
    for i in range(1001):
        if n == 0:
            break
        # While n is even, divide it by 2 and update bit
        while n % 2 == 0 and n:
            n //= 2
            bit *= 2
        if n == 0:
            break
        # Append the current bit value to the list
        li.append(bit)
        n -= 1
    # Start building the result sequence
    ans = [now]
    for i in li[:-1]:
        now -= i
        ans.append(now)

    bit //= 2

    # Add remaining powers of 2 to the sequence
    while bit:
        ans.append(bit)
        bit //= 2

    print(len(ans))
    print(" ".join(list(map(str, ans))))

    return 0


TT = int(input())
while TT:
    solve()
    TT -= 1


# https://github.com/VaHiX/CodeForces/