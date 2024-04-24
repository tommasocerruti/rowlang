# RowLang

## Technical Description of RowLang

RowLang is an esoteric programming language designed for symbolic computation, inspired by the dynamics of rowing.  
It offers a minimalistic yet expressive syntax, combining memory manipulation with the metaphorical representation of rowing actions.  
RowLang programs are composed of commands, loops, formations and stroke rate adjustments providing a unique perspective on algorithmic expression.  

## Syntax and Semantics

- **Commands:** RowLang commands correspond to rowing maneuvers and memory operations:
  - `P`: Pull - Move the memory pointer to the right.
  - `R`: Recover - Move the memory pointer to the left.
  - `S`: Stroke - Increment the byte at the current memory cell.
  - `B`: Bow - Decrement the byte at the current memory cell.
  - `.`: Catch - Output the byte at the current memory cell as a character.
  - `,`: Release - Input a character and store its ASCII value in the current memory cell.
  Commands can be followed by an integer (ranging from 2 to 9) that represents the number of repetitions of that command (if omitted it's 1).
- **Loops:** RowLang supports loop constructs enclosed within `[...]`, facilitating repetitive execution of commands until the value of the current memory cell becomes zero.
- **Formations:** By utilizing `{...}`, RowLang enables parallel execution of commands, simulating the synchronized movements of rowers in a regatta race.
- **Stroke Rate Adjustment:** The `^` and `v` commands allow for dynamic adjustment of the stroke rate, regulating the speed of program execution to simulate changes in rowing intensity and pacing.

## Implementation of the compiler

- **Lexer and Parser:** Lexical analysis and parsing techniques to translate source code into a structured representation, such as an abstract syntax tree (AST), facilitating further analysis and transformation.
- **Code Generation:** RowLang programs are translated from their parsed representation into executable C code. This process involves mapping RowLang commands and constructs to equivalent machine instructions or function calls.
- **Optimization:** Optimization techniques to enhance the efficiency and performance of generated code: loop unrolling, constant folding, and dead code elimination.
- **Execution:** RowLang programs are executed by interpreters or virtual machines capable of interpreting the generated code and simulating the behavior of RowLang commands and constructs. Interpreters typically iterate through the program's instructions, updating memory state and performing I/O operations as necessary.

## Actual structure of the compiler

- **Memory tape size and libraries:** Memory tape size set to 30kbyte and included basic C libraries.
- **Definition of token types and token representation:** Two structs one representing the different token types and one for the token representation (the token itself plus its possible repetitions).
- **Function to read token from input:** Function reading the character, assigning to the token its type and reading its repetitions (possibly omitted and by default set to one).
- **Function to emit C code:** Function emitting the C code based on the type of the token.
- **Main function to compile RowLang source code:** Main function dealing with format errors and with the reading logic to compile the code.

## Procedure to use the compiler

- **Compile the RowLang Compiler:** using gcc: gcc -o rlc rlc.c
- **Compile the RowLang source code:** using rlc: ./rlc rl_programs/example.rl > c_programs/example.c
- **Compile the generated C code:** using gcc: gcc -o exec_programs/example c_programs/example.c
- **Execute the compiled program** ./exec_programs/example

## Applications and Use Cases

- **Education and Exploration:** Educational tool for introducing programming concepts in a playful and engaging manner using a metaphorical approach to visualize algorithms as sequences of rowing actions.
- **Artistic Expression:** As an esoteric programming language, it appeals to enthusiasts interested in creative coding and algorithmic art. 
- **Algorithmic Challenges:** Its simplicity and metaphorical abstraction provide a platform for exploring computational concepts in unconventional ways.

## Conclusion

RowLang embodies the intersection of programming and metaphorical expression, offering a unique lens through which to view computational concepts. Its minimalist syntax and rowing-inspired semantics provide a canvas for creativity, exploration, and technical experimentation. Whether used for educational purposes, artistic endeavors, or algorithmic challenges, RowLang invites programmers to navigate the waters of symbolic computation with curiosity and imagination.