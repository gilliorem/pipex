#PIPEX 

##FUNCTIONS


##REDIRECTION
###DUP DUP2
Duplicate a file descriptor
Redirect the output to a specific fd.
*usage*
`int fd = open ("out, O_WRONLY | O_CREAT | O_TRUNC, 0644")
int saved_output = dup(1)
dup2(fd, 1): now fd and now both redirect to fd. that means output from
stdout will now be redirected to the fd. (file )`
dup is never called inside write.

But you might have called dup2 earlier, so when you write(1, …), fd 1 no longer goes to your terminal — it goes wherever you redirected it.
###PIPE


##ERROR
###PERROR
prints the error message regarding the last errno (error number.)
###ERRNO
returns the error code.
###STRERROR
returns a char * associated with the errno passed as argument. *
**strerror(130) = Owner died.**
###ACCESS
returns a specific access code based on the file and what we are
trying to do with it. 
*acess(file,W_OK) == 0* means we can write in file.

##PROCESS
###FORK
###WAIT
###WAITPID

minipx <cmd1> 'arg1 arg2 ...' <cmd2> 'arg1 arg2 ...'

le nom du program (argv[0])
le nom de notre cmd (argv[1]) 
	qui doit prendre toutes les comandes.
	ici on doit fournir une sorte de variable pour qu'il trouve
les args de cmd1 (argv[2]): on doit faire un split pour separer les mots: que chaque mot soit un argument.
le nom de notre cmd2 (argv[3])
les args de cmd2 (argv[4])

PART A. Single command
run one cmd in a child and wait.
	fork, child does execve
	parent waitpid, return child's exit status
	if execve fails, child prints an error to stderr and ex127
./runone /bin/echo hello
! echo is a built in cmd. it is a bad example | use (ls-cat-wc...) any command that is in the /bin/ 
so now instead of having to type /bin/cmd
I want to have cmd

- retrieve path (/bin/cmd)
- 
*I pass my cmd from the cmf line arg. (arg[1]) (ls)*

*thought of the split join combo*
*split on this string 
char *path = "PATH=/home/regillio/bin:/home/regillio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
split(path, '/') starting at h
"home" "regillio" "bin:"
**I want to split on `:`**
'home/regillio/bin'
'/home/regillio/bin'
'/usr/local/sbin'
'/usr/local/sbin'

Sep 5 - Day 3
-
So I wanted to go from ./pipex /bin/ls -l to ./pipex ls -l
To do so, I needed to "found" /bin/
so our starting point to find it is the third argument of the main (`char *envp[]`). this is a list of our environment variables (runing the env cmd)
`SSH_AUTH_SOCK=/run/user/102382/keyring/ssh
USER=regillio
XDG_MENU_PREFIX=gnome-
SHELL=/bin/zsh
SESSION_MANAGER=local/c2r7s5.42singapore.sg:@/tmp/.ICE-unix/146565,unix/c2r7s5.42singapore.sg:/tmp/.ICE-unix/146565
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
OLDPWD=/home/regillio/Desktop/pipex
VTE_VERSION=6800
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
COLORTERM=truecolor
...`
the format of this list is `KEY=value` (whatever that means)
that can mean that we can perform a split on the '=' to seperate the two strings and search for the specific KEY. Or we can search for `PATH=`
Now we want to get our hands on the PATH variable
Since each line is already a substring of envp, we can loop through each string and stop until we find `PATH=`;
A strncmp (properly handled) (think of the case we dont find it) (think of the case where there is a `PATHETIC=` variable...) will do.
so now we are left we one line that looks like this:PATH=/home/regillio/bin:/home/regillio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

and we need to seperate in 2 and then separate again in more pieces.
first separation is [PATH] `=` [THE REST]
so we split on `=`
and we keep [THE REST]

since we want to try to run our command (argv[1]) (ls for example) in every dir
so that mean we want to do:
/home/regillio/bin*/ls*
/home/regillio/bin*/ls*
/usr/local/sbin*/ls*
...
we do this until... it runs ! good think about execve (we gonna see later) is that if it does run, it returns. you will understand.
but first we need to take care of two things

##Questions

