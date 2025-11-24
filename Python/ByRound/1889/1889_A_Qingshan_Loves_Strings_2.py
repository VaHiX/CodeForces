# Problem: CF 1889 A - Qingshan Loves Strings 2
# https://codeforces.com/contest/1889/problem/A

"""
Problem: Qingshan Loves Strings 2

Purpose:
This code determines whether a binary string can be made "good" by inserting "01" at most 300 times.
A string is "good" if no prefix of length k equals the reverse of any suffix of same length (i.e., s[i] != s[k-i+1] for all valid i).
The algorithm uses a deque-based approach to match characters from both ends of the string and decide where to insert '01' to eventually make it good.

Algorithms/Techniques:
- Two-pointer simulation using deque
- Greedy insertion strategy

Time Complexity: O(n^2) in worst case due to repeated operations on string segments
Space Complexity: O(n) for storing the string in deque and result list

Input:
- t: number of test cases
- n: length of string
- s: binary string consisting of only 0 and 1

Output:
- -1 if impossible to make good string
- Otherwise, number of operations followed by indices where '01' was inserted
"""

from collections import deque

for _ in range(int(input())):
    n = int(input())
    s = input()
    if s.count("0") != s.count("1"):  # If counts of 0s and 1s are unequal, impossible to make good string
        print(-1)
        continue
    q = deque(s)  # Use deque for efficient append/pop from both ends
    front = 0  # Tracks front insertion index
    rear = n   # Tracks rear insertion index
    ans = []   # Stores indices where '01' was inserted
    while q:   # While there are characters left in the deque
        if q[0] != q[-1]:  # If first and last char don't match, remove them
            q.pop()
            q.popleft()
            rear -= 2
        elif q[0] == "1":  # If both ends are '1', insert '1' at front and mark position for insertion
            q.appendleft("1")
            q.pop()
            ans.append(front)
        else:  # If both ends are '0', insert '0' at rear and mark position for insertion
            q.append("0")
            q.popleft()
            ans.append(rear)
        front += 1  # Update front index
        rear += 1   # Update rear index
    print(len(ans))   # Number of operations
    print(*ans)       # Indices where '01' was inserted



# https://github.com/VaHiX/codeForces/