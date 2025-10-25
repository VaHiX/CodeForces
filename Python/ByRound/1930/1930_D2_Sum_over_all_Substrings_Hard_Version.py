# Problem: CF 1930 D2 - Sum over all Substrings (Hard Version)
# https://codeforces.com/contest/1930/problem/D2

"""
Purpose:
This code calculates the sum of f(p) over all substrings of a given binary string s.
f(p) is defined as the minimum number of 1s in a p-good binary string of the same length as p.
A p-good string is one where for every position i in pattern p, there exists a substring q[l:r+1] 
such that p[i] is the mode of that substring. A character c is the mode of a string if it appears 
at least ceil(m/2) times where m is the length of the string.

Algorithm:
The algorithm uses dynamic programming. It computes for each index i in the string s the contribution 
of all substrings ending at i to the final answer. It traverses the string from right to left and 
updates a DP array based on the character at position i.

Time Complexity: O(n)
Space Complexity: O(n)

The approach leverages the observation that for a substring of length m, the number of 1s needed 
in a good string is minimized by the properties of modal elements. The DP recurrence considers 
the effect of adding a character to previous substrings.

Key Insight:
For any substring, we only care about the minimal number of 1s required to make it good.
This problem can be optimized using a greedy approach and DP to efficiently compute the sum 
over all substrings.

"""

def calculate_sum_of_f(s):
    dp = [0] * (len(s) + 10)  # Create a DP array with extra padding
    for i in range(len(s) - 1, -1, -1):  # Traverse from right to left
        if s[i] == "1":  # If current character is '1'
            # Add contribution of 1s from the current position to end
            dp[i] = dp[i + 3] + len(s) - i  # Use dp[i+3] as offset
        else:
            # If current character is '0', no extra 1s needed from this point
            dp[i] = dp[i + 1]  # Propagate from next position
    return sum(dp)  # Return total sum of all contributions


testcases = range(int(input()))
for case in testcases:
    input()  # Read and discard the length n (not used)
    print(calculate_sum_of_f(input()))  # Process the string and output result


# https://github.com/VaHiX/CodeForces/