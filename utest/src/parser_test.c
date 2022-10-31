/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 08:45:45 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/11 11:39:59 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

t_parser 	*data;
t_list		*lst;
t_list		*b_lst;

t_light		*l;
t_camera	*cam;
t_alight	*al;

t_cylinder	*cyl;
t_plane		*pl;
t_sphere	*sph;

static void	pointer_test(void *ptr)
{
	TEST_ASSERT_NOT_NULL(ptr);
	if (!ptr)
		TEST_ABORT();
}

static void	test_setup(char *infile)
{
	data = parse_input_file(infile);
	pointer_test(data);
}

static void	testError(char *infile)
{
	int	status;
	pid_t f = fork();

	if (f == 0)
	{
		test_setup(infile);
		exit(0);
	}
	waitpid(f, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	TEST_ASSERT_EQUAL_INT(1, status);
	data = NULL;
}

static void	compare_tvec4(t_vec4 compare, t_vec4 actual)
{
	TEST_ASSERT_EQUAL_FLOAT(compare[0], actual[0]);
	TEST_ASSERT_EQUAL_FLOAT(compare[1], actual[1]);
	TEST_ASSERT_EQUAL_FLOAT(compare[2], actual[2]);
}

static void	compare_cylinder(t_vec4 cord, t_vec4 norm, float d, float h, t_vec4 colors, t_cylinder *actual)
{
	pointer_test(actual);
	compare_tvec4(cord, actual->cord);
	compare_tvec4(norm, actual->norm);
	compare_tvec4(colors, actual->colors);
	TEST_ASSERT_EQUAL_FLOAT(d, actual->d);
	TEST_ASSERT_EQUAL_FLOAT(h, actual->h);
}

static void compare_plane(t_vec4 cord, t_vec4 norm, t_vec4 colors, t_plane *actual)
{
	pointer_test(actual);
	compare_tvec4(cord, actual->cord);
	compare_tvec4(norm, actual->norm);
	compare_tvec4(colors, actual->colors);
}

static void compare_sphere(t_vec4 center, float d, t_vec4 colors, t_sphere *actual)
{
	pointer_test(actual);
	compare_tvec4(colors, actual->colors);
	TEST_ASSERT_EQUAL_FLOAT(d, actual->d);
}

static void	compare_light(t_vec4 cord, float b_rat, t_vec4 colors, t_light *actual)
{
	pointer_test(actual);
	compare_tvec4(cord, actual->cord);
	compare_tvec4(colors, actual->colors);
	TEST_ASSERT_EQUAL_FLOAT(b_rat, actual->b_rat);
}

static void	compare_camera(t_vec4 cord, t_vec4 norm, float fov, t_camera *actual)
{
	pointer_test(actual);
	compare_tvec4(cord, actual->cord);
	compare_tvec4(norm, actual->norm);
	TEST_ASSERT_EQUAL_FLOAT(fov, actual->fov);
}

static void compare_alight(float a_rat, t_vec4 colors, t_alight *actual)
{
	pointer_test(actual);
	compare_tvec4(colors, actual->colors);
	TEST_ASSERT_EQUAL_FLOAT(a_rat, actual->a_rat);
}

void	setUp(void) {}

void	tearDown()
{
	if (!data)
		return ;
	if (data->al)
		free(data->al);
	if (data->cam)
		free(data->cam);
	if (data->l)
		free(data->l);
	ft_lstdelone(data->cylinder, delete_structs);
	ft_lstdelone(data->plane, delete_structs);
	ft_lstdelone(data->sphere, delete_structs);
	free(data);
}

void	test1()
{
	test_setup("rt_files/simple.rt");
	compare_alight(0.2, (t_vec4){255,255,255}, data->al);
	compare_camera((t_vec4){-50, 0, 20}, (t_vec4){0, 0, 1.0}, 70, data->cam);
	compare_light((t_vec4){-40,0,30}, 0.7, (t_vec4){255,255,255}, data->l->ct);
	lst = data->plane;
	pointer_test(lst);
	pl = (t_plane *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_plane((t_vec4){0,0,0}, (t_vec4){0,1.0,0}, (t_vec4){255,0,225}, pl);
	lst = data->sphere;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = data->cylinder;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
}

void	test2()
{
	test_setup("rt_files/simple_spaces.rt");
	compare_alight(0.2, (t_vec4){255,255,255}, data->al);
	compare_camera((t_vec4){-50, 0, 20}, (t_vec4){0, 0, 1.0}, 70, data->cam);
	compare_light((t_vec4){-40,0,30}, 0.7, (t_vec4){255,255,255}, data->l->ct);
	lst = data->plane;
	pointer_test(lst);
	pl = (t_plane *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_plane((t_vec4){0,0,0}, (t_vec4){0,1.0,0}, (t_vec4){255,0,225}, pl);
	lst = data->sphere;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = data->cylinder;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	TEST_ASSERT_NULL(lst->next);
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
}

void	test3()
{
	test_setup("rt_files/simple_mulitple_PlSpCy.rt");
	compare_alight(0.2, (t_vec4){255,255,255}, data->al);
	compare_camera((t_vec4){-50, 0, 20}, (t_vec4){0, 0, 1.0}, 70, data->cam);
	compare_light((t_vec4){-40,0,30}, 0.7, (t_vec4){255,255,255}, data->l->ct);
	
	// plane
	lst = data->plane;
	pointer_test(lst);
	pl = (t_plane *)lst->ct;
	compare_plane((t_vec4){0,0,0}, (t_vec4){0,1.0,0}, (t_vec4){255,0,225}, pl);
	lst = lst->next;
	pointer_test(lst);
	pl = (t_plane *)lst->ct;
	compare_plane((t_vec4){0,0,0}, (t_vec4){0,1.0,0}, (t_vec4){255,0,225}, pl);
	lst = lst->next;
	pointer_test(lst);
	pl = (t_plane *)lst->ct;
	compare_plane((t_vec4){0,0,0}, (t_vec4){0,1.0,0}, (t_vec4){255,0,225}, pl);
	lst = lst->next;
	TEST_ASSERT_NULL(lst);
	
	// sphere
	lst = data->sphere;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = lst->next;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = lst->next;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = lst->next;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = lst->next;
	pointer_test(lst);
	sph = (t_sphere *)lst->ct;
	compare_sphere((t_vec4){0,0,20}, 20, (t_vec4){255,0,0}, sph);
	lst = lst->next;
	TEST_ASSERT_NULL(lst);
	
	// cyl
	lst = data->cylinder;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
	lst = lst->next;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
	lst = lst->next;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
	lst = lst->next;
	pointer_test(lst);
	cyl = (t_cylinder *)lst->ct;
	compare_cylinder((t_vec4){50.0,0.0,20.6}, (t_vec4){0,0,1.0}, 14.2, 21.42, (t_vec4){10,0,255}, cyl);
	lst = lst->next;
	TEST_ASSERT_NULL(lst);
}

void	fileDoesNotExist() {
	testError("file does not exist");
}

void	errorCamera() {
	testError("rt_files/wrongInputCamera.rt");
}

void	errorCamera2(){
	testError("rt_files/wrongInputCamera2.rt");
}

void	errorColor(){
	testError("rt_files/wrongInputColor.rt");
}

void	errorNorm(){
	testError("rt_files/wrongInputNorm.rt");
}

void	errorSource(){
	testError("rt_files/wrongInputSource.rt");
}

void	errorSource2(){
	testError("rt_files/wrongInputSource2.rt");
}

void	errorVector() {
	testError("rt_files/wrongInputVector.rt");
}

void	errorVector2() {
	testError("rt_files/wrongInputVector2.rt");
}

int	parser_test(void)
{
	UNITY_BEGIN();
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);

	RUN_TEST(fileDoesNotExist);
	RUN_TEST(errorCamera);
	RUN_TEST(errorCamera2);
	RUN_TEST(errorColor);
	RUN_TEST(errorNorm);
	RUN_TEST(errorSource);
	RUN_TEST(errorSource2);
	RUN_TEST(errorVector);
	RUN_TEST(errorVector2);
	return (UNITY_END());
}

int main(void)
{
	int	nr_fails;
	int fd;
	
	fd = open("tests/errors.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 2);
	nr_fails = parser_test();
	close(fd);
	printf("#NR of failes in lexer -->: %d\n", nr_fails);
	return (0);
}
