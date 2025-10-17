// Problem: CF 2000 B - Seating in a Bus
// https://codeforces.com/contest/2000/problem/B

/*
 * Purpose: Determine if all passengers followed the seating rules on a bus.
 * 
 * Algorithm:
 * - For each passenger in order, check if the chosen seat has at least one occupied neighbor.
 * - Use a set to track occupied seats for efficient lookup.
 * - For the first passenger, no checks are needed as the bus is empty.
 * - For subsequent passengers, verify that either the seat to the left or right is occupied.
 *
 * Time Complexity: O(n) per test case, where n is the number of passengers.
 * Space Complexity: O(n) for the set storing occupied seats.
 */
fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val a = readLine()!!.split(" ").map { it.toInt() }
        val occupied = mutableSetOf<Int>() // Track which seats are occupied
        var valid = true // Flag to track if all passengers followed rules
        
        for (i in a.indices) {
            val seat = a[i]
            
            // For the first passenger, no check is needed
            if (i > 0) {  
                // Check if neither left nor right neighbor is occupied
                if ((seat - 1 !in occupied) && (seat + 1 !in occupied)) {
                    valid = false
                    break // Invalid seating, stop processing
                }
            }
            occupied.add(seat) // Mark current seat as occupied
        }
        
        if (valid) {
            println("YES")
        } else {
            println("NO")
        }
    }
}


// https://github.com/VaHiX/CodeForces/