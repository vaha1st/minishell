#ifndef READTERM_H
# define READTERM_H

# include <term.h>
# include <termios.h>
# include "minishell.h"

typedef struct s_hd {
	char	*stoper;
	char	*tail;
}	t_hd;

int		ft_putint(int ch);
int		read_history(int fd, t_node **node);
void	clear_buf(char *buf, int size);
void	previous_cmd(t_rl *rl, t_node **histnode);
void	next_cmd(t_rl *rl, t_node **histnode);
void	addchar(t_rl *rl);
void	delchar(t_rl *rl);
void	showchar(t_rl *rl);
void	sig_c(t_rl *rl);
void	end(t_rl *rl);
void	home(t_rl *rl);
void	left(t_rl *rl);
void	right(t_rl *rl);
void	wordend(t_rl *rl, int k, int end);
void	wordbegin(t_rl *rl, int k, int beg);
void	tabkey(t_rl *rl);
void	correct_rl(t_rl *rl);
t_rl	*init_rl(char *argv, char **envp);
void	writehist(t_rl *rl);
void	readterm(t_rl *rl, t_node **histnode);
void	casecore(t_rl *rl, t_node **histnode);
char	*readheredoc(t_rl *rl);
void	preread(t_rl *rl, struct termios *term);
void	add_rus(t_rl *rl);

#endif
