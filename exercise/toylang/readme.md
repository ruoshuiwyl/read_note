## Toy language



### Release
### data types
- boolean true|false   
- integer int32_t   
- float   double    
- string  
### variable 
- var x : int 
- val x : int 
### function
- fn id () {}  
- fn id ( int x) {}  
### control flow 
#### if expression
- if () {} else {}
- if () {} elsif () {} else {}
##### loop expression
- while () {}
- for  (init; ; ) {}
- foreach () {} 



#### operator and operator priority
() call function  
- Symbol inversion  
* / %   
+ =   
<< >>   
< <= >= >  
== !=   
&& 
|| 
####  symbols 
- => (pat => expr) part of match arm syntax  
- ; (...;)statement
- -> (fn() -> type, lamdba()->type) function and closure return type





### comments 
- // comments 
- /\*comments\*/

### collections
- vector


### key words 
- break - exit a loop immediately  
- continue - continue to the next loop iteration  
- else -  fallback for if control flow constructs   
- elsif - fallback for if contril flow constructs  
- false - boolean false literal  
- fn - function definition and function pointer type  
- for - iterator loop  
- if - conditional branching  
- lambda - lambda function definition
- match - pattern matching
- return - return from function 
- use - import sysbols into scope 
- true - boolean true literal   
- val - denotes immutability in references, raw pointers, and pattern bindings 
- var - denotes mutability in references, raw pointers, and pattern bindings 
- while - iterator loop 
