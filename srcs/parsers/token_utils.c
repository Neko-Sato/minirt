/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:21:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:11:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"

t_rt_errno	parse_blank(t_parser_ctx *ctx)
{
	char	*s;

	s = ctx->str;
	while (ft_isblank(*s))
		s++;
	if (ctx->str == s)
		return (INCORRECT_FORMAT);
	ctx->str = s;
	return (SUCCESS);
}

t_rt_errno	parse_text(t_parser_ctx *ctx, char *buf, size_t size)
{
	size_t	len;
	char	*s;

	s = ctx->str;
	if (ft_isalpha(*s) || *s == '_')
	{
		s++;
		while (ft_isalnum(*s) || *s == '_')
			s++;
	}
	len = s - ctx->str;
	if (!len || len >= size)
		return (INCORRECT_FORMAT);
	ft_strncpy(buf, ctx->str, len);
	buf[len] = '\0';
	ctx->str = s;
	return (SUCCESS);
}

t_rt_errno	parse_entry(t_parser_ctx *ctx, const t_parse_entry *entry)
{
	t_rt_errno	ret;
	char		buf[20];

	if (entry->name)
	{
		ret = parse_text(ctx, buf, sizeof(buf));
		if (ret)
			return (ret);
		if (ft_strcmp(buf, entry->name) || *ctx->str != ':')
			return (INCORRECT_FORMAT);
		ctx->str++;
	}
	return (entry->fun(ctx, entry->dst));
}

static inline t_rt_errno	parse_entries_internal(t_parser_ctx *ctx,
		const t_parse_entry *entry)
{
	t_rt_errno	ret;
	char		*s;

	s = ctx->str;
	ret = parse_blank(ctx);
	if (entry->name && ret == INCORRECT_FORMAT)
	{
		ctx->str = s;
		return (SUCCESS);
	}
	else if (ret)
		return (ret);
	ret = parse_entry(ctx, entry);
	if (entry->name && ret == INCORRECT_FORMAT)
	{
		ctx->str = s;
		return (SUCCESS);
	}
	return (ret);
}

t_rt_errno	parse_entries(t_parser_ctx *ctx, const t_parse_entry *entries,
		size_t size)
{
	t_rt_errno	ret;
	size_t		i;

	i = 0;
	ret = SUCCESS;
	while (!ret && i < size)
		ret = parse_entries_internal(ctx, &entries[i++]);
	return (ret);
}
