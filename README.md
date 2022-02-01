# minishell

This project is the first group (2 people) project in the 42 core curriculum.

The objective of this project is to create a simple shell, like an own little bash.

## Project specifications

For the project we were allowed to use GNU's readline library which handles the terminal interaction (history & input reading).
For everything else the subject allows only to use a few low-level functions and a few POSIX system calls.

## Features


## How to use

The current version of minishell is developed and tested on macOS, but it should work on all UNIX/LINUX based systems as well.

<b>Requirements:</b>
- GCC / CLANG Compiler
- GNU Make
- GNU Readline library

1. Download/Clone this repo
```
git clone <repo-url> minishell
```
```
cd minishell && make release
```
```
./minishell
```

## Dependencies
### Install readline with [brew](https://brew.sh/)
```
brew install readline
```

```
brew link --force readline
```

```
```

### Install readline on 42 Macs

Install Brew, <b>only if it is not already installed:</b>

```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

Install Readline library:
```
brew install readline
```

```
brew link --force readline
```

```
echo 'export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```

```
echo 'export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"' >> ~/.zshrc
```

## Activate debug mode

Enter minishell and export the DEBUG env:

```
export DEBUG=printer
```

For all next commands you will execute in the minishell you will see the different processing steps from the lexer and parser with syntax highlighting.

## Change the command line prompt
1. Enter the SHELL
```
./minishell
```
2. Export the PS1 env (also works in Bash and other similar shells)
```
export PS1='enter your prompt wish...$ '
```
