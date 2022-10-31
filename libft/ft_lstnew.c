/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:55:49 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/03/25 11:45:45 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	if (!content)
		return (NULL);
	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->ct = content;
	new_list->next = NULL;
	return (new_list);
}
