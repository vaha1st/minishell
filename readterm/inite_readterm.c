#include "../includes/readterm.h"

t_rl    *init_rl(char *argv)
{
    t_rl *rl;

    rl = malloc(sizeof(rl));
	rl->len = 28;
	rl->histnode = NULL;
	rl->history = ft_strjoin(get_absolute_path_process(argv), HISTORY);
	rl->fd = open(rl->history, O_RDWR | O_CREAT, 0777);
	read_history(rl->fd, &rl->histnode);
	rl->buf = (char *)malloc(BUF_SIZE);
	clear_buf(rl->buf, BUF_SIZE);
	rl->command_line = (char *)malloc(rl->len);
    return (rl);
}