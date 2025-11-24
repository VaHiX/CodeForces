# Problem: CF 2072 B - Having Been a Treasurer in the Past, I Help Goblins Deceive
# https://codeforces.com/contest/2072/problem/B

# B. Having Been a Treasurer in the Past, I Help Goblins Deceive
# Time Complexity: O(n) for each test case, where n is the length of string s
# Space Complexity: O(1), only using a few variables for counting

# For each test case, read input and process the string to find maximum number of "-_-" subsequences
for s in [*open(0)][2::2]:  # Iterate over test cases (every 2nd line starting from index 2)
    d, m = map(s.count, "-_")  # Count '-' and '_' characters in the string
    print(d // 2 * (-~d // 2) * m)  # Calculate and print maximum subsequences


# https://github.com/VaHiX/codeForces/