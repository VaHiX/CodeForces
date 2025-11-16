# Problem: CF 1902 B - Getting Points
# https://codeforces.com/contest/1902/problem/B

"""
Code Purpose:
This solution computes the maximum number of days Monocarp can rest while still earning enough points to avoid being expelled.
The problem involves choosing between attending lessons (earning 'a' points) and completing practical tasks (earning 'b' points).
Tasks are unlocked weekly, starting from day 1, with 7-day intervals. On any given day, Monocarp can attend one lesson and complete at most 2 tasks.
We use a greedy strategy to determine the minimum number of days needed to earn 'p' points, then subtract this from total days 'n' to get the maximum rest days.

Algorithms/Techniques:
- Greedy algorithm with binary search or iterative checking
- Mathematical optimization to compute how many tasks and lessons are needed

Time Complexity: O(1) per test case - the logic uses a fixed number of operations regardless of input size
Space Complexity: O(1) - only a constant amount of extra space is used
"""

o = []
for i in range(int(input())):
    n, p, a, b = map(int, input().split())  # Read n (days), P (points needed), a (lesson points), b (task points)
    w = (n - 1) // 7 + 1  # Calculate total number of unlock weeks (tasks available)

    # If we can do everything in lessons and some tasks, use a greedy approach
    if p <= w * b + a * ((w // 2) + (w % 2)):
        # Estimate how many full study days are needed
        x = p // (b + (a // 2))
        # Check a few nearby values to find the minimal study days
        for i in range(x - 2, x + 3):
            # For i study days, compute max points achievable:
            # At most i/2 + i%2 tasks (each task gives 'a' points) and i lessons (each gives 'b' points)
            if p <= i * b + ((i // 2) + (i % 2)) * a:
                # Number of rest days = total days minus study days (rounded down to account for tasks)
                o.append(n - i // 2 - i % 2)
                break
    else:
        # If we must do more than the base lesson + max task strategy, compute remaining points after taking all lessons.
        p -= w * b
        # If remaining point requirement is exactly divisible by task points 'a'
        if p % a == 0:
            # Rest = total days - (lessons taken + tasks completed)
            o.append(n - p // a)
        else:
            # Otherwise, one additional day is needed to cover partial task
            o.append(n - p // a - 1)
print(*o, sep="\n")


# https://github.com/VaHiX/CodeForces/