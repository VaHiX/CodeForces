# Problem: CF 780 A - Andryusha and Socks
# https://codeforces.com/contest/780/problem/A

"""
Problem: Andryusha and Socks

Algorithm/Technique: Simulation with Hashing
- We simulate the process of taking socks from a bag and placing them appropriately.
- For each sock taken:
  - If its pair is not on the table, place it on the table.
  - If its pair is already on the table, remove both socks from the table and put them in the wardrobe.
- We maintain a count of socks on the table and track the maximum count at any time.

Time Complexity: O(n), where n is the number of pairs. Each element in the input array is processed once.
Space Complexity: O(n), for storing the state of pairs in the array `p`.

Input:
- First line: integer n (number of pairs)
- Second line: 2*n integers representing the order in which socks were taken

Output:
- Maximum number of socks present on the table at any time
"""

n = int(input())  # Read number of pairs
k = [int(i) for i in input().split()]  # Read the sequence of socks taken
p = [0] * n  # Array to track whether a pair's first sock is on the table (0 = not on table, 1 = on table)
c = 0  # Current count of socks on the table
mx = 0  # Maximum count of socks seen on the table

for i in range(2 * n):  # Process each sock in the sequence
    if p[k[i] - 1] == 0:  # If the pair has not been partially taken out
        c += 1  # Increment the count of socks on the table
        p[k[i] - 1] = 1  # Mark that the first sock of the pair is now on the table
    else:  # If the pair's first sock is already on the table
        mx = max(c, mx)  # Update the maximum if needed
        c -= 1  # Remove the pair from the table (decrement count)
        p[k[i] - 1] = 0  # Mark that the pair is now complete and removed

mx = max(c, mx)  # Final check: update maximum after the last operation
print(mx)  # Output the result


# https://github.com/VaHiX/CodeForces/