static inline void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}