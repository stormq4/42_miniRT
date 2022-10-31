/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 08:45:45 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/15 15:07:58 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"


t_list		*tokens;
t_list		*b_tokens;
t_list		*commands;
t_list		*bc;
t_command	*cmd;

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
	bc = commands;
	TEST_ASSERT_NOT_NULL(commands);
}


static void	compare_red(t_list **lst, const char *test_string, t_token_type type)
{
	t_red	*input;
	size_t	len;

	if (!lst)
	{
		printf("No new token_lstfound");
		TEST_ABORT();
		return ;
	}
	input = (t_red *)(*lst)->ct;
	if (!input)
	{
		printf("No new token found");
		TEST_ABORT();
		return ;
	}
	TEST_ASSERT_EQUAL_INT16(type, input->type);
	TEST_ASSERT_EQUAL_STRING(test_string, input->file);
	len = ft_strlen(input->file);
	TEST_ASSERT_EQUAL_UINT64(len, ft_strlen(test_string));
	(*lst) = (*lst)->next;
}

static void	compare_exec(t_exec *exec, const char *test_string)
{
	TEST_ASSERT_NOT_NULL(exec->cmd);
	if (!exec->cmd)
	{
		TEST_ABORT();
		return ;
	}
	TEST_ASSERT_EQUAL_STRING(test_string, exec->cmd);
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

void	test_1()
{
	test_setup("< maan         test     ");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "maan", e_s_in);
	compare_exec(cmd->exec, "test");
}

void	test_2()
{
	test_setup("<< lekker ls| cat  >j >> grappig");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "lekker", e_d_in);
	compare_exec(cmd->exec, "ls");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "cat");
	compare_red(&cmd->out, "j", e_s_out);
	compare_red(&cmd->out, "grappig", e_d_out);
}

void	test_3()
{
	test_setup("cat | ls <in >>out >out1| cat -e");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "cat");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "in", e_s_in);
	compare_red(&cmd->out, "out", e_d_out);
	compare_red(&cmd->out, "out1", e_s_out);
	compare_exec(cmd->exec, "ls");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "cat -e");
}

void	test_4()
{
	test_setup("touch <<heredoc | ls -la | cat -e | <input >output");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "touch");
	compare_red(&cmd->in, "heredoc", e_d_in);
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "ls -la");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "cat -e");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "input", e_s_in);
	compare_red(&cmd->out, "output", e_s_out);
}

void	test_5()
{
	test_setup(" << \"heredoc mama \'mia\'\" <input /bin/cat >>append > output");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "/bin/cat");
	compare_red(&cmd->in, "\"heredoc mama \'mia\'\"", e_d_in);
	compare_red(&cmd->in, "input", e_s_in);
	compare_red(&cmd->out, "append", e_d_out);
	compare_red(&cmd->out, "output", e_s_out);
}

void	test_6()
{
	test_setup("<< heredoc << new heredoc << hd << hd s << hds1");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "heredoc s");
	compare_red(&cmd->in, "heredoc", e_d_in);
	compare_red(&cmd->in, "new", e_d_in);
	compare_red(&cmd->in, "hd", e_d_in);
	compare_red(&cmd->in, "hd", e_d_in);
	compare_red(&cmd->in, "hds1", e_d_in);
}

void	test_7()
{
	test_setup("echo komaaan cat poepjes op je muil");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "echo komaaan cat poepjes op je muil");	
}

void	test_8()
{
	test_setup("< hallo<hallo1<     hallo2 echo       \"good morning sir\" > hoi >hoi1>hooi>>hoiq");
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec,"echo \"good morning sir\"");
	compare_red(&cmd->in, "hallo", e_s_in);
	compare_red(&cmd->in, "hallo1", e_s_in);
	compare_red(&cmd->in, "hallo2", e_s_in);
	compare_red(&cmd->out, "hoi", e_s_out);
	compare_red(&cmd->out, "hoi1", e_s_out);
	compare_red(&cmd->out, "hooi", e_s_out);
	compare_red(&cmd->out, "hoiq", e_d_out);
}

void	test_9()
{
	test_setup("<<< hallo >echo>>echoo | echo pipe | cat -e");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "<", e_d_in);
	compare_exec(cmd->exec, "hallo");
	compare_red(&cmd->out, "echo", e_s_out);
	compare_red(&cmd->out, "echoo", e_d_out);
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "echo pipe");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "cat -e");
}

void	test_10()
{
	test_setup("<<      << hallo >echo cat>>echoo | echo pipe | << < < echo cat -e");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "<<", e_d_in);
	compare_exec(cmd->exec, "hallo cat");
	compare_red(&cmd->out, "echo", e_s_out);
	compare_red(&cmd->out, "echoo", e_d_out);
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_exec(cmd->exec, "echo pipe");
	commands = commands->next;
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "<", e_d_in);
	compare_red(&cmd->in, "echo", e_s_in);
	compare_exec(cmd->exec, "cat -e");
}

void	test_11(void)
{
	test_setup("< $HOME echo hallo");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "$HOME", e_s_in);
}

void	test_12(void)
{
	test_setup("< \"\"''$HOME''\"\"");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "\"\"''$HOME''\"\"", e_s_in);
}

void	test_13(void)
{
	test_setup("< \"\"'' $HOME ''\"\"");
	cmd = (t_command *)commands->ct;
	compare_red(&cmd->in, "\"\"''", e_s_in);
	compare_exec(cmd->exec, "$HOME ''\"\"");
}

int	parser_test(void)
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
	return (UNITY_END());
}

int main(void)
{
	int	nr_fails;

	nr_fails = parser_test();
	printf("#NR of failes in lexer -->: %d\n", nr_fails);
	return (0);
}
