/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:31:12 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 12:49:49 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		s_len;

	s_len = ft_strlen(s) + 1;
	result = (char *)malloc(sizeof(char) * s_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, s_len);
	return (result);
}
