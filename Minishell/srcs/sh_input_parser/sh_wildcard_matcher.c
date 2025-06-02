/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_wildcard_matcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:47 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 10:50:44 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_match_wildcard(const char *filename, const char *pattern)
{
	const char	*file_ptr;
	const char	*pat_ptr;
	const char	*next_match;

	file_ptr = filename;
	pat_ptr = pattern;
	while (*file_ptr)
	{
		next_match = NULL;
		while (*pat_ptr == '*')
			pat_ptr++;
		if (!*pat_ptr)
			return (*(pat_ptr - 1) == '*');
		if (!ft_strchr(pat_ptr, '*') || pat_ptr != pattern
			|| *pat_ptr == *file_ptr)
			next_match = ft_strchr(file_ptr, *pat_ptr);
		if (!next_match)
			return (0);
		file_ptr += (next_match - file_ptr);
		while (*file_ptr && *pat_ptr && *pat_ptr != '*'
			&& *(file_ptr++) == *(pat_ptr++));
	}
	while (*pat_ptr == '*')
		pat_ptr++;
	return (!*file_ptr && !*pat_ptr);
}

static void	fill_file_list(DIR *dir_stream, char ***file_list, char *pattern)
{
	struct dirent	*entry;

	entry = readdir(dir_stream);
	while (entry)
	{
		if (entry->d_name[0] != '.'
			&& sh_match_wildcard(entry->d_name, pattern))
			ft_strapp(file_list, ft_strdup(entry->d_name));
		entry = readdir(dir_stream);
	}
}

char	**sh_get_matching_files(char *pattern)
{
	char	**file_list;
	char	*cwd;
	DIR		*dir_stream;

	cwd = sh_get_pwd();
	if (!cwd)
		return (NULL);
	dir_stream = opendir(cwd);
	if (!dir_stream)
	{
		sh_display_error(ERR_NO_ENTRY, cwd);
		free(cwd);
		return (NULL);
	}
	free(cwd);
	file_list = NULL;
	fill_file_list(dir_stream, &file_list, pattern);
	closedir(dir_stream);
	return (file_list);
}

char	*sh_format_wildcard_matches(char ***file_array)
{
	char	*formatted;

	formatted = NULL;
	ft_sort_lowstrs_tab(*file_array, ft_tab_len(*file_array));
	return (ft_strsjoin(*file_array, ft_strdup(" "), 0b10));
}

void	sh_replace_wildcards(char **str)
{
	char	**matched_files;
	char	*formatted_output;
	char	*unquoted_str;

	unquoted_str = ft_strdup(*str);
	if (!unquoted_str)
		return ;
	matched_files = sh_get_matching_files(unquoted_str);
	free(unquoted_str);
	if (matched_files && *matched_files)
	{
		free(*str);
		formatted_output = sh_format_wildcard_matches(&matched_files);
		*str = ft_strdup(formatted_output);
		free(formatted_output);
	}
	ft_free_tab((void **)matched_files);
}
