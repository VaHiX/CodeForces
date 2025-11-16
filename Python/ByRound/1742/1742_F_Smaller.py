# Problem: CF 1742 F - Smaller
# https://codeforces.com/contest/1742/problem/F

"""
Problem: Determine if string s can be rearranged to be lexicographically smaller than string t after each operation.

Algorithm:
- We maintain counts of 'a' characters in both strings s and t
- We also maintain a flag to check if any non-'a' character is present in either string
- For each operation, we update the counts based on the input string x
- To determine if s can be smaller than t:
    - If t contains any non-'a' character, then we can always arrange s to be smaller (just put all 'a's in s and non-'a's in t)
    - If t only contains 'a's, but s also only contains 'a's and s length < t length, then s can be smaller
    - Otherwise, it's impossible

Time Complexity: O(sum of lengths of all x strings) - we process each character once
Space Complexity: O(1) - we only use fixed-size arrays of size 2
"""

for _ in range(int(input())):
    # ct[0] = count of 'a' in s, ct[1] = count of 'a' in t
    ct = [0] * 2
    # check[0] = whether s has any non-'a' character, check[1] = whether t has any non-'a' character
    check = [0] * 2
    
    for i in range(int(input())):
        q, f, x = input().split()  # q = operation type (1 or 2), f = repetition count, x = string to append
        f = int(f)
        q = int(q) - 1  # Convert to 0-based index

        # Update counts based on characters in x
        for i in x:
            if i == "a":
                ct[q] += f  # Increment count of 'a' in string q
            else:
                check[q] = 1  # Mark that string q contains non-'a' character

        # If t already has a non-'a' character, s can be made smaller
        if check[1]:
            print("YES")
            continue
        
        # If t only has 'a's and s only has 'a's, check if s can be made shorter
        if not check[0] and ct[0] < ct[1]:
            print("YES")
        else:
            print("NO")


# https://github.com/VaHiX/CodeForces/