char	*check_path(t_s *vs, char **cpath)
{
	int i;
	int j;
	int c;
	int k;
	char *tmp;

	k = 0;
	while (cpath[k])
	{
		c = 0;
		while (vs->env[c])
		{
			i = 0;
			j = 0;
			tmp = ft_calloc(sizeof(char), ft_strlen(cpath[k]) + ft_strlen(vs->env[c]) + 1);
			printf("allocating strlen:%lu\n",(ft_strlen(cpath[k]) + ft_strlen(vs->env[c]) + 1));
			while (vs->env[c][i++] != '\0')
				tmp[i] = vs->env[c][i];
			tmp[i++] = '/';
			while (cpath[k][j] != '\0')
				tmp[i++] = cpath[k][j++];
			tmp[--i] = '\0';


			printf("checking %s\n", tmp);
			printf("null bit at %d\n", i);

			if (access(tmp, F_OK) == 0)
			{
				cpath[k] = ft_strdup(tmp);
				printf("final: %s\n", tmp);
				printf("============FINISH===========\n");
				return(0);
			}
			free(tmp);
				printf("-----------------------------\n");
			c++;
		}
		k++;
	}
	return (NULL);
}
