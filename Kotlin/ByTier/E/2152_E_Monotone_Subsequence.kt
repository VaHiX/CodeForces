// Problem: CF 2152 E - Monotone Subsequence
// https://codeforces.com/contest/2152/problem/E

/*
 * Problem: E. Monotone Subsequence
 * Algorithm: Interactive problem using skyscraper queries to find a monotone subsequence of length n+1.
 * Time Complexity: O(n^3) due to at most n queries, each querying up to n^2 elements, and processing each.
 * Space Complexity: O(n^2) for storing intermediate results and stack.
 */

import java.util.Stack

fun main() {
    cases@for (c in 1..readln().toInt()) { // Process each test case
        val n = readln().toInt() // Read the value of n
        
        // Function to query indices and get visible skyscrapers
        fun query(indexes: List<Int>): List<Int> {
            println("? ${indexes.size} ${indexes.joinToString(" ")}")
            val response = readln().split(" ").map(String::toInt)
            return response.subList(1, response.size) // Return the indices of visible skyscrapers
        }
        
        val rem = (1..(n * n) + 1).toMutableSet() // Set of remaining indices to process
        val stack = Stack<List<Int>>() // Stack to store results from queries
        
        for (t in 1..n) {
            val result = query(rem.sorted()) // Query all remaining indices in sorted order
            
            if (result.size > n) { // If more than n visible skyscrapers, we found a long subsequence
                val answer = result.subList(0, n + 1) // Take the first n+1 indices
                println("! ${answer.joinToString(" ")}") // Output the answer
                continue@cases // Move to next test case
            }
            
            stack.push(result) // Push result onto stack for later processing
            rem.removeAll(result) // Remove processed indices from remaining set
        }
        
        val answer = mutableListOf(rem.min()) // Start building answer with minimum of remaining
        
        repeat(n) {
            val next = stack.pop() // Get previous query results
            // Find last value in next that is smaller than the last value in current answer
            answer.add(next.last { it < answer.last() })
        }
        
        answer.reverse() // Reverse to get correct order
        println("! ${answer.joinToString(" ")}") // Output final answer
    }
}


// https://github.com/VaHiX/CodeForces/