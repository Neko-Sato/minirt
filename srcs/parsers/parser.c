/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:15:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:15:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/abstract_light.h"
#include "objects/camera.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

static void	apply(t_parser_ctx *ctx, t_parser_res *res, int err);
static void	ctx_del(t_parser_ctx *ctx);
static void	put_info(t_parser_ctx *ctx);

t_rt_errno	parser(const char *filename, t_parser_res *res)
{
	t_rt_errno		ret;
	t_parser_ctx	ctx;

	ctx = (t_parser_ctx){};
	ctx.filename = filename;
	ctx.stream = ft_file_new(open(ctx.filename, O_RDONLY), 0b10, 0, 1);
	if (!ctx.stream)
		return (FAILED_OPEN);
	while (ft_getline(&ctx.line, &ctx.line_size, ctx.stream) != -1)
	{
		ctx.str = ctx.line;
		ctx.lineno++;
		ret = parse_line(&ctx);
		if (ret)
			break ;
	}
	if (ret)
		put_info(&ctx);
	else if (ft_ferror(ctx.stream))
		ret = FAILED_READ;
	else if (!ft_feof(ctx.stream))
		ret = FAILED_ALLOCATE;
	apply(&ctx, res, !!ret);
	return (ctx_del(&ctx), ret);
}

static void	apply(t_parser_ctx *ctx, t_parser_res *res, int err)
{
	void	*tmp;

	if (err)
	{
		while (ft_xlstpop(&ctx->cameras, 0, &tmp, sizeof(tmp)) != -1)
			(void)(camera_del(tmp), free(tmp));
		while (ft_xlstpop(&ctx->lights, 0, &tmp, sizeof(tmp)) != -1)
			(void)(((t_abstract_light *)tmp)->_->del(tmp), free(tmp));
		while (ft_xlstpop(&ctx->figures, 0, &tmp, sizeof(tmp)) != -1)
			(void)(((t_abstract_figure *)tmp)->_->del(tmp), free(tmp));
	}
	else
	{
		res->cameras = ctx->cameras;
		res->lights = ctx->lights;
		res->figures = ctx->figures;
	}
}

static void	ctx_del(t_parser_ctx *ctx)
{
	ft_fclose(ctx->stream);
	free(ctx->line);
}

static void	put_info(t_parser_ctx *ctx)
{
	if (!ctx->str)
		return ;
	ft_putstr_fd("Parser Error in ", STDERR_FILENO);
	ft_putstr_fd((char *)ctx->filename, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putnbr_fd((int)ctx->lineno, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putnbr_fd((int)(ctx->str - ctx->line), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	(void)((int){write(STDERR_FILENO, ctx->line, ctx->str - ctx->line)});
	ft_putstr_fd("\033[01;31m", STDERR_FILENO);
	ft_putstr_fd(ctx->str, STDERR_FILENO);
	ft_putstr_fd("\033[0m\n", STDERR_FILENO);
}
