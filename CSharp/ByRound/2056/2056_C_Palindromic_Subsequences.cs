using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine()); // Reading number of test cases
        
        while (testCases-- > 0)
        {
            int size = int.Parse(Console.ReadLine()); // Read the size of the array
            List<int> numbers = new List<int>(new int[size]); // Initialize the list with size
            
            numbers[0] = 1; // Set the first element
            numbers[1] = 2; // Set the second element
            
            for (int i = 1; i <= size - 2; i++) 
            {
                numbers[i] = size - i - 1; // Set elements in the middle of the list
            }
            
            numbers[size - 1] = 1; // Set the last element
            
            // Print the list in reverse order
            for (int i = size - 1; i >= 0; i--)
            {
                Console.Write(numbers[i] + " ");
            }
            Console.WriteLine(); // Move to the next line after each test case
        }
    }
}
