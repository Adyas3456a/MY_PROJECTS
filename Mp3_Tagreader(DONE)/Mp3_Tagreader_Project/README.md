# 🎵 MP3 Tag Reader & Editor (C Project)

A simple C-based utility to **read** and **edit** ID3v2 metadata tags (like Title, Artist, Album, etc.) from MP3 files. This tool works via the command line and allows users to view or modify metadata in a structured and user-friendly way.

---

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [How to Build](#how-to-build)
  - [Steps](#steps)
  - [Makefile](#makefile)
- [Usage](#usage)
  - [View Mode](#view-mode)
  - [Edit Mode](#edit-mode)
- [Sample Output](#sample-output)
- [Learnings](#learnings)
- [Contribution](#contribution)
- [License](#license)
- [Author](#author)
---

## Project Structure

```
.
├── editmp3.c        # Handles editing of MP3 tags
├── editmp3.h        # Header for edit functionality
├── main.c           # Entry point; handles CLI input and mode switching
├── Song1.mp3        # Sample MP3 file (for testing purposes)
├── tagreader        # Compiled output executable (name may vary after `make`)
├── util.h           # Utility macros and functions
├── viewmp3.c        # Handles viewing of MP3 metadata
├── viewmp3.h        # Header for view functionality
├── common.h         # Common structures, enums, and constants
└── Makefile         # For compiling the project
```

---

## Features

- ✅ View metadata tags of MP3 files (ID3v2)
- ✅ Edit specific tags like:
  - Title (`TIT2`)
  - Artist (`TPE1`)
  - Album (`TALB`)
  - Year (`TYER`)
  - Genre (`TCON`)
  - Comment (`COMM`)
- ✅ Works on Linux-based and macOS systems
- ✅ Minimal dependencies (only uses standard C libraries)

---

## How to Build

### Steps

1. Open a terminal and navigate to the project directory:

   ```bash
   cd /path/to/Mp3_Tagreader_Project
   ```

2. Build the project using:

   ```bash
   make
   ```

   This will compile all `.c` files and generate an executable called `tagreader`.

3. (Optional) Clean the build:

   ```bash
   make clean
   ```

### Makefile

```makefile
# Makefile for MP3 Tag Reader & Editor

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o viewmp3.o editmp3.o
TARGET = tagreader

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c viewmp3.h editmp3.h util.h
	$(CC) $(CFLAGS) -c main.c

viewmp3.o: viewmp3.c viewmp3.h util.h
	$(CC) $(CFLAGS) -c viewmp3.c

editmp3.o: editmp3.c editmp3.h util.h
	$(CC) $(CFLAGS) -c editmp3.c

clean:
	rm -f *.o $(TARGET)
```

---

## Usage

### ➔ View Mode

```bash
./tagreader -v <filename.mp3>
```

**Example:**

```bash
./tagreader -v Song1.mp3
```

---

### ➔ Edit Mode

```bash
./tagreader -e <filename.mp3> -t <tag_number> -T "<new_text>"
```

**Tag Numbers:**

| Tag No. | Tag     | Description      |
|---------|---------|------------------|
| 1       | TIT2    | Title            |
| 2       | TPE1    | Artist           |
| 3       | TALB    | Album            |
| 4       | TYER    | Year             |
| 5       | TCON    | Genre/Content    |
| 6       | COMM    | Comment/Composer |

**Example:**

```bash
./tagreader -e Song1.mp3 -t 1 -T "My New Song"
```

This updates the **Title** of the MP3 file to `"My New Song"`.

---

## Sample Output

### View Mode:

```bash
ID3v2.3.0 Tag Information:
--------------------------------------
Title       : Rivers
Artist      : Ethereal Darkness
Album       : Smoke And Shadows
Year        : 2019
Genre       : Melodic Death Metal
Comment     : This is a comment
--------------------------------------
```

---

## Learnings

This project helps you understand:

- File handling in C
- Byte-level manipulation (ID3 tags use specific offsets)
- Working with structures and enums
- Little-endian encoding
- Building modular C applications
- Writing Makefiles and CLI tools

---

## Contribution

This is a beginner-friendly open-source project. Feel free to fork and enhance with:

- ID3v1 support
- More tag types
- Cross-platform compatibility
- GUI using GTK or other libraries

---

## License

This project is developed as part of the curriculum at [Emertxe Information Technologies](https://www.emertxe.com/embedded-systems/c-programming/c-projects/mp3-tag-reader/).  
It is open-source and licensed under the [Emertxe License](LICENSE).

---

## Author

**Adyasha Nanda**  
💻 GitHub: [@Adyas3456a](https://github.com/Adyas3456a)  
📩 Email: adyashananda111@gmail.com

