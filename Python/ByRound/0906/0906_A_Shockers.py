# Problem: CF 906 A - Shockers
# https://codeforces.com/contest/906/problem/A

"""
Algorithm: Greedy Simulation with Set Operations
Purpose: Determine the number of excessive electric shocks Valentin received
         by simulating his actions and identifying when the selected letter
         becomes uniquely determined.

Time Complexity: O(n * L) where n is number of actions and L is average word length
Space Complexity: O(1) since we use a fixed-size set of 26 letters

Approach:
1. Maintain a set of possible letters that could be the selected letter
2. For each action:
   - If it's a shock (start with '!'), remove letters not in that word from possible set
   - If it's no shock (start with '.'), remove letters in that word from possible set
3. When only one letter remains in set, that's the selected letter
4. Count all shocks after this point (these are the excessive shocks)

The key optimization is that we only need to track which letters are possible
and we stop counting excessive shocks as soon as we know the final letter.
"""

import sys

input = sys.stdin.readline

n = int(input())
q = {chr(i) for i in range(97, 123)}  # Initialize set with all lowercase letters
c = 0  # Count of excessive shocks
t = "0"  # Flag to indicate if we've determined the letter yet

for i in range(n - 1):  # Process all actions except the final guess
    s = input()[:-1]  # Read input line and remove newline
    
    if t == "0":  # If we haven't determined the selected letter yet
        if s[0] == "!":  # If this was a shock (word contained the selected letter)
            # Intersect our possible set with letters in this word
            s = set(s[2:])  # Extract word after "! "
            q &= s  # Set intersection
        else:  # If no shock (word did not contain selected letter)
            # Remove letters in this word from our possible set
            for j in set(s[2:]):  # Iterate through unique letters in word
                if j in q:  # If letter is still possible
                    q.remove(j)  # Remove it from set of possible letters
        
        # Check if we've uniquely determined the letter
        if len(q) == 1:
            t = q.pop()  # Set flag and store the determined letter
    else:  # If we've already determined the letter
        # Count any shock or guess after that point as excessive
        if s[0] in "!?":  # If it's a shock or a guess
            c += 1  # Increment excessive shock counter

print(c)  # Output the number of excessive shocks


# https://github.com/VaHiX/CodeForces/