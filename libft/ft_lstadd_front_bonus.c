/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:16:09 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/01 13:16:33 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int main(void)
{
    t_list *list = NULL;
    
    ft_lstadd_front(&list, ft_lstnew("First"));
    ft_lstadd_front(&list, ft_lstnew("Second"));
    ft_lstadd_front(&list, ft_lstnew("Third"));
    
    while (list)
    {
        printf("%s\n", (char *)list->content);
        list = list->next;
    }
    
    return 0;
}*/