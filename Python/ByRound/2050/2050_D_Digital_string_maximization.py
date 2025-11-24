# Problem: CF 2050 D - Digital string maximization
# https://codeforces.com/contest/2050/problem/D

"""
Algorithm: Greedy approach with sliding window
Time Complexity: O(n), where n is the length of the string
Space Complexity: O(n), due to the deque and list storage

This solution attempts to maximize the lexicographically ordered string by 
greedily selecting the best digit at each step from a sliding window of size 10.
It maintains a deque of up to 10 digits and repeatedly picks the optimal digit,
then shifts the window forward.
"""

def max_nums_str():
    from collections import deque

    t = int(input())
    for _ in range(t):
        st = [int(x) for x in input()]  # Convert input string to list of integers
        dk = deque()  # Sliding window of at most 10 elements
        for i in range(0, min(10, len(st))):  # Initialize deque with first 10 or fewer digits
            dk.append(st[i])
        out = ""  # Result string being built
        l = 10  # Index of next digit to add from original string
        while dk:  # While there are digits left in the deque
            mx = dk[0]  # Initialize max digit with first in deque
            ind = 0  # Index of the best digit
            # Search for the best digit in the sliding window
            for i in range(1, min(10, len(dk))):
                # Compare dk[i] - i with current max
                # This is a heuristic to determine the best digit to take
                if dk[i] - i > mx:
                    mx = dk[i] - i
                    ind = i
            out += str(mx)  # Append max digit to result
            dk.remove(dk[ind])  # Remove the selected digit
            if l < len(st):  # If more digits in original string, add next one
                dk.append(st[l])
            l += 1  # Move to next digit in original string
        print(out)


max_nums_str()


# https://github.com/VaHiX/CodeForces/