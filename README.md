# compiler-design

# Lexical Analyzer – Compiler Design Project

This project is a basic **Lexical Analyzer** implemented in C++. It reads a `.cpp` source file and identifies various tokens such as:

- Identifiers  
- Keywords  
- Operators  
- Numbers  
- Comments (single-line and multi-line)  
- String literals  
- Punctuation symbols  

## Features

- Identifies and classifies tokens from a C++ source file
- Detects and reports:
  - Single-line (`//`) and multi-line (`/* */`) comments with line numbers and lengths
  - String literals
- Supports common C++ keywords and operators
- Stores identified tokens in separate vectors for further processing or display

## Core Concepts

This project demonstrates the first phase of a compiler: **Lexical Analysis**, which breaks the source code into meaningful units (tokens).

## How to Use

1. Replace the input file path in the `main()` function:
   ```cpp
   ifstream file("D:\\addition.cpp");
