int str_len(char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;

    while(str[i] != '\0')
    {
        i++;
        len++;
    }

    return(len);
}