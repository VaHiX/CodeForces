# Problem: CF 1681 D - Required Length
# https://codeforces.com/contest/1681/problem/D

"""
BFS to find minimum operations to make x have exactly n digits.
Each operation multiplies x by a digit that appears in x.
Time Complexity: O(10^n * n) - At most 10^n strings of length at most n, each operation takes O(n) time.
Space Complexity: O(10^n * n) - For storing visited strings and queue.
"""
def I():
    return [int(e) for e in input().split()]


n, x = I()
x = str(x)
d = {x: 0}  # Dictionary to store minimum steps to reach each string representation of x
q = [x]     # Queue for BFS
ans = -1    # Default answer if impossible
for e in q: # BFS loop
    if len(e) == n: # If current string has desired length
        ans = d[e]  # Set answer to steps taken
        break       # Stop BFS
    x = int(e)      # Convert string back to integer
    for y in e:     # For each digit in current string
        s = str(x * int(y))  # Multiply x by digit y
        if s not in d:       # If result hasn't been seen
            d[s] = d[e] + 1  # Mark steps needed to reach s
            q += [s]         # Add s to queue for further exploration
print(ans)


# https://github.com/VaHiX/CodeForces/