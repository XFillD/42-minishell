static inline void	ft_putstr_fd(char *str, int fd)
{
	if (!str || fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
}