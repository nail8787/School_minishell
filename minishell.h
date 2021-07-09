#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	struct	s_command
{
	char		*line;
	char		**args;
	char		**out_file;
	char		**in_file;
	int			out_append;
	int			left_pipe;
	int			right_pipe;
	int			err;
	int			quotes;
}				t_command;

typedef struct	s_error
{
	char		*err_iden;
}				t_error;

typedef struct	s_pipe
{
	int			*fds;
	int			temp_fd0;
}				t_pipe;

typedef struct	s_shell
{
	char		**env;
	char		*home;
	t_error		error;
	t_pipe		pipe;
	t_command	command;
}				t_shell;

typedef struct	s_cd {
	char		**env_new;
	int			pwd_i;
	int			oldpwd_i;
	int			home_i;
	char		*pwd;
	char		*oldpwd;
	char		*start_pwd;
	char		**temp_env;
	char		*str_tmp;
	char		**str_args;
}				t_cd;

int				get_next_line(int fd, char **line);
void			exec_command(t_shell *shell);
void			line_handler(t_shell *shell);
char			**copy_env(char **envv);
char			*get_env_val(t_shell *shell, char *name);
void			free_mass(char **mass);
void			free_command_struct(t_shell *shell);
void			memory_alloc_error();
char			**word_append(char **words, int *w);
char			**words_cpy(char **dest, char **src);
int				sym_append(char **word, char *line, int *i);
int				words_len(char **words);
char			**words_init(void);
char			*word_init(void);
int				command_init_default(t_shell *shell);
void			special_sym(t_shell *shell, char ***word, char *line, int *i);
void			single_quotes(char **word, char *line, int *i);
void			double_quotes(t_shell *shell, char ***word, char *line, int *i);
void			shield(char **word, char *line, int *i);
void			tilda(t_shell *shell);
void			dolla(t_shell *shell, char ***word, char *line, int *i);
char			*get_var_name(char *line, int *i);
int				set_redirect(t_shell *shell, char ***word, int redirect);
int				redirect_sym(t_shell *shell, int *i, int *redirect);
int				split_line(t_shell *shell);
int				add_sym_to_arg(t_shell *shell, char ***word, int *i);
int				multi_command(t_shell *shell, int *i);
int				create_arg(t_shell *shell, char ***word, int i,
							int *redirect_flag);
int				skip_space(char *line, int *i);
int				is_new_word(char *line, int i);
int				check_delimiter(char *delimiter, char *line, int i);
void			skip_shield(char *line, int *i);
void			skip_quotes(char *line, int *i, char quotes);
int				is_envvar_name(char *line, int i, int begin);
int				check_syntax(t_shell *sh);
void			skip_quotes_and_shield(char *line, int *i, int *flag);
void			pipe_semicolon_case(t_shell *shell, int *flag, int error);
void			out_redirect_case(t_shell *shell, int *flag);
void			in_redirect_case(t_shell *shell, int *flag);
void			print_syntax_error(int error, t_shell *shell);
void			ft_env(char **env_copy);
int				check_if_key_exists(char *str, char **env_old);
int				ft_unset(char *str, t_shell *shell);
int				ft_cd(char *str, t_shell *shell);
char			*trim_last_part_of_path(char **env_copy);
char			*get_home_path(char **env_copy, t_shell *shell);
char			**absolute_or_home_path(char *str, char **env_copy);
char			**change_relative_path(char *str, char **env_copy);
char			**relative_path(char **str_args, char **env_copy,
									t_shell *shell);
int				chdir_relative(char **str_args, char **env_copy,
									t_shell *shell);
int				ft_export(char *str, t_shell *shell);
char			**export_add_key(char *str, char **env_old);
void			export_no_args(char **env_copy);
int				start_binary(char *pathname, char **args, char **envs);
int				choose_cmd(t_shell *shell);
int				ft_pwd(void);
int				ft_echo(t_shell *shell);
void			error_check(t_shell *shell);
char			*prev_dir(char	**env_copy);
void			check_for_oldpwd(t_shell *shell);
int				check_if_value_exists(char *str);
void			check_for_pipe_and_rd(t_shell *shell);
void			ctrl_c_handler(int num);
void			ctrl_slash_handler(int num);
int				error_not_valid_iden(t_shell *shell);
int				error_not_oldpwd(t_shell *shell);
int				check_for_iden(char *str, t_shell *shell);
int				cd_chdir_tilda(t_shell *shell, t_cd *cd);
int				cd_chdir_dot_dot(t_shell *shell, t_cd *cd);
int				cd_chdir_minus(t_shell *shell, t_cd *cd);
void			change_question(int exit_status, t_shell *shell);
void			ft_exit(t_shell *shell);
void			normal_exit(t_shell *shell);
void			print_errors(char *str, t_shell *shell);
void			std_errno(t_shell *shell);
void			cmd_not_found(t_shell *shell);
void			binary_not_found(t_shell *shell);
void			perm_denied(t_shell *shell);
int				check_in_path(t_shell *shell);
int				open_fd(t_shell *shell);
void			is_pipe(t_shell *shell);
int				in_open_fd(t_shell *shell, int fd);
void			signals_init(void);
int				cd_chdir_absolute(t_cd *cd, char *str);
int				cd_chdir_dot(t_cd *cd);
int				child_left_redir(t_shell *shell);
int				cd_chdir_relative(t_cd *cd, char *str, t_shell *shell);
char			**chg_env_paths(char **env_copy, char *str, t_cd cd,
									t_shell *shell);
int				chdir_relative_dot(void);
int				chdir_relative_tilda(char **env_copy, t_shell *shell);
char			*pwd_save(void);
int				chdir_relative_dot_dot(char **env_copy);
void			get_home(t_shell *shell);
int				cd_chdir_relative_cycle(char **str_args, char **env_copy);
int				error_cd(t_shell *shell, t_cd *cd);
#endif
