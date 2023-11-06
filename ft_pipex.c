/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrivas- <anrivas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:45:50 by anrivas-          #+#    #+#             */
/*   Updated: 2023/10/25 16:09:11 by anrivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_baby(char **path, char **env, char **argv, int *pipe)
{
	char	**args1;
	int		open_fd;
	char	*command;

	open_fd = open(argv[1], O_RDONLY);
	if (open_fd < 0)
		return (perror("Error al abrir el archivo de entrada"), 1);
	args1 = ft_split(argv[2], ' ');
	if (!args1)
		return (perror("Error al dividir el comando 1"), 1);
	command = get_command(path, args1[0]);
	if (command)
	{
		free(args1[0]);
		args1[0] = command;
	}
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	execve(args1[0], args1, env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_free(args1);
	return (perror("Error al ejecutar el comando 1"), 1);
}

int	ft_baby2(char **path, char **env, char **argv, int *pipe)
{
	char	**args2;
	int		open_fd;
	char	*command;

	open_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (open_fd < 0)
		return (perror("Error al abrir el archivo de salida"), 1);
	args2 = ft_split(argv[3], ' ');
	if (!args2)
		return (perror("Error al dividir el comando 2"), 1);
	command = get_command(path, args2[0]);
	if (command)
	{
		free(args2[0]);
		args2[0] = command;
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	execve(args2[0], args2, env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_free(args2);
	return (perror("Error al ejecutar el comando 2"), 1);
}

int	ft_fork2(char **argv, char **path, char **env, int *pipe)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		return (perror("Error al crear el proceso hijo"), 1);
	else if (pid2 == 0)
	{
		close(pipe[1]);
		return (ft_baby2(path, env, argv, pipe));
	}
	else
	{
		close(pipe[0]);
		close(pipe[1]);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}

int	ft_father(char **argv, char **path, char **env, int *pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Error al crear el proceso hijo"), 1);
	else if (pid == 0)
	{
		close(pipe[0]);
		return (ft_baby(path, env, argv, pipe));
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_fork2(argv, path, env, pipe);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		pipes[2];

	if (argc != 5)
	{
		perror("Uso incorrecto: ./pipex infile comando1 comando2 outfile");
		exit(1);
	}
	path = ft_find_path(env);
	if (!path)
	{
		perror("No se encontro PATH");
		exit(1);
	}
	if (pipe(pipes) == -1)
	{
		perror("Error al crear el tubo (pipe)");
		exit(1);
	}
	return (ft_father(argv, path, env, pipes));
}
