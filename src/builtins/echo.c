#include "env.h"
#include "libft.h"
#include "builtins.h"
#include <stddef.h>

char	*occurs_exclusively(const char *expected, const char *actual);

static int	is_n_arg(const char *arg)
{
	if (occurs(arg, "-n")
		&& ft_strncmp(arg, "-n", 2) == 0)
			return (1);
	return (0);
}


// need to enable passthrough for env
static int	echo_default(char **cmd_arr, size_t writelen)
{
	size_t	n_args;
	// char	*location;
	// char	*tmp;

	n_args = arr_len((const char **)cmd_arr);
	if (writelen == 1 && (cmd_arr + writelen))
	{
		while (cmd_arr + writelen && is_n_arg(*(cmd_arr + writelen)))
			writelen++;
	}
	while (cmd_arr + writelen && *(cmd_arr + writelen) && writelen <= n_args)
	{
		// location = ft_strnstr(*(cmd_arr + writelen), "$", ft_strlen(*(cmd_arr + writelen)));
		// string contains $KEY somewhere
		// if (location && location + 1)
		// {
		// 	tmp = ft_strdup(location + 1);
		// 	if (!tmp)
		// 		return (-1);
		// 	char	*var[] = {"seom=env", "KEY=val", "other=none", NULL};
		// 	char	**owned = arr_dup((const char **)var);
		// 	location = get_var_val(owned, tmp);
		// }

		ft_printf(*(cmd_arr + writelen));
		if (writelen < n_args - 1)
			write(1, " ", 1);
		writelen++;
	}
	return (0);
}

int	echo(t_shell *shell)
{
	if (!shell->command || !*shell->command || !*(shell->command + 1))
		return (write(1, "\n", 1));
	if (occurs(*(shell->command + 1), "-n")
		&& ft_strncmp(*(shell->command + 1), "-n", 2) == 0)
			return (echo_default(shell->command + 1, 1));
	echo_default((shell->command + 1), 0);
	write(1, "\n", 1);
	return (0);
}