### General
- does ./a.out runs a exec() underneath the hood ?
- the kernel, what is it exactly ? | returns to the kernel ?
- start up routine is called (coded in assembly), in C exit(main(arc,arg2))
- how a process is suppose to terminate ? (8) (3 mostly use (clean exit))
- how does the exit function works ? what are the handlers for ?
- recursion works specifically because of the stack in C
- what does it mean to return a non void* (d'ou le casting, ok I gotta it.)
- use of realloc: increase the size of an allready allocated space. returns the same pointer !
- Is libmalloc worth it ? what about quick-fit ?
- the use of get_env() is better than get if from environ list, why ?
- we cannot affect the env of the parent process ? can I modify my env list ?
-
- The proper way to exit a program ?
- The proper way to print an error ?
- The proper way to catch an error ?

### Code implementation
make a new fds[] variable part of my struct args...
would it fuck me with the pipes' fds and the specific children fds ? I think so.
should I have another struct based on fds?
based on something else?
fd is link with file. every thing is a file. that is why 1 fd ccan be made to write, another to read.
Where does EXIT_FAILURE goes ? is it relative to its children



Cedric's code:
while (full_paths_binary[i])
{
    execve(full_paths_binary[i], cmd_args, envp);
    i++;
}
char **temp;
while (full_paths[i]) 
{
    printf("full_path:%s\n",full_paths[i]);
    temp = ft_split(argv[2], ' ');
    int j = 0;
    while (temp[j])
        ++j;
    printf("j : %i\n", j);

    temp[j] = malloc(sizeof(char *));
    ++j;
    temp[j] = malloc(sizeof(char *));
    temp[j] = NULL;

    // version 1: argv[1] in temp[1]
    // j -= 1;
    //  while (j != 1) {
    //    temp[j] = temp[j - 1];
    //  }
    //  temp[j] = argv[1];

    // version 2: argv[1] in temp[j-1]
    temp[j - 1] = argv[1];

    char *new_paths = ft_strjoin(full_paths[i], temp[0]);
    temp[0] = new_paths;
    printf("temp[0]:%s\n", temp[0]);
    if (access(temp[0], F_OK) == 0) {
        execve(new_paths, temp, envp);
        printf("paths:%s\n", full_paths[i]);
    }

    // argv[1] == argv+1
    // printf("paths:%s\nav:%s\n",path[i],av[i]);
    i++;
}
return (ft_printf("ac:%d\n", ac) & 0);
while (full_paths[i]) {
    // execve(argv[0], argv + 1, envp);
    i++;
}


pipes allow the output of one process: the child process to be the input of a second process
total, we have 4 fds: child_fd[0], child_fd[1] & parent_fd[0], parent_fd[1]
we want to close both children_fds, why ?
in the parent process, we want to read the output of the child process
dup2()
cat -e file | wc 
the output of cat -e file is the input of wc

may have to modify the run_cmd function so I can pass the number like the nth cmd: no need. run_cmd() is process-linked 
if there is an infile, instead of taking input from keyboard, take input for infile 
need to check if we have a *correct* infile and a correct *outfile* and then using dup2 to redirect. we need to get the output of the first cmd to pipe it to the second one.

j'execute ma cmd, je redirige l'output du child sur le parent
le parent lit cet output
le parent execute sa cmd en prenant pour input la cmd de l'enfant, il ecrit son output dans un outfile

je pipe - je fork
je suis dans l'enfant: output original: fds[0]; nv output: STDOUT;

j'ai fait ma redir, je ferme mes fds.
je run ma cmd. testons.

target:
[x] check for correct infile open
[]  handle segfault if infile is incorrect.
[x] check for correct outfile
[x] redirect the infile
[] redirect to outfile

infile: argv[1]
outfile: argv[4]
get the infile-fd; use its fd for the parent process. (using dup2)

fds[0] is always for read.
fds[1] is always for write.

I need to get argv[2] and argv[3] arguments.

I need two children because I have two cmds.
fork for the first child that has his own run_cmds

a second one for the second child.

I have both of my forked children. 

Sep 17, 23:26
On to the best part:
[x] child_execution 1
[x] child_execution 1

[] norm refacto
[] mem issue 
so we have a `printing error issue`: in the case of
./pipex infile "wrong_cmd1" "wrong_cmd2" outfile
the error message prints on the outfile.
 % < infile sl | wc > output
first cmd wrong: zsh: command not found: sl
it creates the output file and display 0    0   0

< infile sl | sl > output
zsh: command not found: sl
zsh: command not found: sl
creates *an empty *outfile**


Sep 19, 12:48, first eval
-
interesting *cmd* has been run during the eval:
- nm -u pixe 
- valgrind --trace-children=yes ./pipex Makefile cat cat outfile
- ./pipex qwdqdqdqd "sleep 2" xxx outfile
- < Makefile sleep 1 | cmd > outfile
- cp file permission
- chmod 000 permission
- **./pipex permission cat cat outfile (this one: error management is incorrect.)**
