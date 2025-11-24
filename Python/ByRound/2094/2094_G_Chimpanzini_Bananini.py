# Problem: CF 2094 G - Chimpanzini Bananini
# https://codeforces.com/contest/2094/problem/G

"""
G. Chimpanzini Bananini
Time Complexity: O(q) amortized per test case, where q is the number of operations.
Space Complexity: O(q) for storing the deque and intermediate results.

Algorithms/Techniques:
- Uses a deque to efficiently support operations at both ends of the array.
- Maintains a running sum 's' and a cumulative answer 'ans' to avoid recalculating rizziness from scratch on each operation.
- Tracks a flag to know which side elements are appended to (left or right).
- Performs cyclic shift by transferring an element from one end to the other while updating the rizziness efficiently.
- Perform reversal by flipping the flag and adjusting the answer accordingly.

"""

import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()
p = []
for _ in range(int(input())):
    arr, ans, s, flag = deque([]), 0, 0, True
    for __ in range(int(input())):
        match input().split():
            case "1",:  # Cyclic shift operation
                if flag:
                    arr.appendleft(x := arr.pop())  # Move last element to front (in forward direction)
                else:
                    arr.append(x := arr.popleft())  # Move first element to back (in reverse direction)
                ans += s - x * len(arr)  # Efficiently update rizziness using current sum and element
            case "2",:  # Reverse operation
                ans = (len(arr) + 1) * s - ans  # Recalculate total rizziness after reversal
                flag = not flag  # Flip the direction flag to know next append location
            case "3", x:  # Append element
                if flag:
                    arr.append(x := int(x))  # Append to right side
                else:
                    arr.appendleft(x := int(x))  # Append to left side
                ans += x * len(arr)  # Add contribution of new element to rizziness
                s += x  # Maintain updated cumulative sum for future updates
        p.append(str(ans))
print("\n".join(p))


# https://github.com/VaHiX/codeForces/