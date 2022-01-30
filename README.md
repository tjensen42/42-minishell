# minishell


A parser is divided into two parts: a ​Lexical Analyzer​ or ​Lexer​ takes the input characters and puts the characters together into words called ​tokens​, and a ​Parser ​that processes the tokens according to a grammar and build the command table.

### Install dependencies on 42 Macs

```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

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
