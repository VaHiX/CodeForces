// Problem: CF 1910 F - Build Railway Stations
// https://codeforces.com/contest/1910/problem/F

/*
F. Build Railway Stations

Purpose:
This solution computes the minimum total travel time between all pairs of cities in a tree after placing at most k railway stations.
The algorithm uses DFS to compute subtree sizes, then evaluates which edges to convert (by placing stations) to minimize total cost.

Techniques:
- Tree DFS with subtree size calculation
- Greedy selection of edges to convert based on contribution to total cost

Time Complexity: O(n * log n) per testcase due to sorting of edges
Space Complexity: O(n) for graph storage, subtree sizes, and edge contributions

Input Format:
- First line contains t (number of test cases)
- Each test case starts with n (cities) and k (max stations)
- Then n - 1 lines describe the tree edges

Output:
- For each test case, minimum total travel time after optimally placing up to k stations
*/

fun main() {
    val t = readInt()
    repeat(t) {
        val (n, k) = readInts()
        val g = List(n) { mutableListOf<Int>() }
        for (i in 0 until n - 1) {
            val (x, y) = readInts()
            g[x - 1].add(y - 1) // Convert to 0-based indexing
            g[y - 1].add(x - 1)
        }
        val sz = IntArray(n)
        
        // DFS to compute subtree sizes for each node
        fun dfs(v: Int, pr: Int) {
            sz[v] = 1
            for (u in g[v]) {
                if (u != pr) { // Avoid going back to parent
                    dfs(u, v)
                    sz[v] += sz[u]
                }
            }
        }
        dfs(0, -1)
        
        val sub = LongArray(n - 1)
        var ans = 0L
        
        // For each edge (connecting node i and its parent), calculate the contribution
        for (i in 1 until n) {
            val cur = sz[i].toLong() * (n - sz[i]) // Number of paths crossing this edge
            ans += cur * 2 // Each path contributes 2 to total time in original tree
            sub[i - 1] = cur
        }
        
        // Sort edge contributions in descending order for greedy selection
        sub.sortDescending()
        
        // Subtract the largest k-1 contributions (we'll place stations to eliminate these)
        for (i in 0 until k - 1) {
            ans -= sub[i]
        }
        println(ans)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }


// https://github.com/VaHiX/codeForces/