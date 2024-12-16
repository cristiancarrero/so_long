/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:41:18 by ccarrero          #+#    #+#             */
/*   Updated: 2024/05/19 01:49:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_list	*lst_new(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

static void	lst_clear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	lst_clear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}

static void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = lst_new(set);
		if (!new_node)
		{
			del(set);
			lst_clear(&new_list, (*del));
			return (new_list);
		}
		lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
void *duplicate_content(void *content)
{
    return ft_strdup((char *)content);
}

void free_content(void *content)
{
    free(content);
}

void print_content2(void *content)
{
    printf("%s\n", (char *)content);
}

int main(void)
{
    t_list *list = ft_lstnew(ft_strdup("First"));

    t_list *duplicated_list = ft_lstmap(list, duplicate_content, free_content);

    printf("Lista original:\n");
    ft_lstiter(list, print_content2);

    printf("Lista duplicada:\n");
    ft_lstiter(duplicated_list, print_content2);

    ft_lstclear(&list, free_content);
    ft_lstclear(&duplicated_list, free_content);

    return 0;
}*/
