# Problem: CF 2108 C - Neo's Escape
# https://codeforces.com/contest/2108/problem/C

"""
C. Neo's Escape

Algorithm/Technique: 
    - Identify peaks in a flattened sequence of unique elements
    - The minimum number of clones needed equals the number of peaks in the modified array
    - This resembles the "peak counting" problem in a sequence where we need to find local maxima
    - We first remove consecutive duplicates and add sentinel 0s at both ends
    - Then count how many elements are greater than their immediate neighbors (local maxima)

Time Complexity: O(n), where n is the length of input array.
Space Complexity: O(n), for storing the modified array 'nl'.

"""

for _ in range(int(input())):  # Process multiple test cases
    n = int(input())            # Read number of buttons
    l = list(map(int, input().split()))  # Read weights of buttons
    
    nl = [0]                    # Initialize modified list with a sentinel 0 at start
    
    # Remove consecutive duplicates and build the modified list `nl`
    for i in range(n):
        if l[i] != nl[-1]:      # Only add element if it's different from last added
            nl.append(l[i])
    
    nl.append(0)                # Add a sentinel 0 at end
    
    answer = 0                  # Counter for number of peaks
    
    # Count the number of local maxima (peaks) in the modified list
    for i in range(len(nl)):
        if nl[i] > nl[i - 1] and nl[i] > nl[i + 1]:  # Check if current element is a peak
            answer += 1
    
    print(answer)  # Output the minimum number of clones needed


# https://github.com/VaHiX/codeForces/