// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
 * C. Divine Tree
 *
 * Problem Description:
 * Given n nodes and target sum m, construct a rooted tree such that the sum of "divineness" 
 * (minimum node label on path from root to node) equals m. Return the tree structure or -1 if impossible.
 *
 * Algorithm:
 * 1. Validity check: m must be between n (minimum possible sum) and n*(n+1)/2 (maximum).
 * 2. Greedily assign values to nodes in order of increasing depth:
 *    - At each step, pick the largest feasible value that keeps remaining sum achievable.
 * 3. Build edges by connecting parent to children based on traversal.
 *
 * Time Complexity: O(n log n) per test case (due to TreeSet operations)
 * Space Complexity: O(n) for storing nodes and result
 */

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val (n, m) = readln().split(' ').map { it.toLong() }
        print(solve(n, m))
    }
}

fun solve(n: Long, m: Long): String {
    // Check if target sum is possible
    if(m < n || m > (n * (n + 1) / 2)) {
        return "-1\n"
    }
    
    val nums = sortedSetOf<Long>() // TreeSet to efficiently find floor value
    val res = mutableListOf<Long>()
    var pos = 0
    var remainingSum = m
    var prevMin = Long.MAX_VALUE
    
    // Initialize with all node labels from 1 to n
    for(i in 1..n) nums.add(i.toLong())
    
    // Greedily assign values to nodes
    while(nums.isNotEmpty()) {
        // Find the largest number <= remainingSum - (nodesLeft)
        var curr = nums.floor(remainingSum - (n - pos - 1))
        if(curr == null) curr = nums.first()!! // Fallback to smallest if no good fit
        
        prevMin = minOf(prevMin, curr)
        remainingSum -= prevMin
        nums.remove(curr)
        res.add(curr)
        pos++
    }
    
    // Build output string: root + edges
    return buildString {
        append("${res[0]}\n")
        repeat(res.size - 1) {
            append("${res[it]} ${res[it + 1]}\n") // Connect each node to next in sequence
        }
    }
}


// https://github.com/VaHiX/CodeForces/