# compiler-design

# Lexical Analyzer

 It reads a `.cpp` source file and identifies various tokens such as:

- Identifiers  
- Keywords  
- Operators  
- Numbers  
- Comments (single-line and multi-line)  
- String literals  
- Punctuation symbols  



- Identifies and classifies tokens from a C++ source file
- Detects and reports:
  - Single-line (`//`) and multi-line (`/* */`) comments with line numbers and lengths
  - String literals
- Supports common C++ keywords and operators
- Stores identified tokens in separate vectors for further processing or display

# Symbol Table

- Tracks program identifiers and their attributes
- Manages variable/function declarations with scope handling
- Records data types and values

# Parser & Code Generator

- Converts infix expressions to postfix notation
- Generates three-address code
- Produces assembly-like instructions

