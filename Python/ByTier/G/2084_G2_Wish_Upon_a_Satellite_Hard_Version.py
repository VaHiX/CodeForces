# Problem: CF 2084 G2 - Wish Upon a Satellite (Hard Version)
# https://codeforces.com/contest/2084/problem/G2

# G2. Wish Upon a Satellite (Hard Version)
# Problem: Maximize the beauty of a permutation where beauty = sum of f(c) for all subsegments c
# Algorithm: Dynamic Programming with optimized state tracking
# Time Complexity: O(n^2) per test case in worst case, but with optimizations it's efficient enough for n <= 5 * 10^5
# Space Complexity: O(n) to store DP states

import random

random.seed()


def ril():
    return map(int, input().split())


T = int(input())
for _ in range(T):
    n = int(input())
    a = list(ril())
    loc = [-1] * (n + 1)
    for i, x in enumerate(a):
        if x > 0:
            loc[x] = i % 2  # Store whether each number appears at odd or even index
    oc = loc.count(1)   # Count of numbers placed at odd positions
    ec = loc.count(0)   # Count of numbers placed at even positions
    jmin = [n // 2] * (n + 1)
    jmax = [0] * (n + 1)
    oused = 0      # Count of numbers we've placed at odd indices when forced
    eused = 0      # Count of numbers we've placed at even indices when forced
    odd_count = 0  # Current count of numbers in odd positions from all placed numbers

    # First pass: determine how to assign the remaining elements for optimal DP state tracking
    for i in range(1, n + 1):
        if loc[i] == 0:
            pass       # Already assigned to even index
        elif loc[i] == 1:
            odd_count += 1  # Already assigned to odd index
        elif odd_count < i // 2:
            # Not enough odds yet - assign one more odd if there's room (but prefer not to use up reserved spaces)
            if oc + oused < n // 2:
                oused += 1
                odd_count += 1
            else:
                eused += 1   # Must place it on even index to preserve the parity balance
        else:
            # Already have more than required odds - prefer placing it on even index if possible
            if ec + eused < n - n // 2:
                eused += 1
            else:
                oused += 1   # Force it to odd place, increase odd count
                odd_count += 1

        k = 30  # Window adjustment for bounds
        jmin[i] = min(jmin[i], max(odd_count - k, 0))
        jmax[i] = max(jmax[i], min(odd_count + k, n // 2))
        jmax[i] = min(jmax[i], i)  # Ensure bounds

    assert ec + eused == n - n // 2  # Total even positions used
    assert oc + oused == odd_count == n // 2   # Total odd positions used

    jmin[0] = 0      # Base case for DP
    dp = [0]
    
    # Second pass: Dynamic Programming over indices and parity counts
    for i in range(1, n + 1):
        filled = n - i               # How many positions are left to fill (used in transition logic)
        ndp = [-float("inf")] * (jmax[i] - jmin[i] + 1)  # Current DP state: dp[odd count offset]

        for j in range(jmin[i], jmax[i] + 1):
            jj = j - jmin[i]     # Convert to array indices
            mode = 0             # Mode indicating where we place next element

            if loc[i] == 1:
                # Element already placed at odd index, can't place another at an even index in same group
                if j == 0:
                    continue     # This would violate constraints
                else:
                    mode = 1     # Assign to left of previous state (odd)
            if loc[i] == 0:
                # Element already placed at even index, can't place here if it would conflict
                if j == i:
                    continue     # Conflicting placement
                else:
                    mode = 2     # Must be even and allowed

            used_odd = n // 2 - j   # Number of odd slots filled in current state
            used_even = filled - used_odd  # Same for evens

            rem_even = i - j        # How many even slots remain from prefix up to this point

            # Transition 1: Try assigning element in an odd group (if allowed)
            if mode != 2 and jmin[i - 1] <= j - 1 <= jmax[i - 1]:
                odd_val = (j - 0) * i + used_even * i   # Value from placing item in odd slot
                ndp[jj] = max(ndp[jj], dp[j - 1 - jmin[i - 1]] + odd_val)

            # Transition 2: Try assigning element in an even group (if allowed)
            if mode != 1 and jmin[i - 1] <= j <= jmax[i - 1]:
                even_val = used_odd * i + (rem_even - 0) * i   # Value from placing item in even slot
                ndp[jj] = max(ndp[jj], dp[j - jmin[i - 1]] + even_val)

        dp = ndp

    print(dp[n // 2 - jmin[n]])   # Result for final parity state


# https://github.com/VaHiX/codeForces/