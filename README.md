# 42_pipex  
Pipex – Project at 42 school (42 Wolfsburg)

<h1 align="center">
	🔗 Pipex
</h1>

<p align="center">
	<b><i>UNIX pipe recreation and command execution in C</i></b><br>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-what-i-learned">What I Learned</a>
</h3>

---

## 💡 About the project

> _Pipex is an individual project focused on recreating the shell’s pipe functionality in C. The program executes a series of commands, passing outputs through pipes to mimic shell behavior. This project emphasizes process creation, file descriptor management, and inter-process communication using pipes—fundamental concepts for advanced C programming and future studies at 42._

For more details, refer to the [**subject of this project**](https://github.com/jonona912/42_pipex/blob/main/pipex_subject.pdf).

## 🛠️ Usage

### Requirements

Pipex is implemented in C and requires the **`gcc` compiler** and standard **C libraries** for compilation and execution.

### Instructions

**1. Compiling the program**

To compile, use the following command in the project directory:

```shell
make
```

**2. Running pipex**

The standard usage format is:

```shell
./pipex infile "cmd1" "cmd2" outfile
```
- `infile`: source file for input
- `cmd1`: first command to execute
- `cmd2`: second command to execute
- `outfile`: destination file for output

Example:

```shell
./pipex input.txt "grep hello" "wc -l" output.txt
```
This command executes `grep hello < input.txt | wc -l > output.txt`.

**3. Bonus: Multiple Commands (pipex_bonus)**

When the bonus part is enabled, the program can handle more than two commands, as well as `here_doc` functionality.

**Multiple commands:**
```shell
./pipex_bonus infile "cmd1" "cmd2" "cmd3" ... "cmdn" outfile
```
Example:
```shell
./pipex_bonus input.txt "grep hello" "sort" "uniq" output.txt
```
This command executes: `grep hello < input.txt | sort | uniq > output.txt`

**here_doc mode:**
```shell
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" ... "cmdn" outfile
```
Example:
```shell
./pipex_bonus here_doc END "cat" "wc -l" output.txt
```
This command takes input from stdin until 'END' is encountered, then pipes through the commands and writes to `output.txt`.

## 📚 What I Learned

- UNIX process and file descriptor management
- Implementation and chaining of pipes
- Forking and command execution in C
- Robust error handling and resource management
- Parsing and handling command-line arguments
