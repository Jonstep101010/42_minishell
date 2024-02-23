#include "lexer.h"
#include <stdlib.h>

// @audit-info error  "cmd "'" hello" or any other unbalanced delimiters
// @follow-up free in caller and just get ref to struct?
t_lexer	lexer_checks_basic(const char *s)
{
	if (!s || !*s)
		return (LEXER_NULL);
	struct s_lexer	input;
	input.lexer = LEXER_NULL;
	count_number(s, &input);
	if (input.singlequotes == 1)
		return (LEXER_SINGLE_QUOTE);
	if (input.doublequotes == 1)
		return (LEXER_DOUBLE_QUOTE);
	if (input.singlequotes % 2 != 0 || input.doublequotes % 2 != 0)
		return (LEXER_UNBALANCED_QUOTES);
	if (input.singlequotes > 0 || input.doublequotes > 0)
		ignore_quotes(s, &input);
	if (check_pipes_redirection(s, &input) != LEXER_SUCCESS
		&& check_against_ignore(s, &input) != LEXER_SUCCESS)
		return (free(input.ignore), input.lexer);
	if (check_against_ignore(s, &input) != LEXER_SUCCESS)
		return (free(input.ignore), input.lexer);
	return (free(input.ignore), LEXER_SUCCESS);
}
