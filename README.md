# Trapesium_solver
This is program which solves simple puzzles with numbers


Let say you have to obtain 10 with numbers 1, 2, 3

one of the possible ways to do so is 3 ^ 2 + 1 = 10

this program aims to get as close answer as possible

also you can run it on multiple cores with par.sh 


# usage
1. specify a task in format similar to below:
``` 
3
1 2 3
10 
``` 
so the number of elements, elements, and score
2. the easiest way to run a programm is to use par.sh
``` bash par.sh number_of_cores input_file_name compiled_programm ```
  I recommend to compile with ``` g++ -O3 a.cpp -o a ```
3. Answer, If it gets an exact score, then it will stop automatically. 
4. 
  Otherwise it will run forever just decreasing the distance to the score 
  
  You can break at any point (with ctrl+C) and best results from each core will be at sol*.out in same directory
  
  They will be displayed in reverse polish notation, so get familiar with it
  
  
 # How it works?
  In short, it simply randomize an equation and compute it, if it's better than current score, then simply replace it. 
  
  The progress from each core will be displayed once in a while. 
  
  It suports: +, -, !, ^, / (only if result is an integer), !! (double factorial, which is just a product of numbers of the same parity, 4!! = 2 * 4, 5!! = 5 * 3), and C (newton's binomial)
  
  The result **MUST** be an integer
  
  I don't plan to further expand this project, how it's working now fully satisfy me, as it beats humans in most of the cases.
