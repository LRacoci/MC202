
# ${EUID} identifica o tipo de usuario:
#    se for 0 eh o root, caso contrario, eh um usuario comum
# \[\033[x;xxm]] indica uma cor
# \w eh substituido pelo nome do diretorio atual
# \$ eh substituido por $ caso o usuario seja normal ou por # caso seja root
# \u eh substituido pelo nome do usuario

if [[ ${EUID} == 0 ]] ; then
    PS1='\[\033[01;34m\]\w \$\[\033[00m\] '
else
    PS1='\[\033[0;93m\](\t)\[\033[0;91m\]\u:\[\033[0;94m\]\w \[\033[0;92m\]\$\[\033[0;00m\] '
fi

alias gcc='gcc -std=c99 -ansi -pedantic -Wall -Werror -lm'
alias l="ls"
alias ls='ls --color=auto'
alias ll='ls -l'
alias la='ls -A'
alias lh="ls -lh"
alias ltr="ls -ltr"
alias cd..='cd ..'
alias mkdir='mkdir -p'
alias rm='rm -i'
alias mv='mv -i'
alias cp='cp -ai'
alias .='pwd'
alias ..='cd ..'
alias ...='cd ../..'
alias grep='grep --color=auto'
alias df='df -H'
alias du='du -h'

# quando usamos "seta para cima" para visualizar o historico de
# comandos, essa especificacao faz com que comandos iguais sejam
# ignorados

HISTCONTROL=ignoreboth
export HISTCONTROL


