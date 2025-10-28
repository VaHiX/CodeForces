// Problem: CF 2113 F - Two Arrays
// https://codeforces.com/contest/2113/problem/F

/*
F. Two Arrays

Algorithms/Techniques:
- Graph construction based on element mappings between arrays a and b
- Depth-first search (DFS) to process connected components in the graph
- Greedy assignment of elements to maximize distinct values in both arrays

Time Complexity: O(n)
Space Complexity: O(n)

Problem:
Given two arrays a and b of length n, we can swap elements at the same indices.
We want to maximize f(a) + f(b), where f(c) is the number of distinct elements in array c.

Approach:
1. Build a graph by connecting each pair (a[i], b[i]) with an edge.
2. Use DFS to find connected components.
3. For each component, assign values greedily to avoid duplication and try to maximize distinct elements in both arrays.
4. Track assignments using ans array to keep track of which value was assigned to a[i].
*/

import java.util.*

const val maxn = 400005 

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt() 
    repeat(t) {
        solve(scanner)
    }
}

data class Edge(val v: Int, val id: Int, var nxt: Int)

var idx = 0 
var rt = 0  
val head = IntArray(maxn) 
val vis1 = IntArray(maxn) 
val vis2 = IntArray(maxn) 
val a = IntArray(maxn)    
val b = IntArray(maxn)    
val ans = IntArray(maxn)  
val e = Array(maxn * 4) { Edge(0, 0, 0) } 

// Add directed edge from u to v
fun adde(u: Int, v: Int, id: Int) {
    e[++idx] = Edge(v, id, head[u]) 
    head[u] = idx                    
}

// First DFS traversal for component processing
fun dfs1(u: Int) {
    vis1[u] = 1 
    var i = head[u]
    while (i != 0) { 
        val v = e[i].v
        val id = e[i].id
        if (vis2[id] == 0) { 
            vis2[id] = 1     
            ans[id] = u      
            if (vis1[v] == 0) { 
                dfs1(v)         
            }
        }
        i = e[i].nxt 
    }
}

// Second DFS traversal for handling cycles
fun dfs2(u: Int) {
    vis1[u] = 2 
    var i = head[u]
    while (i != 0) { 
        val v = e[i].v
        val id = e[i].id
        if (v != rt && vis2[id] != 2) { 
            vis2[id] = 2                 
            ans[id] = v                  
            if (vis1[v] == 1) {          
                dfs2(v)                 
            }
        }
        i = e[i].nxt 
    }
}

fun solve(scanner: Scanner) {
    val n = scanner.nextInt()
    idx = 0
    Arrays.fill(head, 0, 2 * n + 5, 0) 
    Arrays.fill(vis1, 0, 2 * n + 5, 0) 
    Arrays.fill(vis2, 0, 2 * n + 5, 0) 
    val valArr = IntArray(2 * n + 5)   // count of occurrences for each value
    
    // Read and count frequencies
    for (i in 1..n) {
        a[i] = scanner.nextInt()
        valArr[a[i]]++ 
    }
    for (i in 1..n) {
        b[i] = scanner.nextInt()
        valArr[b[i]]++ 
    }
    
    // Build the graph
    for (i in 1..n) {
        adde(a[i], b[i], i) 
        adde(b[i], a[i], i) 
    }
    
    var tmp = 0
    
    // Process each connected component
    for (u in 1..2 * n) {
        tmp += minOf(2, valArr[u]) // Sum of minimum of 2 and frequency for a value
        
        if (vis1[u] == 0) {        
            dfs1(u)                // Start DFS from node u
            
            var fl = false
            var i = head[u]
            
            // Check if all edges point to same node as root
            while (i != 0) {
                if (ans[e[i].id] != u) {
                    fl = true
                    break
                }
                i = e[i].nxt
            }
            
            // If it's a cycle, special handling is necessary
            if (!fl && head[u] != 0) {
                rt = u
                ans[e[head[u]].id] = e[head[u]].v
                dfs2(e[head[u]].v)
            }
        }
    }
    
    println(tmp) 
    
    // Print final array a
    for (i in 1..n) {
        print("${ans[i]} ") 
    }
    println()
    
    // Print final array b (which is sum of a and b minus answer assignment)
    for (i in 1..n) {
        print("${a[i] + b[i] - ans[i]} ") 
    }
    println()
}


// https://github.com/VaHiX/CodeForces/