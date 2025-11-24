# Problem: CF 2143 E - Make Good
# https://codeforces.com/contest/2143/problem/E

"""
E. Make Good

Algorithm:
This problem involves transforming a bracket string into a valid (regular) bracket sequence using two specific operations:
1. Replace "((" with "))" 
2. Replace "))" with "(("

Key insight:
- The operations essentially allow swapping pairs of adjacent brackets.
- A valid bracket sequence has equal numbers of '(' and ')' and never has more ')' than '(' at any prefix.
- We use a stack to simulate the matching process by pairing consecutive brackets.
- For each pair of identical adjacent brackets, we can "consume" them through the operations and count how many such pairs we could form (this is m).
- If we can't balance everything or end up with invalid starting/ending brackets, we output -1.

Time Complexity: O(n) where n is the length of the string. Each character is processed once.
Space Complexity: O(n) for the stack and temporary structures.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    II()  # Read n but don't use it directly
    s = input()
    sk = []  # Stack to simulate bracket matching
    m = 0  # Count of operations that can be applied (i.e., how many "((" or "))" pairs we can reduce)
    
    for c in s:
        if sk and sk[-1] == c:  # If the last character in stack matches current character
            sk.pop()  # Remove from stack — effectively applying an operation to reduce a pair
            m += 1  # Increment operation count
        else:
            sk.append(c)  # Push onto stack otherwise
    
    # If odd number of unmatched brackets or odd number of operations, impossible to form valid sequence
    if len(sk) % 2 or m % 2:
        print(-1)
        return
    
    # If we have unmatched closing bracket at the start and zero operations, not valid
    if sk and sk[0] == ")" and m == 0:
        print(-1)
        return
    
    # Construct result: prepend m opening brackets, add remaining stack contents, append m closing brackets
    res = "(" * m + "".join(sk) + ")" * m
    print(res)


for _ in range(II()):
    main()


# https://github.com/VaHiX/codeForces/