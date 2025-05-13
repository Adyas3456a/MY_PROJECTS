# Lexical Analyzer Project

![C](https://img.shields.io/badge/Language-C-blue) ![Status](https://img.shields.io/badge/Status-Completed-brightgreen) ![Author](https://img.shields.io/badge/Author-Adyasha%20Nanda-blueviolet)  

**Author:** Adyasha Nanda  
**Institution:** EMERTXE Information Technologies Pvt. Ltd.  
**Module:** Advanced C

---

## 📑 Table of Contents
- [1. Project Overview](#1-project-overview)
- [2. Features & Capabilities](#2-features--capabilities)
- [3. File Structure](#3-file-structure)
- [4. Compilation & Execution](#4-compilation--execution)
- [5. Token Types Recognized](#5-token-types-recognized)
- [6. Functional Flow & Pseudocode](#6-functional-flow--pseudocode)
- [7. Sample Input/Output](#7-sample-inputoutput)
- [8. Token Flow Diagram](#8-token-flow-diagram)
- [9. Conclusion](#9-conclusion)

---

## 1. Project Overview
Lexical analysis is the first phase of a compiler, where the source code is read and broken into tokens. This project simulates a **Lexical Analyzer** that identifies and classifies tokens from a `.c` source file.

This project was developed as part of the **EMERTXE Advanced C module**, and it focuses on:
- File I/O
- String handling
- Token classification

---

## 2. Features & Capabilities
- Accepts any `.c` file and reads it line-by-line.
- Recognizes and classifies the following token types:
  - Keywords
  - Identifiers
  - Operators
  - Special characters
  - Constants (Numeric literals)
  - String literals
- Displays tokens in a clean and aligned format.

---

## 3. File Structure
```
lexical_analyzer/
├── main.c             // Entry point: handles argument parsing and printing
├── lexer.c            // Core logic: tokenization and classification
├── lexer.h            // Header file with declarations and enums
├── Makefile           // Compiles the program
└── test.c             // Sample input source file
```

---

## 4. Compilation & Execution
To run the project:

### 🛠️ Step-by-step:
1. Open a terminal and navigate to the project directory.
2. Run the following command to compile the project:
   ```bash
   make
   ```
3. Prepare a `.c` file, e.g., `test.c` with some simple C code.
4. Run the lexical analyzer:
   ```bash
   ./lexical_analyser test.c
   ```

### Example:
```
Open        :   test.c   :    Success
Parsing     :   test.c   :    Started

Keyword            :   int
Identifier         :   main
...
Parsing     :   test.c   :    Done
```

---

## 5. Token Types Recognized
| Token Type        | Description |
|------------------|-------------|
| Keyword          | Reserved words like `int`, `return`, etc. |
| Identifier       | Variable or function names |
| Operator         | Arithmetic, assignment, etc. (`+`, `=`, `==`) |
| Special Character| Symbols like `{`, `}`, `;` |
| Literal          | Numeric or string constants |
| Unknown          | Anything not recognized |

---

## 6. Functional Flow & Pseudocode

This section describes how the Lexical Analyzer processes input, tokenizes it, and classifies each token.

### 🔁 `main()` - Entry Point
Responsible for handling command-line arguments, initializing the lexer, and printing the output.

#### Behavior:
- Verifies that a filename is provided.
- Prints a user-friendly message like `Open : filename : Success`.
- Starts parsing and repeatedly calls `getNextToken()`.
- Based on the token type, prints the token in a formatted line.

#### Pseudocode:
```c
if (argc != 2)
    print "Usage" and exit

print "Open : <file> : Success"
print "Parsing : <file> : Started"

initializeLexer(argv[1])

loop:
    token = getNextToken()
    if token.type == UNKNOWN
        break
    print tokenType : token.lexeme

print "Parsing : <file> : Done"
```

---

### 📥 `initializeLexer(filename)` - Setup Phase
Initializes the lexer with the input file stream.

#### Behavior:
- Opens the `.c` file in read mode.
- Reads the first character using `fgetc`.
- Sets global file pointer and character tracker.
- If file doesn't exist, prints an error and exits.

#### Pseudocode:
```c
open file using fopen(filename, "r")
if file == NULL:
    print error and exit

currentChar = fgetc(file)
```

---

### 🔍 `getNextToken()` - Tokenization Engine
The core function that extracts and categorizes tokens.

#### Behavior:
- Skips whitespace and newlines.
- Identifies the type of the next token:
  - **Keywords/Identifiers:** Starts with alphabet or `_`, continues with alnum or `_`.
  - **Numeric Constants:** Starts and continues with digits.
  - **String Literals:** Surrounded by double quotes `"`.
  - **Operators:** Matches single-character symbols like `+`, `-`, `=` etc.
  - **Special Characters:** `{`, `}`, `;`, `(`, `)` etc.
  - **Unknowns:** Anything else, used to signal EOF or invalid characters.

#### Pseudocode:
```c
skip whitespace

if currentChar == EOF:
    return token with type UNKNOWN

if isalpha(currentChar) or currentChar == '_':
    read while alnum or _
    if match with keyword list:
        return token(KEYWORD)
    else:
        return token(IDENTIFIER)

if isdigit(currentChar):
    read while digit
    return token(CONSTANT)

if currentChar == '"':
    read until next '"'
    return token(STRING_LITERAL)

if currentChar is in operator list:
    return token(OPERATOR)

if currentChar is in special character list:
    return token(SPECIAL_CHARACTER)

else:
    return token(UNKNOWN)
```

Each call to `getNextToken()` reads from the global file stream and returns the next token until EOF.

---

## 7. Sample Input/Output
### 🔡 Input (`test.c`)
```c
int main()
{
    printf("Hello World\n");
    return 0;
}
```

### 📤 Output
```
Open        :   test.c   :    Success
Parsing     :   test.c   :    Started

Keyword            :   int
Identifier         :   main
Operator           :   (
Operator           :   )
Operator           :   {
Identifier         :   printf
Operator           :   (
Literal            :   "Hello World\n"
Operator           :   )
Operator           :   ;
Keyword            :   return
Literal            :   0
Operator           :   ;
Operator           :   }

Parsing     :   test.c   :    Done
```

---

## 8. Token Flow Diagram

```text
 Source Code  -->  Lexer Reads Character by Character
                        ↓
         [Whitespace skipped automatically]
                        ↓
     ┌────────────┬─────────────┬──────────────┐
     │ Identifier │  Keyword    │  Literal     │
     └────────────┴─────────────┴──────────────┘
             ↓
        Token classified → Stored and printed
```

---

## 9. Conclusion
This Lexical Analyzer provides a foundational understanding of compiler design, particularly the lexing stage. It's lightweight, easy to extend, and a great way to practice string manipulation, token classification, and file processing in C.

Further improvements can include:
- Line number tracking
- Multi-character operator support (like `>=`, `!=`)
- Error highlighting for invalid tokens
- Comment detection and classification

