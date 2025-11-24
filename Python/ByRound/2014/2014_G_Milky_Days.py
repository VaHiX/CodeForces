# Problem: CF 2014 G - Milky Days
# https://codeforces.com/contest/2014/problem/G

"""
G. Milky Days
Algorithm: Simulation with a stack to track milk expiration and consumption.
Time Complexity: O(n * log(n)) due to stack operations per day.
Space Complexity: O(n) for the stack storing milk entries.

The problem simulates a process where:
- Milk is acquired on specific days and expires after k days.
- Each day, at most m pints of milk are consumed.
- Consumption prioritizes freshest milk first.
- A satisfaction day is one where exactly m pints are consumed.

Approach:
- Use a stack to maintain milk entries (day of expiry, amount).
- For each new milk entry:
  - Process previous entries that have expired or need consumption.
  - Add current milk entry to the stack.
- When processing, we calculate how much can be consumed daily and update stack accordingly.

This implementation uses a simulation approach with careful handling of
expiration times and prioritization using a stack.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m, k = map(int, input().split())
    S = 0  # Satisfaction days counter
    day = 0  # Current day tracking
    mon = []  # Stack to store (expiration_day, amount) of milk

    for q in range(n + 1):
        rem = 0  # Remaining milk from previous unprocessed entries
        if q < n:
            d, a = map(int, input().split())  # Day and amount of new milk
        else:
            d = int(1e9)  # Final fake day to process remaining milk
            a = 0

        # Process entries in the stack that are still valid before 'd'
        while mon and day < d:
            assert rem < m  # Ensure remainder is less than daily capacity
            exp, num = mon.pop()  # Get oldest milk entry (stack behavior)
            if day >= exp:
                continue  # Already expired

            num += rem  # Add previous remaining milk to current batch

            # Calculate how much we can consume from this milk batch
            mi = min(d - day, max(0, exp - day), num // m)

            S += mi  # Increment satisfaction days if we could fully consume
            day += mi  # Advance the day counter
            num -= m * mi  # Reduce total milk by what was consumed

            # If still not at target day, continue processing; else store remaining if any
            if day < d:
                if exp <= day:
                    continue  # This batch is already expired in this window
                if mon:
                    rem = num  # Save current milk for next iteration
                else:
                    break  # No more items to process
            else:
                if exp <= day:
                    continue  # Expired entry
                mon.append((exp, num))  # Put back the remaining milk

        # Add current batch of milk with its expiry time
        mon.append((d + k, a))
        day = d  # Update current day to new arrival day

    print(S)


# https://github.com/VaHiX/codeForces/