/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_test.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/18 10:14:19 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/05/20 10:26:45 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

/**
 * @param tokens global list variable that is adjusted every test with 
 * new input
 * @param begin global variable to assign beginning of the link list
 */
t_list	*tokens;
t_list	*begin;

/**
 * @brief creates token from the lexer and puts cmd_line inside
 * 
 * @param cmd_line is converted by the lexer to tokens
 */
static void	test_setup(const char *cmd_line)
{
	tokens = lexer(cmd_line);
	begin = tokens;
	if (cmd_line)
		TEST_ASSERT_NOT_NULL(tokens);
}

/**
 * @brief function to test if the string inside the tokens->token_data is 
 * equal to the testers string by valuating length and the content of the
 * given string. The corresponding type of the token is compared with the 
 * tokens->type and type;
 * 
 * @param test_string 
 * @param type 
 */
static void	compare_tokens(const char *test_string, t_token_type type)
{
	size_t	len;
	t_token	*tok;

	if (!tokens)
	{
		printf("No new token found");
		TEST_ABORT();
		return ;
	}
	tok = (t_token *)tokens->ct;
	TEST_ASSERT_EQUAL_STRING(test_string, tok->token_data);
	TEST_ASSERT_EQUAL_INT16(type, tok->type);
	len = ft_strlen(tok->token_data);
	TEST_ASSERT_EQUAL_UINT64(len, ft_strlen(test_string));
	tokens = tokens->next;
}

void	setUp(void)	{}

/**
 * @brief clears the list of tokens
 * 
 */
void	tearDown(void)
{
	ft_lstclear(&begin, token_delete);
	tokens = NULL;
	begin = NULL;
}

static void	test_1()
{
	test_setup("   testing    ");
	compare_tokens("testing", e_word);
}

static void	test_2()
{
	test_setup("  test   super test          meeee!");
	compare_tokens("test", e_word);
	compare_tokens("super", e_word);
	compare_tokens("test", e_word);
	compare_tokens("meeee!", e_word);
}

static void	test_3()
{
	test_setup("  echo   test\"\'d_commmas\"         | cat -e");
	compare_tokens("echo", e_word);
	compare_tokens("test\"\'d_commmas\"", e_word);
	compare_tokens("|", e_pipe);
	compare_tokens("cat", e_word);
	compare_tokens("-e", e_word);
}

static void	test_4()
{
	test_setup("  echo   test\'\"s_commmas\'         | cat -e");
	compare_tokens("echo", e_word);
	compare_tokens("test\'\"s_commmas\'", e_word);
	compare_tokens("|", e_pipe);
	compare_tokens("cat", e_word);
	compare_tokens("-e", e_word);
}

static void	test_5()
{
	test_setup("<echo \'$HOME\"\"\"\'    >test.txt");
	compare_tokens("<", e_s_in);
	compare_tokens("echo", e_word);
	compare_tokens("\'$HOME\"\"\"\'", e_word);
	compare_tokens(">", e_s_out);
	compare_tokens("test.txt", e_word);	
}

static void	test_6()
{
	test_setup("ls<<>>><> | | \"cat -e\"       cookies");
	compare_tokens("ls", e_word);
	compare_tokens("<<", e_d_in);
	compare_tokens(">>", e_d_out);
	compare_tokens(">", e_s_out);
	compare_tokens("<", e_s_in);
	compare_tokens(">", e_s_out);
	compare_tokens("|", e_pipe);
	compare_tokens("|", e_pipe);
	compare_tokens("\"cat -e\"", e_word);
	compare_tokens("cookies", e_word);
}

static void	test_7()
{
	test_setup("<< \"HELLO\"  \"HELLO\"\'WORLD\' ");
	compare_tokens("<<", e_d_in);
	compare_tokens("\"HELLO\"", e_word);
	compare_tokens("\"HELLO\"\'WORLD\'", e_word);
}

