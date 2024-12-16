/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:51:59 by marvin            #+#    #+#             */
/*   Updated: 2024/03/22 20:51:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int main(void)
{
    t_list *node = ft_lstnew("Hola Mundo");

    if (node)
    {
        printf("Nuevo nodo creado con éxito.\n");
        printf("Contenido del nodo: %s\n", (char *)node->content);
    }
    else
    {
        printf("Error al crear el nuevo nodo.\n");
    }

    return 0;
}*/