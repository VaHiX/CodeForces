# Problem: CF 1904 D2 - Set To Max (Hard Version)
# https://codeforces.com/contest/1904/problem/D2

"""
Algorithm: 
- This problem uses a sliding window technique with a deque to simulate the operations.
- For each position in the array, we maintain a deque that stores values in a decreasing order.
- We process the array from left to right and then from right to left.
- At each step, we check if we can assign the value from b[i] to a[i] based on the constraints of the operations.

Time Complexity: O(n) - Each element is pushed and popped from the deque at most once.
Space Complexity: O(n) - The deque can store up to n elements.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
from collections import deque

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    def solve(order):
        dq = deque()
        for i in order:
            # Remove elements from the end of deque that are <= a[i]
            while dq and dq[-1] <= a[i]:
                dq.pop()
            # Remove elements from the front of deque that are > b[i]
            while dq and dq[0] > b[i]:
                dq.popleft()
            # Add a[i] to the deque
            dq.append(a[i])
            # If the front of deque equals b[i], we can assign it to a[i]
            if dq[0] == b[i]:
                a[i] = b[i]

    # Process from left to right
    solve(range(n))
    # Process from right to left
    solve(reversed(range(n)))
    # Check if arrays are equal
    print("YES" if a == b else "NO")


# https://github.com/VaHiX/CodeForces/