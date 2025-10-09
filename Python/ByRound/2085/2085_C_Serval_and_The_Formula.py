# Problem: CF 2085 C - Serval and The Formula
# https://codeforces.com/contest/2085/problem/C

# C. Serval and The Formula
# Task: For given x and y, find k such that (x + k) + (y + k) == (x + k) ^ (y + k)
# Algorithm:
#   - If x == y, then k = 0 works because (x + 0) + (x + 0) = 2*x and (x + 0) ^ (x + 0) = 0,
#     but 2*x != 0 unless x = 0 which is not allowed. However, let's simplify:
#     If x == y, the equation becomes 2*(x + k) == 0, so k must be -x which can't be non-negative.
#     But actually, if x == y, the simplified case allows any k = 0 to work, because
#     (x + 0) + (x + 0) = 2*x and (x + 0) ^ (x + 0) = 0. So only when x = 0.
#     Since input constraints say x, y >= 1, we need to evaluate k = 0 directly:
#     For x == y => (x + 0) + (y + 0) = 2*x and (x + 0) ^ (y + 0) = 0,
#     so 2*x = 0 implies x = 0 - contradiction.
#     Let's look at logic correctly:
#     We can use bit manipulation property that a + b == a ^ b + 2 * (a & b)
#     So for the equation (x+k)+(y+k) == (x+k)^(y+k), 
#     using identity: (x+k) + (y+k) = (x+k) ^ (y+k) + 2 * ((x+k) & (y+k))
#     Hence we must have 2*((x+k) & (y+k)) = 0
#     This means (x+k)&(y+k)=0, i.e., x+k and y+k are disjoint in binary.
#     If x == y, then k=0 works only if 2*x = 0 => x=0 contradiction again. So output -1,
#     but actually this is a special case that's already handled in implementation.
#
#   Key insight to solve efficiently:
#   - Try k = (x ^ y) >> 1, which is the most likely solution.
#   - For x != y, if k = 2^48 - max(x,y) is used as fallback when x == y,
#     and for x == y, it's forced to return -1 using the condition (-(x == y) or ...).
#
# Time Complexity: O(1)
# Space Complexity: O(1)

for l in [*open(0)][1:]:  # Read all lines from input except first (which is number of test cases)
    x, y = map(int, l.split())  # Parse two integers x and y
    print(-(x == y) or 2**48 - max(x, y))  # Logic to compute k, returns -1 if x == y, otherwise computes k using formula


# https://github.com/VaHiX/codeForces/