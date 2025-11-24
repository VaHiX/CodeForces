# Problem: CF 2117 A - False Alarm
# https://codeforces.com/contest/2117/problem/A

# Problem: Determine if Yousef can pass through all doors given that he can use a special button once to open all closed doors for x seconds.

# Algorithm/Techniques:
# - Find the first and last closed door (represented by '1')
# - Calculate the distance between them
# - If this distance is <= x, then the button can cover the entire span of closed doors and the answer is "YES"
# - Time Complexity: O(n) per test case
# - Space Complexity: O(n) for storing the door states

for _ in range(int(input())):  # Read number of test cases
    n, x = map(int, input().split())  # Read n (number of doors) and x (button duration)
    a = input().split()  # Read the state of each door ('0' for open, '1' for closed)
    
    # Find index of first closed door (from start)
    first_closed = a.index("1")
    
    # Find index of last closed door (from end)
    last_closed = n - a[::-1].index("1") - 1
    
    # Check if the span between first and last closed door can be covered by the button
    # If the distance between first and last closed door is <= x, then it's possible
    print("YES" if last_closed - first_closed + 1 <= x else "NO")


# https://github.com/VaHiX/codeForces/