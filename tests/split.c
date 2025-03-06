#include "../minishell.h"

void    count_words_test(void)
{
    printf("Testing count words function:\n\n");

    char *str = "Bonjour je suis le delimiteur";
    printf("Bonjour je suis le delimiteur: Number of words counted with space delimiter: %d\n", count_words(str, ' '));

    char *str2 = "Essayons de compter les espaces  ";
    printf("Essayons de compter les espaces: Number of words counted: %d\n", count_words(str2, ' '));
}