# Problem: CF 2092 D - Mishkin Energizer
# https://codeforces.com/contest/2092/problem/D

# Problem: Make a string of 'L', 'I', 'T' balanced by inserting characters
# Algorithm: Greedily find transitions and insert a character different from both neighbors to balance counts
# Time Complexity: O(n^2) in worst case due to potential insertions and reprocessing
# Space Complexity: O(n) for storing the result list

for _ in range(int(input())):
    n = int(input())
    s = input()
    res = []
    pre = n  # Tracks the last processed position
    
    # Traverse string from right to left to find transitions
    for i in range(n - 1, 0, -1):
        if s[i] == s[i - 1]:
            continue  # Skip if characters are same
        
        # Extend result with positions for insertion
        res.extend([i + j for j in range(2 * (pre - i))])
        pre = i  # Update last processed index
    
    # If no transition was found, string is uniform and can't be made balanced
    if pre == n:
        print(-1)
    else:
        # Add final operations to balance the string
        res.extend([pre] * (2 * pre))
        print(2 * n)
        print(*res, sep="\n")


# https://github.com/VaHiX/codeForces/