Test case:

For my test case I used acorn.txt. I entered 
"./life 50 50 100 Tests/acorn.txt y y" into the commandline. The final output
looked something like below:
                                   
                                                  
                                                  
                                                  
      xxx                                         
     x           xxx                              
   xx x x                          xx             
  xxxxx x                          xx             
  x    x                                          
xxx     x                                         
      xxx                                         
      xx                                          
                                                  
                                                  
                                                  
  x  x                                            
   x  x                                           
   x x                                            
                                                  
                                                  
                                                  
                                                  
                                                  
                                                  
                                                  
                                                  
                                                  

Max generations reached: 100


Loop invariants:

There are 15 loop invariants in this program. Most of them are repetitive but
descriptive. For the nested for loops, the outer loop invariant would always
be that i+1 is the number of rows that the loop has accessed. The inner loop
invariant would always be that j+1 is the number of columns that the loop has
accessed in the ith row.

I left a few loop invariants blank near the end because I procrastinated on
this project and don't have time to fill them in. The last invariants that
were left blank would go like this: i+1 is always equal to the number of 
generations that the loop has gone through



Problems:

The biggest problem and most frustrating problem I had was trying to figure out
why my getNeighbors function wasn't working. It turns out that I had to swap the
x and y coordinates around because I forgot that arrays in c are row major.
(brain fart).

A smaller problem that I had and currently have is that my program can't detect
whether or not the pattern is oscillating. If I started this assignment earlier
like I should have I would have gotten it. Next time I will start the assignment sooner.


Credit:
I got the idea of creating a buffer of o's around the array in my getNeighbors()
function from stack overflow. I thought it was a clever way and I put the link
in my code.
