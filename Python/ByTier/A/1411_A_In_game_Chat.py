# Problem: CF 1411 A - In-game Chat
# https://codeforces.com/contest/1411/problem/A

# Problem: In-game Chat
# Algorithm: String manipulation and comparison
# Time Complexity: O(n) where n is the length of the string (for each test case)
# Space Complexity: O(1) - only using a constant amount of extra space

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of string
    s = input().rstrip(")")    # Remove all trailing ')' characters from string
    # Compare remaining length with count of removed ')' characters
    ans = n - len(s) > len(s)  # If more ')' characters than remaining chars, message is bad
    print("Yes" if ans else "No")  # Print result


# https://github.com/VaHiX/codeForces/