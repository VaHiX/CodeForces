using System;
using System.Collections.Generic;

public class Program
{
    public static void Main(string[] args)
	{
		int n = Convert.ToInt32(Console.ReadLine());
		List<int> results = new List<int>();
		
		int checks = 0;
		int digits = n.ToString().Length;
		for(int i = 1; i <= digits; i++){
			checks += 9;
		}
		if(n - checks < 0) checks = 1;
		else checks = n - checks;
		
		for(int i = n; i >= checks ; i-- ){
			int b = n - i;
			string number = i.ToString();
		
			int sum = 0;
			for(int j = 0; j < number.Length; j++){
				
				sum += (Convert.ToInt32(number[j] - 48));
				
			}
			
			if(sum == b) results.Add(i);
		}
		
		
		Console.WriteLine(results.Count);
		results.Sort();
		foreach(int result in results)
		Console.WriteLine(result);
		
		
    }
}
