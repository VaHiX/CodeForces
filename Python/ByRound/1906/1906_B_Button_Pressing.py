# Problem: CF 1906 B - Button Pressing
# https://codeforces.com/contest/1906/problem/B

"""
Code Purpose:
This code determines whether it's possible to transform an initial lamp configuration (A) into a desired lamp configuration (B) using button presses. Each button toggles the state of adjacent lamps, but not its own lamp. The solution uses a function 'rankk' to compute a rank value for each configuration, which represents the number of "groups" or "segments" of consecutive lamps in the same state. The final decision is based on the parity (odd/even) of these rank values.

Algorithms/Techniques:
- Rank computation based on consecutive segments of '0' and '1'.
- Parity check for determining if transformation is possible.

Time Complexity:
- O(N) for each test case, where N is the number of lamps.
- Overall time complexity across all test cases is O(N) due to the constraint on sum of N.

Space Complexity:
- O(1) as only a few variables are used regardless of input size.
"""

def rankk(n, s):
    i = s.find("0")  # Find first occurrence of '0'
    if i == -1:
        return n  # All lamps are '1', so return total count
    j = s.find("1", i)  # Find first occurrence of '1' after i
    if j == -1:
        return i  # All lamps are '0', return count of '0's
    k = s.find("0", j)  # Find first '0' after j
    while True:
        if k == -1:  # No more '0's
            if (n - j) % 2:  # If the final segment is odd
                return n - j + i + 1  # Return modified rank
            else:
                return n - j + i  # Return modified rank
        if (k - j) % 2 == 0:  # If length of '1' segment is even
            i += k - j  # Move i forward
            j = s.find("1", k)  # Find next '1'
            if j == -1:
                return i  # Return remaining i
            k = s.find("0", j)  # Find next '0'
        else:  # If length of '1' segment is odd
            j2 = s.find("1", k)  # Find next '1' after k
            if j2 == -1:  # If no more '1's
                if (j - i) > (n - k):  # Compare lengths
                    j -= n - k
                    k = -1  # No more '0's
                elif (j - i) == (n - k):  # Equal lengths
                    return n
                else:  # If (j - i) < (n - k)
                    return k + (j - i)
            else:  # If there are more '1's
                if (j - i) > (j2 - k):  # Compare lengths
                    j -= j2 - k
                    k = s.find("0", j2)
                elif j - i == j2 - k:  # Equal lengths
                    i = s.find("0", j2)  # Move i
                    if i == -1:
                        return n  # No more '0's
                    j = s.find("1", i)  # Find next '1'
                    if j == -1:
                        return i
                    k = s.find("0", j)  # Find next '0'
                else:  # If (j - i) < (j2 - k)
                    i = k + (j - i)  # Adjust i
                    j = j2  # Move j
                    k = s.find("0", j2)  # Find next '0'


t = int(input())
for i in range(t):
    n = int(input())
    a, b = input(), input()
    # Compare the parity of rank values for initial and target configurations
    if (rankk(n, a) + 1) // 2 == (rankk(n, b) + 1) // 2:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/