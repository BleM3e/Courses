#include "struct.h"
#include <stdio.h>
#include <assert.h>

int main (int argc, char *argv[])
{
    assert (argc > 1);

    struct sched s;

    init_sched (&s);

    fill_file (argv[1],&s);

    afficher (s);

    desallouer (&s);
    return 0;
}