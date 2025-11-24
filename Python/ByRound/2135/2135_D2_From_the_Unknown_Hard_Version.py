# Problem: CF 2135 D2 - From the Unknown (Hard Version)
# https://codeforces.com/contest/2135/problem/D2

"""
D2. From the Unknown (Hard Version)

Purpose:
This code is an interactive solution to find an unknown integer W (the width of lines in a text editor) 
by querying articles and observing how many lines they take to display. The algorithm uses binary search 
with two queries, optimizing for minimal total length of words across queries.

Algorithms/Techniques:
- Binary search on the value of W
- Interactive problem solving with constraints on query word count
- Adaptive response handling based on editor display behavior

Time Complexity: O(log(10^5)) = O(17) since we do binary search in range [1, 10^5]
Space Complexity: O(1) - only using a constant amount of extra space regardless of input size

"""

K = 125
L = 25000 - K * K

for _ in range(int(input())):
    # First query: try to find an article that is too large (returns 0), or fits (returns > 0)
    print(f"? {L}" + f" {K}" * L)
    ans0 = int(input())
    
    if ans0 == 0:
        # Article was too large, so W < L
        # Second query: construct an article of size K*K and check how many lines it uses
        print(f"? {K*K}" + " 1" * (K * K))
        ans1 = int(input())
        
        if ans1 == K * K:
            # All words fit on one line => W >= K*K
            print("! 1")
        else:
            # We are looking for a divisor of K*K that matches the number of lines
            # We know: W <= K*K - 1, and W must be such that K*K // W = ans1
            for i in range(2, K):
                if (K * K + i - 1) // i == ans1:
                    print(f"! {i}")
    else:
        # Article was accepted with 'ans0' lines -> W >= (L / ans0)
        lft = K * ((L + ans0 - 1) // ans0)  # Lower bound for W
        rgt = min(10**5, K * (L // (ans0 - 1)) + K)  # Upper bound for W
        
        # Construct array to make second query with two parts: first part at lft, second part from (rgt - lft) down to 1
        arr = []
        for i in range(rgt - lft, 0, -1):
            arr.append(lft)
            arr.append(i)
            
        # Query with constructed article: use alternating values between lft and decreasing integers
        print(f"? {2*(rgt-lft)} " + " ".join(list(map(str, arr))))
        ans1 = int(input())
        
        # Output result using formula derived from previous bounds
        print(f"! {2*rgt-lft-ans1}")


# https://github.com/VaHiX/codeForces/