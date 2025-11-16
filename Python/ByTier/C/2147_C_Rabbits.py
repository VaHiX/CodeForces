# Problem: CF 2147 C - Rabbits
# https://codeforces.com/contest/2147/problem/C

"""
C. Rabbits
Algorithms/Techniques: Two-pointers, greedy
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves placing rabbits in empty pots (0s) such that no rabbit jumps into another rabbit or a pot already occupied.
We use a greedy approach to group consecutive 0s and check if it's possible to assign directions to avoid conflicts:
- For each segment of 0s, we ensure that the number of middle positions can be allocated properly based on parity
- If the segment contains only one 0, it is trivially valid
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    ans = "yEs"  # Assume answer is YES initially
    p = 0  # Start of current segment of zeros
    
    for i in range(1, n + 1):
        if i == n or s[i] == s[i - 1]:
            # End of a segment of same characters (0s or 1s)
            # Check if the segment is made of only 0s
            if s[p] == "1" and s[i - 1] == "1" and ((i - p) // 2) & 1:
                # Condition to determine invalidity:
                # If both ends of the group are '1' and number of positions in between is odd,
                # then it's impossible to resolve conflicts
                ans = "nO"
            p = i  # Move start pointer to next segment
    
    print(ans)


# https://github.com/VaHiX/CodeForces/