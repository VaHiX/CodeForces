# Problem: CF 1776 C - Library game
# https://codeforces.com/contest/1776/problem/C

"""
Library game solution using greedy strategy and adversarial game theory.

The problem involves two players (Alessia and Bernardo) playing a game with passes
and library sections. The goal is to determine who can guarantee a win based on
the initial setup.

Algorithms/Techniques:
- Greedy strategy to determine optimal play
- Adversarial game simulation with optimal responses
- Preprocessing of pass distribution to determine winning condition

Time Complexity: O(n^2 * m) in worst case due to nested loops for pass selection and
                 section marking, where n is number of passes and m is number of sections.
Space Complexity: O(m) for maintaining section availability status array.
"""

n, m = map(int, input().split())
A = list(map(int, input().split()))
A.sort(reverse=True)

for i in range(n):
    if A[i] * (i + 1) > m:
        win = A[i]
        break
else:
    win = 0

if win != 0:
    # Bernardo's strategy: Try to force a duplicate subject
    print("Bernardo")
    S = [0] * m
    # Mark sections that are multiples of the winning pass length
    for i in range(m):
        if (i + 1) % win == 0:
            S[i] = 1
    V = [0] * m  # Track taken sections
    for i in range(n):
        y, a = map(int, input().split())
        # Try to find already taken section in range
        for j in range(a - 1, a + y - 1):
            if V[j]:
                print(j + 1)
                break
        else:
            # If no taken section found, try to use marked section
            for k in range(a - 1, a + y - 1):
                if S[k]:
                    print(k + 1)
                    V[k] = 1
                    break
            else:
                # Default to first available section
                print(a)
                V[a - 1] = 1


else:
    # Alessia's strategy: Avoid duplicate subjects by ensuring each subject is used once
    print("Alessia")
    V = [0] * m  # Track taken sections
    for i in range(n):
        cur = 0
        # Count how many sections are taken in first A[i]-1 positions
        for j in range(A[i] - 1):
            if V[j]:
                cur += 1
        # Check each valid interval of length A[i]
        for j in range(m - A[i] + 1):
            # Check if the next section is taken
            if V[j + A[i] - 1]:
                cur += 1
            # If no sections are taken in current interval, choose it
            if cur == 0:
                print(A[i], j + 1)
                break
            # Remove the section that slides out of the window
            if V[j]:
                cur -= 1

        b = int(input())
        V[b - 1] = 1  # Mark the chosen section as taken


# https://github.com/VaHiX/CodeForces/