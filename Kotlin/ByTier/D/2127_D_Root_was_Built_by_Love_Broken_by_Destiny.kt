// Problem: CF 2127 D - Root was Built by Love, Broken by Destiny
// https://codeforces.com/contest/2127/problem/D

/**
 * Problem: D. Root was Built by Love, Broken by Destiny
 *
 * Purpose:
 *   Given a connected graph with n nodes (houses) and m edges (bridges), determine how many valid
 *   arrangements of houses on two sides of a river exist such that each bridge connects nodes from
 *   different sides, and no two bridges cross when drawn as straight lines.
 *
 * Algorithm:
 *   1. The problem reduces to checking if the graph is a tree (since m = n - 1) or not.
 *   2. If m != n - 1, then it's not a tree and it’s impossible to arrange without crossing — return 0.
 *   3. For tree structure:
 *       a. Identify leaf nodes (degree = 1)
 *       b. Check if any internal node has degree > 2 → invalid arrangement (return 0)
 *       c. Count the number of internal nodes (non-leaves)
 *       d. Use combinatorics: for each internal node, multiply by factorial of its number of leaves.
 *       e. Multiply result by 2 due to choice of side assignment (north/south).
 *       f. Handle special case where there's more than one internal node → multiply by 2.
 *
 * Time Complexity:
 *   O(n + m) per test case, as we perform a single traversal of graph and operations on nodes.
 *
 * Space Complexity:
 *   O(n + m), to store adjacency lists and auxiliary arrays.
 */
const val MOD = 1000000007L

fun main() {
    val factorial = LongArray(200001) // Precompute factorials up to 200000!
    factorial[0] = 1L
    for (k in 1..200000) {
        factorial[k] = (k.toLong() * factorial[k - 1]) % MOD
    }
    repeat(readLine()!!.toInt()) {
        val (n, m) = readLine()!!.split(" ").map(String::toInt)
        if (m != n - 1) {
            // If not a tree, it's impossible to arrange without crossing bridges
            repeat(m) {
                readLine()
            }
            println(0)
        } else {
            val adj = Array(n + 1) { mutableListOf<Int>() }
            repeat(n - 1) {
                val (a, b) = readLine()!!.split(" ").map(String::toInt)
                adj[a].add(b)
                adj[b].add(a)
            }
            val leaf = BooleanArray(n + 1) { adj[it].size == 1 }
            // Detect invalid internal nodes with degree > 2
            if ((1..n).any { adj[it].count { !leaf[it] } > 2 }) {
                println(0)
            } else {
                var answer = 2L * if ((1..n).count { !leaf[it] } > 1) 2L else 1L
                // Multiply by factorial of leaf counts for each node
                for (a in 1..n) {
                    answer *= factorial[adj[a].count { leaf[it] }]
                    answer %= MOD
                }
                println(answer)
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/