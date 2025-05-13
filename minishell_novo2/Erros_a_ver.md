echo "aspas ->'"	erro	aspas ->
echo "aspas -> ' "	erro	aspas -> 
echo 'aspas ->"'	erro	aspas ->
echo 'aspas -> " '	erro	aspas ->

echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<"	erro	> >> < Makefile README includes libft minishell objs srcs test.c workflowsepareted.md ? [ ] | ; [ ] || && ( ) & # $ \ <<

echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'	erro > >> < Makefile README includes libft minishell objs srcs test.c workflowsepareted.md ? [ ] | ; [ ] || && ( ) & # $ \ <<



export hello	error	zsh: segmentation fault (core dumped)  ./minishell
export HELLO=123

export A-	error /!\ ERROR! > export: `A-': not a valid identifier zsh: segmentation fault (core dumped)  ./minishell

export hello world	error	zsh: segmentation fault (core dumped)  ./minishell
export HELLO-=123
export =
export 123	error zsh: segmentation fault (core dumped)  ./minishell

unset HOME	error /!\ ERROR! > UNSET: command not found
unset PATH	error 
unset SHELL
	/!\ ERROR! ter atencao dps de alguns unsets cd fica com zsh: segmentation fault (core dumped)  ./minishell

export HELLO=123
export HELLO="beautiful world" /!\ ERROR! its not updating env its should return beautiful world when we do echo $HELLO and its not its returning HELLO

# Check if there isn't a zombie process called `cat`
echo "hi" | cat | cat | cat | cat | cat | cat | cat -> hi is not showing up it creates just a new line

cat cmd not working can not test heredoc heredoc manual test postponed until cat is fixed


CTRL+D not working
