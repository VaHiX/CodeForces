# Problem: CF 1765 N - Number Reduction
# https://codeforces.com/contest/1765/problem/N

"""
Task: Number Reduction
Algorithm/Technique: Greedy with Stack-like Approach (Monotonic Stack)
Time Complexity: O(n) where n is the length of the input string x
Space Complexity: O(n) for storing the queue and position queue

The problem asks to reduce a number by exactly k operations, each removing one digit,
to get the smallest possible positive integer. This is done greedily:
- We use a stack-like approach to maintain digits in increasing order.
- When a smaller digit is encountered, we remove larger digits from the back if allowed.
- Special handling for zeros to prevent leading zero formation.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    s = map(int, input())  # Convert input string into list of integers
    k = int(input())
    queue = []             # Main result array storing digits
    posqueue = []          # Stack to track positive (non-zero) digits for comparison
    zerocnt = [0]          # Count of consecutive zeros at current position
    for el in s:           # Iterate through each digit
        # While we can still remove digits and the top of posqueue is larger than current digit
        while k > zerocnt[-1] and len(posqueue) > 0 and el < posqueue[-1]:
            # Special case handling to avoid leading zeros
            if el == 0 and len(posqueue) == 1:
                break
            # Remove the last digit from queue and update counters
            while queue.pop() == 0:
                k -= 1
            zerocnt.pop()
            posqueue.pop()
            k -= 1
        # If current digit is zero, increment zero counter at current position
        if el == 0:
            zerocnt[-1] += 1
        else:  # If not zero, update counters and add to stack
            zerocnt.append(0)
            posqueue.append(el)
        queue.append(el)  # Append the current digit to final queue
    # Output result: keep all digits except the last k removed ones
    sys.stdout.write("".join(map(str, queue[: len(queue) - k])) + "\n")


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/