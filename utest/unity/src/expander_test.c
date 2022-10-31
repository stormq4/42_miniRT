/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 11:50:49 by gpirro        #+#    #+#                 */
/*   Updated: 2022/09/19 17:09:47 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

t_list		*tokens;
t_list		*b_tokens;
t_list		*commands;
t_list		*bc;
t_command	*cmd;
t_red		*in;
t_red		*out;
t_exec		*exec;


extern char	**environ;


static void	test_setup(const char *cmd_line)
{
	tokens = lexer(cmd_line);
	TEST_ASSERT_NOT_NULL(tokens);
	b_tokens = tokens;
	if (!parser(&tokens, &commands))
	{
		printf("Parser error");
		TEST_ABORT();
		return ;
	}
	TEST_ASSERT_NOT_NULL(commands);
	tokens = lexer(cmd_line);
	parser(&tokens, &commands);
	bc = commands;
	expander(&commands, environ);
	TEST_ASSERT_NOT_NULL(&commands);
}


void	setUp(void) {}

void	tearDown(void)
{
	ft_lstclear(&b_tokens, token_delete);
	ft_lstclear(&bc, parser_delete);
	tokens = NULL;
	commands = NULL;
	bc = NULL;
}


static void test_1(void)
{

	test_setup("< \"$LESS\"");
	cmd = (t_command *)commands->ct;
	in = (t_red *)cmd->in->ct;
	TEST_ASSERT_EQUAL_STRING("-R", in->file);
}

static void test_2(void)
{
	test_setup("< \"''\"$LESS\"''\"");
	cmd = (t_command *)commands->ct;
	in = (t_red *)cmd->in->ct;
	TEST_ASSERT_EQUAL_STRING("''-R''", in->file);
}

static void test_3(void)
{
	test_setup("> \"''\"$LESS\"''\"");
	cmd = (t_command *)commands->ct;
	out = (t_red *)cmd->out->ct;
	TEST_ASSERT_EQUAL_STRING("''-R''", out->file);
}

static void test_4(void)
{
	test_setup("echo $PAGER > $LESS");
	cmd = (t_command *)commands->ct;
	out = (t_red *)cmd->out->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo less", exec->cmd);
	TEST_ASSERT_EQUAL_STRING("-R", out->file);
}

static void test_6(void)
{
	test_setup("echo 999$SHLVL");
	cmd = (t_command *)commands->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo 9992", exec->cmd);
}

static void test_7(void)
{
	test_setup("echo hallo\"$SHLVL\"");
	cmd = (t_command *)commands->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo hallo2", exec->cmd);
}

static void test_8(void)
{
	test_setup("echo hallo\'$SHLVL\'");
	cmd = (t_command *)commands->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo hallo$SHLVL", exec->cmd);
}

static void test_9(void)
{
	test_setup("echo hallo\'$SHLVL\'\"$SHLVL\"");
	cmd = (t_command *)commands->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo hallo$SHLVL2", exec->cmd);
}

static void test_10(void)
{
	test_setup("echo $?");
	cmd = (t_command *)commands->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_EQUAL_STRING("echo 0", exec->cmd);
}

static void test_11(void)
{
	test_setup("echo $?");
	cmd = (t_command *)commands->ct;
	out = (t_red *)cmd->out->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_NOT_EQUAL("echo 1", exec->cmd);
}

static void test_12(void)
{
	test_setup("$LALA");
	cmd = (t_command *)commands->ct;
	out = (t_red *)cmd->out->ct;
	exec = (t_exec *)cmd->exec;
	
	TEST_ASSERT_EQUAL_STRING("$LALA", exec->cmd);
}

static void test_13(void)
{
	test_setup("$LALA");
	cmd = (t_command *)commands->ct;
	out = (t_red *)cmd->out->ct;
	exec = (t_exec *)cmd->exec;
	TEST_ASSERT_NOT_EQUAL("echo 1", exec->cmd);
}


/**
 * @brief runs all tests
 * 
 * @return int 
 */
int	expander_test(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_1);
	RUN_TEST(test_2);
	RUN_TEST(test_3);
	RUN_TEST(test_4);
	RUN_TEST(test_6);
	RUN_TEST(test_7);
	RUN_TEST(test_8);
	RUN_TEST(test_9);
	RUN_TEST(test_10);
	RUN_TEST(test_11);
	RUN_TEST(test_12);
	RUN_TEST(test_13);

	return (UNITY_END());
}

int	main(void)
{
	int	nr_fails;

	nr_fails = expander_test();
	printf("#NR of failes in export -->: %d\n", nr_fails);
	return (0);
}
