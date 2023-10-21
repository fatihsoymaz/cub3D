#ifndef CUB3D_H
# define CUB3D_H

# include "../include/get_next_line/get_next_line.h"
# include "../include/libft/libft.h"
# include "../include/mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_map
{
	char	**map;
	char	**map2;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	int		*c;
	int		*f;
	int		i;
	double	p_col;
	double	p_row;
	char	type;
	int		count;
	int		map_row;
	int		map_col;
}			t_map;

typedef struct s_data
{
	t_map	map;
}			t_data;

char		*ft_ret(char *str);
void		ft_err(void);
int			ft_wh_sp(char c);
int			count_wd(char *s);
int			count_comma(char *s);
int			ft_sp_ctrl(char *str);
void		path_check(t_data *fc);
void		control2(t_data *data, char *str);
int			*ft_ret_fc(char *str, char c);
void		ft_nosw(char *str, t_data *game);
void		ft_get_map2(t_data *data);
void		map_free(char **map);
char		*ft_strjoin_v2(char *str, char buffer, int len);
int			map_lines(char *str);
void		del_wspace(char **str);
void		free_func(t_data *data);
void		path_checker(char **str, t_data *data);
char		**duplicate_to_map(t_data *data);
void		ctrl(t_data *data);
void		space_full(char **str);
void		empty_line(char **str, int *k, t_data *data);
#endif