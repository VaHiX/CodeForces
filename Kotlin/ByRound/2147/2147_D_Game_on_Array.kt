// Problem: CF 2147 D - Game on Array
// https://codeforces.com/contest/2147/problem/D

/*
D. Game on Array
Purpose: Solves a game theory problem where Alice and Bob play optimally on an array of positive integers.
Each turn, a player selects a value x > 0 present in the array:
- They earn 1 point for each occurrence of x in the array,
- Each x in the array decreases by 1.

Algorithm:
1. Group elements by their frequency.
2. For odd values, collect frequencies to be used later for optimal allocation.
3. Calculate base points for even values (each value contributes half its count).
4. Sort odd frequencies in descending order.
5. Alternate adding these to Alice and Bob's scores optimally.

Time Complexity: O(n log n) due to sorting of frequencies.
Space Complexity: O(n) for storing groupings and frequency map.
*/

fun slv(){
    val n = readInt()
    val a = readInts()
    val freq = a.groupingBy{it}.eachCount() // Group elements by value and count occurrences
    var f = mutableListOf<Int>()
    var alice = 0L
    var bob = 0L
    
    for((x, y) in freq) {
        if(x % 2 == 1) { // If the value is odd, store its frequency
            f.add(y)
        }
        alice += (x/2).toLong() * y // Add base points from even parts of the value
        bob += (x/2).toLong() * y
    }
    
    f = f.sortedDescending().toMutableList() // Sort odd frequencies in descending order for optimal play
    
    for(i in 0 until f.size) {
        if(i % 2 == 0) alice += f[i] // Alice gets the odd frequency (optimal choice)
        else bob += f[i] // Bob gets the odd frequency
    }
    
    println("$alice $bob")
}

fun main(){
    repeat(readInt()) {
        slv()
    }
}

fun readInt() = readln().toInt()
fun readInts() = readln().split(" ").map{it.toInt()}


// https://github.com/VaHiX/CodeForces/