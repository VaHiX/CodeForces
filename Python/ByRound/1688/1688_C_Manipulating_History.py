# Problem: CF 1688 C - Manipulating History
# https://codeforces.com/contest/1688/problem/C

"""
Code Purpose:
This code solves the problem of reconstructing the initial string from a sequence of operations performed on it. 
The key insight is that each operation consists of a substring to be replaced (t_{2i-1}) and the replacement string (t_{2i}).
Since the operations are shuffled, we need to find the original string by reversing the process.
However, a simpler observation is that in the set of all strings in t and s, characters that appear an odd number of times
must be the ones that were not replaced, i.e., they are part of the original string.
Time Complexity: O(sum of lengths of all input strings)
Space Complexity: O(1) - since we use a fixed-size array of 26 characters
"""

for __ in range(int(input())):  # Process each test case
    n = 2 * int(input()) + 1  # Total number of strings in t plus final string s (n operations = 2*n strings in t, plus final string)
    a = [0 for i in range(26)]  # Array to count frequency of each character (a-z)
    
    for i in range(n):  # Read all 2*n + 1 strings (t_i)
        s = input()
        for c in s:  # For each character in the string
            a[ord(c) - ord("a")] += 1  # Increment count for that character
    
    cnt = 0  # Counter to track how many characters appear an odd number of times
    for i in range(26):  # Check each character from 'a' to 'z'
        if a[i] % 2 == 1:  # If character count is odd
            print(chr(i + ord("a")))  # Print the character
            cnt += 1  # Increment counter
    
    if cnt != 1:  # If not exactly one character appeared an odd number of times, the input is inconsistent
        print("fake problem")


# https://github.com/VaHiX/CodeForces/