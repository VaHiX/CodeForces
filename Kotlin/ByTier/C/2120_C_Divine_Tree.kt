// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
C. Divine Tree

Purpose:
This program constructs a rooted tree with n nodes such that the sum of divineness across all nodes equals m.
The divineness d(v) of a node v is defined as the smallest label on the path from root to v.

Algorithm:
- First check if solution is possible: m must be between n and n*(n+1)/2
- Use a greedy approach with a sorted set to construct tree by selecting nodes in order
- Each node's divineness is its own label (since it's on the path from root to itself)
- Assign labels greedily to minimize total sum while satisfying constraints

Time Complexity: O(n log n) per test case due to SortedSet operations
Space Complexity: O(n) for storing nodes and result

Input Format:
- First line contains number of test cases t
- Each test case has two integers n and m

Output Format:
- If impossible, print "-1"
- Otherwise, print root followed by n-1 edges in any valid format
*/

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val (n, m) = readln().split(' ').map { it.toLong() }
        print(solve(n, m))
    }
}

fun solve(n: Long, m: Long): String {
    // Check if solution is impossible:
    // Minimum possible sum is n (each node contributes at least 1)
    // Maximum possible sum is n*(n+1)/2 (when tree is a path and labels are 1..n)
    if(m < n || m > (n * (n + 1) / 2)) {
        return "-1\n"
    }
    
    val nums = sortedSetOf<Long>() // Maintains available nodes in sorted order
    val res = mutableListOf<Long>()
    var pos = 0
    var remainingSum = m
    var prevMin = Long.MAX_VALUE
    
    // Initialize with all node labels 1 to n
    for(i in 1..n) nums.add(i.toLong())
    
    // Greedily assign values to ensure sum equals m
    while(nums.isNotEmpty()) {
        // Find largest value <= remainingSum - (number of remaining nodes)
        var curr = nums.floor(remainingSum - (n - pos - 1))
        if(curr == null) curr = nums.first()!! // If no such element, take smallest
        prevMin = minOf(prevMin, curr)
        remainingSum -= prevMin
        nums.remove(curr) // Remove used value
        res.add(curr)
        pos++
    }
    
    // Build output string
    return buildString {
        append("${res[0]}\n") // Root is first element
        repeat(res.size - 1) {
            append("${res[it]} ${res[it + 1]}\n") // Connect adjacent elements in sequence
        }
    }
}


// https://github.com/VaHiX/CodeForces/