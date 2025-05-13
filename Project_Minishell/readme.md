# 🐚 Mini Shell (`msh`)

> A simple bash-like shell written in C  
> Author: **Adyasha Nanda**  
> Institution: **Emertxe Institution**  
> Platform: **Windows (via Terminal or WSL)**

---

## 📚 Table of Contents

- [Files](#📦-files)
- [How to Compile](#🛠️-how-to-compile)
- [How to Run](#▶️-how-to-run)
- [Features](#📌-features)
- [Sample Output (Windows Terminal)](#💻-sample-output-windows-terminal)
- [Final Status](#✅-final-status)

---

##  📦 Files

| File       | Description                                      |
|------------|--------------------------------------------------|
| `msh.c`    | Core implementation of the Mini Shell            |
| `msh.h`    | Header file with function declarations           |
| `Makefile` | Build automation with clean and txt file cleanup |

---

## 🛠️ How to Compile

```bash
make
````

To clean object files and any `.txt` files created during execution:

```bash
make clean
```

---

## ▶️ How to Run

```bash
./msh
```

---

## 📌 Features

* ✅ Custom shell prompt (`PS1`)
* ✅ Background (`&`) and foreground jobs
* ✅ Built-in commands: `cd`, `pwd`, `echo`, `exit`, `jobs`, `fg`, `bg`
* ✅ Piping using `|`
* ✅ Input/output redirection: `>`, `<`, `>>`
* ✅ Signal handling: `Ctrl+C`, `Ctrl+Z`
* ✅ Environment variable support: `$?`, `$$`, `$SHELL`

---

## 💻 Sample Output (Windows Terminal)

```bash
msh> ls
Test            makefile        msh             msh.c           msh.h           msh.o
msh> pwd
C:/Users/Adyasha/Downloads/My_projects/msh
msh> mkdir test
msh> cd Test
msh> pwd
C:/Users/Adyasha/Downloads/My_projects/msh/test
msh> cd ..
msh> pwd
C:/Users/Adyasha/Downloads/My_projects/msh
msh> echo Hello World
Hello World
msh> echo $?
0
msh> echo $
73787
msh> echo $SHELL
C:/Users/Adyasha/Downloads/My_projects/msh/msh
msh> PS1=MY_SHELL>
MY_SHELL> echo hello world > file.txt
MY_SHELL> cat file.txt
hello world
MY_SHELL> echo next line >> file.txt
MY_SHELL> cat file.txt
hello world
next line
MY_SHELL> ls | wc -l
       7
MY_SHELL> cat file.txt | grep Hello | wc -l
       0
MY_SHELL> sleep 10 &
[75081] 75081
MY_SHELL> sleep 50
^Z
MY_SHELL>[75113]+ Stopped
MY_SHELL> jobs
[75113] sleep 50

[75081] sleep 10 &

MY_SHELL> bg
MY_SHELL> fg
^C
MY_SHELL> sleep 30
^C
MY_SHELL> exit
```

---

## ✅ Final Status

* 🔹 All functionalities tested successfully
* 🔹 Project compiles and runs without errors
* 🔹 Supports Windows (via WSL or compatible terminal)
* 🔹 Implements job control, piping, redirection, and signal handling

---
