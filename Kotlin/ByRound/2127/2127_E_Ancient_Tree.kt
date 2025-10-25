// Problem: CF 2127 E - Ancient Tree
// https://codeforces.com/contest/2127/problem/E

/*
 * Problem: E. Ancient Tree
 * Purpose: Assign colors to vertices of a tree to minimize the sum of weights of "cutie" vertices.
 *          A vertex is cutie if there exist two nodes x and y such that:
 *          - Their LCA is the vertex,
 *          - They have the same color,
 *          - But that color differs from the color of the LCA node.
 *
 * Algorithms/Techniques:
 * - Tree rooting and DFS traversal
 * - Color merging using sets to detect duplicate colors in subtrees
 * - Greedy assignment of colors during DFS to minimize cost
 *
 * Time Complexity: O(n * k) per test case, where n is number of vertices and k is number of colors.
 * Space Complexity: O(n + k) for storing tree structure, recursion stack, and auxiliary data structures.
 */

import kotlin.math.max
import kotlin.math.min

fun main() {
    val out = StringBuilder()
    repeat(readLine()!!.toInt()) {
        val (n, k) = readLine()!!.split(" ").map(String::toInt)
        val weights = listOf(0L) + readLine()!!.split(" ").map(String::toLong)
        val colors = (listOf(0) + readLine()!!.split(" ").map(String::toInt)).toIntArray()
        val adj = Array(n + 1) { mutableListOf<Int>() }
        repeat(n - 1) {
            val (a, b) = readLine()!!.split(" ").map(String::toInt)
            adj[a].add(b)
            adj[b].add(a)
        }
        
        // Convert tree to rooted tree by removing parent links
        fun root(a: Int) {
            for (b in adj[a]) {
                adj[b].remove(a)
                root(b)
            }
        }
        root(1)
        
        var answer = 0L
        
        // DFS function to process subtree and assign colors greedily
        fun colorUp(a: Int): MutableSet<Int> {
            var colorsInSubtree = mutableSetOf<Int>()
            var minDuplicate = Int.MAX_VALUE
            var maxDuplicate = 0
            
            // Recursively process all children
            for (b in adj[a]) {
                var below = colorUp(b)
                // Optimize by always making 'below' the smaller set
                if (below.size > colorsInSubtree.size) {
                    val temp = below
                    below = colorsInSubtree
                    colorsInSubtree = temp
                }
                
                // Find common colors between current subtree and processed children
                for (c in below) {
                    if (!colorsInSubtree.add(c)) {
                        minDuplicate = min(minDuplicate, c)
                        maxDuplicate = max(maxDuplicate, c)
                    }
                }
            }
            
            // If duplicate color found in subtree, vertex 'a' is cutie
            if (maxDuplicate != 0) {
                if (colors[a] == 0)  {
                    colors[a] = maxDuplicate  // Assign one of duplicates to avoid penalty
                }
                if (colors[a] != minDuplicate || colors[a] != maxDuplicate) {
                    answer += weights[a]  // Add weight of cutie node to total cost
                }
            }
            
            // Add color of current vertex to set if it has a color
            if (colors[a] != 0) {
                colorsInSubtree.add(colors[a])
            }
            return colorsInSubtree
        }
        
        colorUp(1)
        
        // DFS function to propagate colors from root down to leaves
        fun colorDown(a: Int, c: Int) {
            if (colors[a] == 0) {
                colors[a] = c
            }
            for (b in adj[a]) {
                colorDown(b, colors[a])
            }
        }
        
        colorDown(1, 1)
        
        out.appendLine(answer)
        out.appendLine(colors.toList().subList(1, n + 1).joinToString(" "))
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/