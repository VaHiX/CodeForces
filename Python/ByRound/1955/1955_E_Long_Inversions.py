# Problem: CF 1955 E - Long Inversions
# https://codeforces.com/contest/1955/problem/E

"""
Algorithm: 
This code attempts to find the maximum value of k such that we can make all characters in the string equal to '1' 
by inverting k consecutive characters any number of times. 

The core idea is to check for each possible k (from n down to 1), whether it's valid. 
A k is valid if, when we process the string in chunks of size k (starting from each index 0 to k-1), 
the number of 0s in each such chunk (when processed from left to right) results in a consistent parity of flips needed to make everything 1.

For each k:
- Divide the string into groups of k elements, starting at indices 0, 1, ..., k-1
- For each group, calculate how many 0s it contains (after considering any previous flip operations)
- If at any point, two groups require different parity of flips, then k is invalid

Time Complexity: O(n^2), in worst case, for each k we check all positions up to n
Space Complexity: O(n), due to string slicing and temporary storage
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    ans = 0
    for i in range(n, 0, -1):  # Iterate from n down to 1
        z = -1  # Initialize variable to store flip parity for current k
        for j in range(i):  # Process each starting position from 0 to i-1
            x = 0  # Count of 0s in current group (after applying flip operations)
            s1 = s[j::i]  # Slice string starting at index j, step size i
            for k in s1:  # Count how many '0' in each group
                if k == "0":
                    x ^= 1  # XOR to flip parity (odd = 1, even = 0)
            if z != -1 and z != x:  # If previous group required different parity 
                z = -2  # Mark invalid
                break
            z = x  # Store parity of current group
        if z != -2:  # If valid for this k
            ans = i  # Update answer
            break
    print(ans)


# https://github.com/VaHiX/CodeForces/