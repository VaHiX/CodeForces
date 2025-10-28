# Problem: CF 1930 D1 - Sum over all Substrings (Easy Version)
# https://codeforces.com/contest/1930/problem/D1

"""
Algorithm/Technique: Dynamic Programming with Greedy Approach

Purpose:
This code computes the sum of f(p) over all substrings of a given binary string s.
f(p) is defined as the minimum number of 1s in a p-good binary string of the same length as p.
A p-good string is one where for every position i in the pattern p, there exists a substring 
in the string q such that p[i] is a mode (appears at least half the time, rounded up) of that substring.

Time Complexity: O(n^3)
Space Complexity: O(1)

The function `f(s)` computes f(p) for a given pattern p. It greedily tries to assign 1s to ensure 
that each position in the pattern can have a mode. It uses a greedy strategy to minimize the number of 1s needed.

The outer loop iterates over all substrings of s, and for each substring, it calls f() to compute f(p), 
where p is the substring. This leads to O(n^3) due to nested loops (n^2 substrings, and each f() call is O(n)).

"""

def f(s):
    count = 0
    needed_next_turn = False  # Indicates if we are waiting for a 1 to cover a pending mode requirement
    provided_from_last_turn = False  # Indicates if a 1 was provided in the last step
    for c in s:
        if needed_next_turn:
            # If we are waiting for a 1 to fulfill a requirement, place one now
            count += 1
            provided_from_last_turn = True
            needed_next_turn = False
        else:
            # If we don't need a 1, check if a 1 is required at this position
            if c == 1 and not provided_from_last_turn:
                needed_next_turn = True  # Mark that a 1 is needed ahead to satisfy mode condition
            provided_from_last_turn = False  # No 1 was placed in this step
    if needed_next_turn:
        # If the pattern ends with a pending requirement, fulfill it
        count += 1
    return count


t = int(input())
for _ in range(t):
    n = int(input())
    numbers = list(map(int, input()))  # Convert input string to list of integers
    count = 0
    # Generate all substrings and compute f for each
    for i in range(n):
        for j in range(i, n):
            count += f(numbers[i : j + 1])  # Call f on each substring
    print(count)


# https://github.com/VaHiX/CodeForces/