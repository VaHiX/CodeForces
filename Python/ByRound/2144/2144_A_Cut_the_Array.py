# Problem: CF 2144 A - Cut the Array
# https://codeforces.com/contest/2144/problem/A

# =============================================================================
# Problem: Cut the Array
# Description: Given an array of non-negative integers, split it into three non-empty parts
#              such that either all three remainder sums (mod 3) are equal,
#              or all three remainder sums are different.
# Algorithm: Brute-force search for valid l and r indices.
# Time Complexity: O(n^3) where n is the length of the array.
# Space Complexity: O(1), only using a constant amount of space.
# =============================================================================

i = input
for _ in range(int(i())):  # Read number of test cases
    n = int(i())  # Read array length
    a = list(map(int, i().split()))  # Read the array elements
    
    found = False  # Flag to check if valid split is found
    
    # Try all possible combinations of l and r (prefix and middle part boundaries)
    for l in range(1, n - 1):  # l must be less than r and both < n
        for r in range(l + 1, n):  # r must be greater than l and < n
            # Calculate sum of prefix from index 0 to l-1 (inclusive)
            s1 = sum(a[:l]) % 3
            
            # Calculate sum of middle part from index l to r-1 (inclusive)
            s2 = sum(a[l:r]) % 3
            
            # Calculate sum of suffix from index r to n-1 (inclusive)
            s3 = sum(a[r:]) % 3
            
            # Check if all remainders are same or all are different
            if s1 == s2 == s3 or len(set([s1, s2, s3])) == 3:
                print(l, r)
                found = True
                break
        if found:
            break
    
    # If no valid split found, print "0 0"
    if not found:
        print("0 0")


# https://github.com/VaHiX/codeForces/