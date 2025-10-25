// Problem: CF 2122 D - Traffic Lights
// https://codeforces.com/contest/2122/problem/D

/*
 * Problem: D. Traffic Lights
 * 
 * Purpose:
 * This code finds the minimum total time and minimum waiting time to move a token from vertex 1 to vertex n
 * in an undirected graph, following specific movement rules based on edge order and time.
 *
 * Algorithms/Techniques:
 * - Multi-source BFS with state tracking for both time and waiting time
 * - Simulation of movements over time steps using modulo operation for edge selection
 * 
 * Time Complexity: O((n + m) * T), where T is the maximum number of time steps needed;
 *                   In worst case, T can be up to O(n), so overall complexity is approximately O(n * (n + m))
 * Space Complexity: O(n + m), for adjacency list representation and waiting array
 */

import kotlin.math.min

fun main() {
    repeat(readLine()!!.toInt()) {
        val (n, m) = readLine()!!.split(" ").map(String::toInt)
        val adj = Array(n + 1) { mutableListOf<Int>() } // Build adjacency list
        repeat(m) {
            val (a, b) = readLine()!!.split(" ").map(String::toInt)
            adj[a].add(b)
            adj[b].add(a)
        }
        var waiting = IntArray(n + 1) { Int.MAX_VALUE } // Minimum waiting time to reach each node
        waiting[1] = 0 // Starting at node 1 with 0 waiting time
        var t = 0 // Current time step
        outer@while (true) {
            val next = IntArray(n + 1) { Int.MAX_VALUE } // Next state of waiting times
            for (a in 1..n) {
                if (waiting[a] != Int.MAX_VALUE) { // If we can reach node 'a'
                    if (a == n) { // Found destination
                        println("$t ${waiting[a]}") // Print total time and waiting time
                        break@outer
                    }
                    next[a] = min(next[a], waiting[a] + 1) // Wait one second: increase waiting time by 1
                    val b = adj[a][t % adj[a].size] // Move to next adjacent node using modular index
                    next[b] = min(next[b], waiting[a]) // No additional waiting when moving
                }
            }
            waiting = next // Update current state
            t++ // Increment time step
        }
    }
}


// https://github.com/VaHiX/CodeForces/