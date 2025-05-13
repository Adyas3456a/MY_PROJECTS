# Source2HTML — Emertxe Training Project

## 1. Abstract

The **Source2HTML** project was developed as part of the Emertxe Advanced C module training.  
Its purpose is to **convert a C source file into a syntax-highlighted HTML file**, enabling users to visualize source code in a web browser.  
It adds semantic coloring for:

- Reserved keywords
- Preprocessor directives
- Numeric constants
- Strings
- ASCII characters
- Comments

Optionally, it can also generate **line numbers** in the HTML output.

---

## 2. Why This Project Matters

- **Readability**: Code is displayed with clear syntax highlighting.
- **Sharability**: Developers and instructors can showcase formatted C code in documentation, blogs, or reports.
- **Automation**: Converts files in a reproducible, programmable way.
- **Skill Application**: Reinforces knowledge of file I/O, state machines, parsing logic, and HTML.

---

## 3. Project Structure

### Files Used:

| File              | Description |
|-------------------|-------------|
| `s2html_main.c`   | Entry point. Handles CLI, file opening, calls parser and HTML writer |
| `s2html_event.c`  | Core parser using a state-event-driven approach to detect tokens |
| `s2html_event.h`  | Event type declarations and parser interface |
| `s2html_conv.c`   | Handles HTML generation and token-to-span conversion |
| `s2html_conv.h`   | HTML writer declarations |
| `styles.css`      | Defines styles for each syntax type (keywords, comments, etc.) |
| `test.c`          | Sample C source code for testing the tool |
| `Makefile`        | Compilation automation (recommended to create) |

---

## 4. Function Overview

### `get_parser_event(FILE *fp)`
State-driven lexer: reads the input C file and returns tokenized elements (strings, constants, etc.)

### `source_to_html(FILE *fp, pevent_t *event)`
Maps each event (e.g., string, keyword) to an HTML `<span>` element with proper CSS class.

### `html_begin()` / `html_end()`
Writes the beginning and end HTML skeleton (`<html><head>...</pre></html>`)

---

## 5. How to Build and Run

### Build:
```bash
make
```

### Usage:
```bash
./source_to_html test.c output_with_lines.html -n
./source_to_html test.c output_without_lines.html
```

- `-n` adds line numbers
- Without `-n`, no line numbers are shown

### View Output:
Simply open the HTML file in any browser:

- Double-click `output_with_lines.html` or `output_without_lines.html`
- Or drag and drop it into a browser window
- Or run:
  ```bash
  open -a "Google Chrome" output_with_lines.html
  open -a "Google Chrome" output_without_lines.html
  open -a "Google Chrome" output.html


---

## 6. Sample Output (Browser View)

```html
<span class='line-number'>  1: </span><span class='preprocess_dir'>#include</span> <span class='header_file'>&lt;stdio.h&gt;</span>
<span class='line-number'>  2: </span><span class='reserved_key1'>int</span> main() {
...
```

---

## 7. Credits

**This project is part of Emertxe Information Technologies' Advanced C Training**  
Module: Source2HTML — June 2014, Version 0.1

**Author:** Adyasha Nanda  

---

## 8. License

Educational use only. All rights reserved to Emertxe Information Technologies (P) Ltd.