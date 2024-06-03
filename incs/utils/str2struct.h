/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:38:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:59:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

typedef int						(*t_parser_fn)(char *str, void *value,
							char **endptr);

typedef struct s_str2struct_entry
{
	size_t						offset;
	t_parser_fn					fun;
}								t_str2struct_entry;

typedef struct s_str2struct
{
	char						*str;
	char						*delimiter;
	const t_str2struct_entry	*entries;
	size_t						size;
	void						*value;
	char						**endptr;
}								t_str2struct;

int	str2struct(t_str2struct args)
{
	int		ret;
	size_t	i;

	i = 0;
	while (i < args.size)
	{
		ret = args.entries[i].fun(args.str, (unsigned char *)args.value
				+ args.entries[i].offset, &args.str);
		if (ret)
			return (ret);
		i++;
	}
	if (args.endptr)
		*args.endptr = args.str;
	return (0);
}
