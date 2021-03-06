#include "../../includes/readterm.h"

void	next_cmd(t_rl *rl, t_node **histnode)
{
	if ((*histnode)->next)
	{
		free((*histnode)->content);
		(*histnode)->content = ft_strdup(rl->command_line);
		(*histnode) = (*histnode)->next;
		clear_buf(rl->command_line, rl->len);
		tputs(tgetstr("rc", 0), 1, ft_putint);
		tputs(tgetstr("ce", 0), 1, ft_putint);
		while ((int)ft_strlen((*histnode)->content) > rl->len
			 || (int)ft_strlen(rl->last_insert) > rl->len)
			mem_add(rl);
		if (!(*histnode)->next)
			ft_strcpy(rl->command_line, rl->last_insert);
		else
			ft_strcpy(rl->command_line, (*histnode)->content);
		rl->cursor_pos = ft_strlen(rl->command_line) + rl->plen;
		rl->count_symb = ft_strlen(rl->command_line) + rl->plen;
		write (1, rl->command_line, ft_strlen(rl->command_line));
	}
}