static void	test_8()
{
	test_setup("echo \'$HOME\"\"\"\'    >test.txt");
	compare_tokens("echo", e_word);
	compare_tokens("\'$HOME\"\"\"\'", e_word);
	compare_tokens(">", e_s_out);
	compare_tokens("test.txt", e_word);
}

static void	test_9()
{
	test_setup("funny\"test\'\'\'\" || >> hi << test.txt");
	compare_tokens("funny\"test\'\'\'\"", e_word);
	compare_tokens("|", e_pipe);
	compare_tokens("|", e_pipe);
	compare_tokens(">>", e_d_out);
	compare_tokens("hi", e_word);
	compare_tokens("<<", e_d_in);
	compare_tokens("test.txt", e_word);
}

static void	test_10()
{
	test_setup("cat | ls>>> < < >> << | echo HELLOOO world");
	compare_tokens("cat", e_word);
	compare_tokens("|", e_pipe);
	compare_tokens("ls", e_word);
	compare_tokens(">>", e_d_out);
	compare_tokens(">", e_s_out);
	compare_tokens("<", e_s_in);
	compare_tokens("<", e_s_in);
	compare_tokens(">>", e_d_out);
	compare_tokens("<<", e_d_in);
	compare_tokens("|", e_pipe);
	compare_tokens("echo", e_word);
	compare_tokens("HELLOOO", e_word);
	compare_tokens("world", e_word);
}

static void	test_11()
{
	test_setup("\"echo\" $HOME>");
	compare_tokens("\"echo\"", e_word);
	compare_tokens("$HOME", e_word);
	compare_tokens(">", e_s_out);
}

static void	test_12()
{
	test_setup("\"accept meeeee");
	compare_tokens("\"accept meeeee", e_word);
}

static void	test_13()
{
	test_setup("echo testje\"");
	compare_tokens("echo", e_word);
	compare_tokens("testje\"", e_word);
}

static void test_14()
{
	test_setup("cat |ls|");
	compare_tokens("cat", e_word);
	compare_tokens("|", e_pipe);
	compare_tokens("ls", e_word);
	compare_tokens("|", e_pipe);
}


static void test_15()
{
	test_setup("\"");
	compare_tokens("\"", e_word);
}

static void	test_16()
{
	test_setup("\"echo \" $HOME>>");
	compare_tokens("\"echo \"", e_word);
	compare_tokens("$HOME", e_word);
	compare_tokens(">>", e_d_out);
}

static void	test_17()
{
	test_setup("<hallo<hallo1<hallo2<hallo3>out");
	compare_tokens("<", e_s_in);
	compare_tokens("hallo", e_word);
	compare_tokens("<", e_s_in);
	compare_tokens("hallo1", e_word);
	compare_tokens("<", e_s_in);
	compare_tokens("hallo2", e_word);
	compare_tokens("<", e_s_in);
	compare_tokens("hallo3", e_word);
	compare_tokens(">", e_s_out);
	compare_tokens("out", e_word);
}

void	test_18(void)
{
	test_setup("< \"\"''$HOME''\"\"");
	compare_tokens("<", e_s_in);
	compare_tokens("\"\"''$HOME''\"\"", e_word);
}

int	lexer_test(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_1);
	RUN_TEST(test_2);
	RUN_TEST(test_3);
	RUN_TEST(test_4);
	RUN_TEST(test_5);
	RUN_TEST(test_6);
	RUN_TEST(test_7);
	RUN_TEST(test_8);
	RUN_TEST(test_9);
	RUN_TEST(test_10);
	RUN_TEST(test_11);
	RUN_TEST(test_12);
	RUN_TEST(test_13);
	RUN_TEST(test_14);
	RUN_TEST(test_15);
	RUN_TEST(test_16);
	RUN_TEST(test_17);
	RUN_TEST(test_18);
	return (UNITY_END());
}

int main(void)
{
	int	nr_fails;

	nr_fails = lexer_test();
	printf("#NR of failes in lexer -->: %d\n", nr_fails);
	return (0);
}