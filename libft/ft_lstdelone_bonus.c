/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:57:06 by marvin            #+#    #+#             */
/*   Updated: 2024/03/22 21:57:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
/*
void	free_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*node = ft_lstnew(ft_strdup("Hello, world!"));

	printf("Antes de eliminar el nodo:\n");
	printf("Contenido del nodo: %s\n", (char *)node->content);

	ft_lstdelone(node, &free_content);

	printf("\nEl nodo ha sido eliminado.\n");

	return (0);
}*/
