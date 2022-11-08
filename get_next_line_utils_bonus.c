/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:36:30 by mtravez           #+#    #+#             */
/*   Updated: 2022/11/08 12:36:54 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//This function creates a new string from the string s from the index start
//and then returns the pointer
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	size = ft_strlen(s);
	if (len > size - start)
		len = size - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, &s[start], len);
	sub[len] = '\0';
	return (sub);
}

//This function returns the size of the given string
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//This function copies up to n bytes of array src into array dst
void	*ft_memcpy(void *dst, const void *src, int n)
{
	char	*source;
	char	*destiny;
	int		i;

	source = (char *) src;
	destiny = (char *) dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		destiny[i] = source[i];
		i++;
	}
	return (dst);
}

//This function creates a new string with the joint strings s1 and s2
char	*ft_strjoin(char *s1, char *s2)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;
	size_t	i;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 1);
	if (!joint)
		return (NULL);
	joint = ft_memcpy(joint, s1, sizes1);
	i = 0;
	while (i < sizes2)
	{
		joint[i + sizes1] = s2[i];
		i++;
	}
	joint[sizes1 + sizes2] = '\0';
	free(s1);
	free(s2);
	return (joint);
}

//This function is sympilar to ft_memcpy, but it behaves 
//more cautiously when both pointers overlap, copying the src into dst
//starting at the end
void	*ft_memmove(void *dst, const void *src, int len)
{
	char	*source;
	char	*destiny;
	int		i;

	i = len - 1;
	source = (char *) src;
	destiny = (char *) dst;
	if (dst == 0 && src == 0)
		return (0);
	if (destiny < source || destiny > source + len)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (i >= 0)
		{
			destiny[i] = source[i];
			i--;
		}
	}
	return (dst);
}
