# Problem: CF 2041 A - The Bento Box Adventure
# https://codeforces.com/contest/2041/problem/A

# =============================================================================
# Problem: Find the missing restaurant number from 1-5
# Algorithm: Calculate sum of visited restaurants and subtract from total sum
# Time Complexity: O(1) - constant time operations
# Space Complexity: O(1) - constant space usage
# =============================================================================

# Read input line and convert to integers, then calculate the missing number
# Total sum of restaurants 1+2+3+4+5 = 15
# Subtract the sum of visited restaurants from 15 to get the unvisited restaurant
print(15 - sum(map(int, input().split())))


# https://github.com/VaHiX/codeForces/