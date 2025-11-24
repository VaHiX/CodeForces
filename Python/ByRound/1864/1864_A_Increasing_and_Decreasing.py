# Problem: CF 1864 A - Increasing and Decreasing
# https://codeforces.com/contest/1864/problem/A

"""
Algorithm/Technique: Greedy Construction
Time Complexity: O(n)
Space Complexity: O(n)

This solution constructs a strictly increasing array where the differences between consecutive elements form a strictly decreasing sequence. 

The approach:
1. First, we calculate the minimum possible sum of differences: (n-1)*n/2. If the total difference (y - x) is less than this, it's impossible.
2. We build the array from the end (y), subtracting an increasing sequence of steps (1, 2, 3, ...) to ensure the difference sequence is strictly decreasing.
3. Finally, we reverse the array to get the correct order.

Key steps:
- Compute minimum sum of differences using arithmetic progression.
- Use a greedy approach to fill in values from right to left.
- Reverse the result to obtain the correct order.
"""

for _ in range(int(input())):
    x, y, n = list(map(int, input().split()))
    ap = int((n / 2) * (n - 1))  # Calculate minimum sum of differences (1 + 2 + ... + (n-1))
    if y - x < ap:               # If total difference is less than minimum possible, impossible
        print(-1)
        continue
    ans, c = [y], 1              # Start from y and keep track of step size
    n -= 1                       # Decrement n since we've placed one element
    while n > 1:                 # Fill array from right to left while there are more elements
        ans.append(ans[-1] - c)  # Subtract current step size from last value
        c += 1                   # Increase step size for next iteration
        n -= 1                   # Decrement remaining count
    ans.append(x)                # Add the starting value at the front
    ans = ans[::-1]              # Reverse to get the correct order
    print(" ".join(map(str, ans)))  # Print the array


# https://github.com/VaHiX/CodeForces/