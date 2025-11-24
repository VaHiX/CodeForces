# Problem: CF 1675 E - Replace With the Previous, Minimize
# https://codeforces.com/contest/1675/problem/E
 
"""
Algorithm: Greedy Optimization
Techniques: 
- Greedy choice: Always try to minimize the lexicographical value of the string
- Cost Tracking: For each character, compute how many operations are needed to reduce it to 'a'
- Loop Reduction: Process characters from right to left to make minimal changes with least operations
 
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) as we use a fixed-size array of size 27 (0-26)
"""
for _ in range(int(input())):
    k = int(input().split()[1])  # Read k (max operations)
    cost = [float("inf")] + [1] * 26  # cost[i] = operations to reduce 'a'+i to 'a'
    for x in input():  # Process each character
        x = ord(x) - ord("a")  # Convert char to index (0-25)
        while k >= cost[x]:  # If we have enough operations to reduce char x to previous
            k -= cost[x]  # Use those operations
            cost[x] = 0   # Mark that this character is fully reduced
            x -= 1        # Move to the previous character in alphabet
        print(chr(ord("a") + x), end="")  # Output the minimized character
    print()  # New line after each test case
 
 
# https://github.com/VaHiX/CodeForces/