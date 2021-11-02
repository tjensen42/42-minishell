# Sample C Project Structure

**I recommend to use this repo as inspiration to create your own [GitHub Template](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-template-repository) for your next projects.**

**To integrate your own library into the template you can copy it sources in the libs folder or add it as a submodule with this command: ```git submodule add <git-submodule-link> libs/libname```**

**When you added it as submodule you should clone the template repo with ```git clone --recursive <git-template-link>```**

## Structure
```
.
├── include/
│   ├ header.h
│   └ ...
├── libs/
│   ├ libft
│   └ ...
├── src/
│   ├ project.c
│   └ ...
├── .gitignore
├── .gitmodules
├── Makefile
└── README.md
```

This is really just an example template-structure for a C project.

There is no 'standard' C project structure, it really depends on the project and your personal application and your needs.

But in general it is always good to have some kind of structure and being aware of that it matches with the type and scope of the project.

I created this repo for myself to use it as git-template for the most 42 core curriculum projects.

The Makefile in every library should at least contain these rules:
```all``` ```clean``` ```fclean``` ```re``` ```debug``` ```release```

## How to use it

1. **Create** new repo based on this template.
2. **Rename** project.c & project.h file and change header protection (#ifndef...)
3. **Add libraries** if you have additional ones for your project
- for example: ```git submodule add <libft-repo-link> libs/libft```
4. **Makefile:** Add all *.c files to the SRCS variable
5. **Makefile:** Name all libs in the LDLIBS variable ```libft -> "-lft" || libmath -> "-lmath"```

## To remove a submodule from your repo you can delete it this way:
1. Remove the submodule entry from .git/config <br> ```git submodule deinit -f path/to/submodule```

2. Remove the submodule directory from the superproject's .git/modules directory <br> ```rm -rf .git/modules/path/to/submodule```

3. Remove the entry in .gitmodules and remove the submodule directory located at path/to/submodule <br> ```git rm -f path/to/submodule```

## Remove 'preinstalled' libft:

```git submodule deinit -f libs/libft && rm -rf .git/modules/libs/libft && git rm -f libs/libft```
