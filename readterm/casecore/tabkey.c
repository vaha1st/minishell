#include "../../includes/readterm.h"

void	restore_line(t_rl *rl);

static char	**get_filenames(t_rl *rl)
{
	char	**name;
	char	*ptr;
	int		size;

	size = rl->cursor_pos - rl->plen - 1;
	while (rl->command_line[size] && rl->command_line[size] != ' ')
		size--;
	ptr = ft_substr(rl->command_line, size + 1, rl->cursor_pos - rl->plen
			 - size - 1);
	name = get_dir_content(get_absolute_path_process(ptr));
	free(ptr);
	return (name);
}

static void	show_same(t_rl *rl, int size, int wordlen, char *name)
{
	int		i;
	char	*tail;

	i = -1;
	while (++i < wordlen)
	{
		tputs(tgetstr("le", 0), 1, ft_putint);
		tputs(tgetstr("dc", 0), 1, ft_putint);
	}
	tputs(tgetstr("im", 0), 1, ft_putint);
	ft_putstr_fd(name, 1);
	tputs(tgetstr("ei", 0), 1, ft_putint);
	tail = ft_substr(rl->command_line, rl->cursor_pos - rl->plen,
			 rl->count_symb - rl->cursor_pos - rl->plen);
	while (ft_strlen(rl->command_line) + ft_strlen(name) > (size_t)rl->len)
		mem_add(rl);
	i = -1;
	while (name[++i])
		rl->command_line[size + 1 + i] = name[i];
	ft_strcpy(&rl->command_line[size + i + 1], tail);
	free(tail);
	rl->cursor_pos += ft_strlen(name) - wordlen;
	rl->count_symb += ft_strlen(name) - wordlen;
	rl->buf[0] = 0;
}

static void	try_complete(t_rl *rl, char **name)
{
	int		size;
	int		i;
	char	*ptr;
	int		wordlen;

	i = -1;
	size = rl->cursor_pos - rl->plen - 1;
	while (rl->command_line[size] && rl->command_line[size] != ' '
		 && rl->command_line[size] != '/')
		size--;
	wordlen = rl->cursor_pos - size - rl->plen - 1;
	ptr = ft_substr(rl->command_line, size + 1, wordlen);
	while (name[++i])
	{
		if (!ft_strncmp(ptr, name[i], wordlen) && ptr[0])
		{
			show_same(rl, size, wordlen, name[i]);
			break ;
		}
	}
	free(ptr);
	ft_arrfree(name);
}

static void	show_all(t_rl *rl, char **name)
{
	int		i;
	int		sp;

	i = 0;
	tputs(tgetstr("do", 0), 1, ft_putint);
	while (name[i])
	{
		ft_putstr_fd(name[i++], 1);
		if (name[i])
		{
			sp = 25;
			sp -= ft_strlen(name[i - 1]);
			if (i % 4 == 0)
				tputs(tgetstr("do", 0), 1, ft_putint);
			else
			{
				if (sp < 2)
					write(1, " ", 1);
				else
					while (sp--)
						write(1, " ", 1);
			}
		}
	}
	restore_line(rl);
}

void	tabkey(t_rl *rl)
{
	char	**name;

	name = get_filenames(rl);
	tputs(tgetstr("vi", 0), 1, ft_putint);
	if (rl->command_line[rl->cursor_pos - rl->plen - 1] != ' '
		 && rl->command_line[rl->cursor_pos - rl->plen - 1] != '/'
		 && rl->command_line[0])
		try_complete(rl, name);
	else
	{
		show_all(rl, name);
		ft_arrfree(name);
	}
	tputs(tgetstr("ve", 0), 1, ft_putint);
}
