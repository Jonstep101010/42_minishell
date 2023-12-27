#include "lexer.h"
#include "libft.h"
#include "struct.h"

void debug_print_table(const char *s, const bool *arr) {
	if (!s || !arr)
		return ;
	for (int i = 0; i <= (int)strlen(s); i++){
		fprintf(stderr, "i: [%d]: %d, %c\n", i, arr[i], s[i]);
	}
	for (int i = 0; i <= (int)strlen(s); i++){
		if (arr[i] == true)
			fprintf(stderr, "%d", arr[i]);
		else
			fprintf(stderr, "%d", arr[i]);
	}
	fprintf(stderr,"\n");
}

void debug_print_line(const char *s, const bool *arr) {
	if (!s || !arr)
		return ;
	for (int i = 0; i <= (int)strlen(s); i++){
		fprintf(stderr, "%c", s[i]);
	}
	fprintf(stderr,"\n");
	for (int i = 0; i <= (int)strlen(s); i++){
		if (arr[i] == true)
			fprintf(stderr, "%d", arr[i]);
		else
			fprintf(stderr, "%d", arr[i]);
	}
	fprintf(stderr,"\n");
}

t_lexer	ignore_quotes(const char *s, struct s_lexer *input)
{
	if (!s || !input)
		return (LEXER_NULL);
	if (input->singlequotes % 2 != 0 && (input->doublequotes % 2 == 0 || input->doublequotes == 0))
		;
	else if (!(input->doublequotes % 2 == 0 || input->singlequotes % 2 == 0))
		return (LEXER_UNBALANCED_QUOTES);
	input->ignore = bool_arr_zeroing(ft_strlen(s));
	range_ignore(s, input->ignore,'"');
	range_ignore(s, input->ignore,'\'');
	debug_print_line(s, input->ignore);
	return (LEXER_SUCCESS);
}

t_lexer	check_against_ignore(const char *s, struct s_lexer *input)
{
	int i;

	if (!s)
		return (LEXER_NULL);
	if (input->ignore == NULL)
		return (fprintf(stderr, "will result in segfault\n"), LEXER_NULL);
	// 	return (LEXER_UNBALANCED_QUOTES);
	i = 0;
	if (input->singlequotes > 0 && input->doublequotes == 0)
		return (LEXER_UNBALANCED_QUOTES);
	while (i < (int)input->len)
	{
		if (input->ignore[i] == false)
		{
			if (s[i] == '|')
				return (LEXER_PIPES);
			if (s[i] == '<' || s[i] == '>')
				return (LEXER_REDIRECTION);
			if (s[i] == '\'' || s[i] == '"')
				return (LEXER_UNBALANCED_QUOTES);
		}
		i++;
	}
	printf("passed check_against_ignore\n");
	return (LEXER_SUCCESS);
}
