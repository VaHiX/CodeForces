// Problem: CF 2160 D - MAD Interactive Problem
// https://codeforces.com/contest/2160/problem/D

/*
 * Problem: D. MAD Interactive Problem
 * 
 * Purpose: This code solves an interactive problem where we need to reconstruct a secret sequence of length 2n
 *          containing each integer from 1 to n exactly twice. We are allowed at most 3n queries.
 *          
 * Algorithm:
 * 1. First phase: Build a list 'b' of indices and use queries to determine which elements appear in the sequence.
 *    The key is to understand whether an element appears more than once (MAD > 0) or not (MAD = 0).
 * 2. Second phase: For each position without known value, we query with a subset of already determined values 
 *    to find the actual value at that index.
 *    
 * Time Complexity: O(n^2) per test case due to nested loops.
 * Space Complexity: O(n) for storing intermediate data (lists 'b' and 'd').
 */

fun main() = repeat(readLine()!!.toInt()) {
    var n = readLine()!!.toInt()    
    var b = mutableListOf(1, 2) // Start building a list of indices
    var k = 2 // Current number of indices used in query
    var i = 2 // Counter for positions processed
    var d = MutableList(2*n){0} // Array to store final sequence values
    
    // Main loop to determine MAD values for indices
    while(i<=2*n) {
        print("? $k ") // Query with current k indices from b
        println(b.joinToString(" "))
        var c = readLine()!!.toInt()
        if(c==0) {            
            i++ // Increment counter if no duplicate found
            k++ // Next index to check
            b.add(i) // Add next index
        }
        else {
            d[i-1]=c // Store the MAD value for this position
            b.removeAt(b.size-1) // Remove last index from list
            i++ // Move to next position
            b.add(i) // Add new index 
        }
    }
    
    var a = mutableListOf<Int>() // List to store indices with known MAD > 0 values
    
    for (j in 0..2*n-1) {
        if(d[j]>0) a.add(j+1)
    }
    
    // Second phase: find remaining unknown elements in the sequence
    for (j in 0..2*n-1) {
        if(d[j]==0) { // If no information was found for this position
            print("? ${n+1} ${j+1} ") // Ask about a combination with known value
            println(a.joinToString(" "))
            var e = readLine()!!.toInt()
            d[j]=e // Store the result to deduce the correct value
        }
    }
    
    print("! ") // Print the result prefix
    println(d.joinToString(" ")) // Output the completed sequence
}


// https://github.com/VaHiX/CodeForces/