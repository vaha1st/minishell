#include "../includes/readterm.h"

static void	casecore_2(t_rl *rl)
{
	if (!ft_strcmp(rl->buf, "\eb") || !ft_strcmp(rl->buf, "\e[1;5D"))
		wordbegin(rl, 0, 0);
	else if (!ft_strcmp(rl->buf, "\ef") || !ft_strcmp(rl->buf, "\e[1;5C"))
		wordend(rl, rl->cursor_pos, rl->count_symb);
	else if (!ft_strcmp(rl->buf, "\1") || !ft_strcmp(rl->buf, "\e[H"))
		home(rl);
	else if (!ft_strcmp(rl->buf, "\5") || !ft_strcmp(rl->buf, "\e[F"))
		end(rl);
	else if (rl->buf[0] == '\n')
		write (1, rl->buf, 1);
	else if ((!ft_isprint(rl->buf[0]) || rl->buf[1] != 0) && rl->buf[0] != '\4'
		&& rl->buf[0] != '\3' && rl->buf[0] != -47 && rl->buf[0] != -48)
		clear_buf(rl->buf, BUF_SIZE);
	else if (rl->cursor_pos < rl->count_symb)
		addchar(rl);
	else
		showchar(rl);
}

void	casecore(t_rl *rl, t_node **histnode)
{
	while (ft_strcmp(rl->buf, "\n") && ft_strcmp(rl->buf, "\3")
		&& (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0))
	{
		correct_rl(rl);
		read(0, rl->buf, BUF_SIZE);
		if (!ft_strcmp(rl->buf, "\e[A"))
			previous_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\e[B"))
			next_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\3"))
			sig_c(rl);
		else if (!ft_strcmp(rl->buf, "\t"))
			tabkey(rl);
		else if (!ft_strcmp(rl->buf, "\177"))
			delchar(rl);
		else if (!ft_strcmp(rl->buf, "\e[D"))
			left(rl);
		else if (!ft_strcmp(rl->buf, "\e[C"))
			right(rl);
		else
			casecore_2(rl);
	}
}

void	readterm(t_rl *rl, t_node **histnode)
{
	char	*bufstr;

	casecore(rl, histnode);
	add_rus(rl);
	writehist(rl);
	bufstr = readheredoc(rl);
	if ((size_t)rl->len < ft_strlen(bufstr))
	{
		free(rl->command_line);
		rl->command_line = bufstr;
		rl->len = ft_strlen(rl->command_line);
	}
	else
	{
		clear_buf(rl->command_line, rl->len);
		ft_strcpy(rl->command_line, bufstr);
		free(bufstr);
	}
}
