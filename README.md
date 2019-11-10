# FILLIT

Fillit is one of the first projects in the 42 curriculum. The goal of Fillit is to parse and validate a file of tetromino pieces, and arrange them to fit into the smallest possible square.
A tetromino is a 4-block geometric figure, popularized by the game Tetris.

## Getting Started

This project uses [my 42 library](https://github.com/mint42/lib), which has already been included in this repository for ease of use. To set up this project, run `git clone https://github.com/mint42/fillit` in the folder of your choice. Then run the `make` command in the root of the repository. The Makefile will first create the library, and then create the executable file called `fillit`.

```
usage: ./fillit file
```

The file referenced is the input file for the program. It can have up to 26 tetromino pieces separated by a newline. These pieces, upon being validated, will be assigned a letter A - Z to represent them when the square is printed.

Example:

```
$> cat -e fake_file
.##.$
.##.$
....$
....$
$
...#$
...#$
..##$
....$
$
....$
..#.$
..#.$
..##$
$> cat -e fake_file_invalid_tetromino
.##.$
.#..$
..#.$
....$
$> ./fillit
usage: ./fillit file
$> ./fillit fake_file_invalid_tetromino
error
$> ./fillit fake_file
CAAB
CAAB
CCBB
....
$> 
```

## Notes

The library included in this repo differs from the [/lib](https://github.com/mint42/lib) repo in a few ways.

First, the ft_lstlen() function differs in that, for Fillit, it considers the a linked list node with NULL content to be the end of the linked list. This is not standard for other linked lists I've made. This was done to act as an alternative NULL terminator to node->next = NULL.

Also, not all the /lib modules are compiled in this project. This is to keep the project small, only using the modules that were necessary for the code to run.

Here is a list of all valid tetromino pieces:

```
#...	####
#...	....
#...	....
#...	....

##..
##..
....
....

#...	###.	##..	..#.
#...	#...	.#..	###.
##..	....	.#..	....
....	....	....	....

##..	#...	.#..	###.
#...	###.	.#..	..#.
#...	....	##..	....
....	....	....	....

##..	.#..
.##.	##..
....	#...
....	....

.##.	#...
##..	##..
....	.#..
....	....

#...	###.	.#..	.#..
##..	.#..	##..	###.
#...	....	.#..	....
....	....	....	....

```

## Authors

[Ari Reedy](https://github.com/mint42/) (me)  
[Alan Barnett](https://github.com/alan23394/) (partner)
