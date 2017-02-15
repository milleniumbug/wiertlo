int main()
{
	int aaa[50] = {};
	int (*ass)[50] = &aaa;
	(*ass)[1] = 42;
}