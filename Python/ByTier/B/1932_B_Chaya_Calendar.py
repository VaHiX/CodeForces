# Problem: CF 1932 B - Chaya Calendar
# https://codeforces.com/contest/1932/problem/B

"""
Purpose: 
    This code determines the year when the nth apocalyptic sign occurs,
    given that each sign appears periodically and must follow sequentially.
    The algorithm calculates the cumulative timing of signs, ensuring that 
    each subsequent sign appears strictly after the previous one.

Algorithm/Techniques:
    - Greedy approach with modular arithmetic
    - For each sign, calculate the next occurrence after the current time (ap)
    - Use modular arithmetic to find the next valid year for the sign

Time Complexity: O(n), where n is the number of signs. We iterate through the signs once.
Space Complexity: O(1), as we use only a constant amount of extra space.

"""

def solve(n, signs):
    # Initialize the time to the first sign's occurrence
    ap = signs[0]
    # Iterate through the remaining signs
    for i in range(1, n):
        # Calculate the next occurrence of the current sign after time 'ap'
        # ap % signs[i] gives how many years have passed since the last occurrence of this sign
        # signs[i] - (ap % signs[i]) gives the years to wait until the next occurrence
        ap += signs[i] - (ap % signs[i])
    return ap


T = int(input())
for _ in range(T):
    n = int(input())
    signs = list(map(int, input().split()))
    print(solve(n, signs))


# https://github.com/VaHiX/CodeForces/