# Problem: CF 1710 B - Rain
# https://codeforces.com/contest/1710/problem/B

"""
Purpose: Determine which days, when erased, will prevent a flood from occurring in a harvesting field.

Algorithm:
- Use an event-based sweep line technique to compute the maximum accumulated rainfall at any point.
- For each rain event, we track how it affects the cumulative rainfall by creating events at start/end of influence.
- Sweep through events to calculate maximum height of the rain function.
- For each day, check if erasing it places the peak within safe bounds.

Time Complexity: O(n log n) due to sorting events.
Space Complexity: O(n) for storing events and intermediate results.
"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    rain = [tuple(map(int, input().split())) for i in range(n)]

    event = []
    # Prepare events for sweep line
    for x, p in rain:
        # Start of influence: (position, type, adjustment)
        event.append((x - p, 1, p - x))
        # Middle point: (position, type, adjustment)
        event.append((x, -2, 2 * x))
        # End of influence: (position, type, adjustment)
        event.append((x + p, 1, -p - x))
    event.sort()  # Sort events by position

    a, b = 0, 0  # Coefficients for line equation: y = ax + b
    S, D = -(10**17), -(10**17)  # Track max overshoot from left and right
    for x, c, d in event:
        tmp = a * x + b  # Current value at x
        if tmp > m:  # Check if current value exceeds threshold
            S = max(S, tmp - m + x)  # Compute left overshoot
            D = max(D, -m + tmp - x)  # Compute right overshoot
        a += c  # Update slope
        b += d  # Update y-intercept

    res = []
    for i in range(n):
        x, p = rain[i]
        # If removing this day's rain keeps the maximum within bounds
        if S <= p + x and D <= p - x:
            res.append("1")
        else:
            res.append("0")
    print("".join(res))


# https://github.com/VaHiX/CodeForces/