# Problem: CF 782 A - Andryusha and Socks
# https://codeforces.com/contest/782/problem/A

"""
Algorithm: Simulation with Set
Purpose: To find the maximum number of socks on the table at any time during the process of taking socks from a bag and putting pairs into the wardrobe.

Approach:
- Traverse the list of socks taken out from the bag in order.
- Use a set to track which sock pairs are currently on the table.
- When a sock is taken:
  - If its pair is not on the table, add it to the set (put on the table).
  - If its pair is already on the table, remove the pair from the set (put into wardrobe).
- Track the maximum size of the set during the process.

Time Complexity: O(n), where n is the number of pairs. Each sock is processed once, and set operations take O(1) average time.
Space Complexity: O(n), for storing the set of active sock pairs.
"""

n = int(input())
s = list(map(int, input().split()))
s_t = set()  # Set to keep track of sock pairs currently on the table
len_s_t = 0  # Maximum number of socks on the table at any time

for i in range(2 * n):  # Process each sock in order
    if s[i] not in s_t:  # If the pair of this sock is not on the table
        s_t.add(s[i])  # Add this sock to the table
    else:  # If the pair of this sock is already on the table
        s_t.remove(s[i])  # Remove the pair from the table (put into wardrobe)
    
    # Update the maximum number of socks on the table
    if len(s_t) > len_s_t:
        len_s_t = len(s_t)

print(len_s_t)


# https://github.com/VaHiX/CodeForces/