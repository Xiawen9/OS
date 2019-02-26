#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define PONG 0xaabbccdd

int main(int argc, char **argv)
{
    int id, buf, cores;
    MPI_Status status;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
    {
        printf("%s: failed to initialize MPI\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (MPI_Comm_rank(MPI_COMM_WORLD, &id) != MPI_SUCCESS)
    {
        printf("%s: failed to lookup MPI rank\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (id == 0)
    {
        if (MPI_Comm_size(MPI_COMM_WORLD, &cores) != MPI_SUCCESS)
        {
            printf("%s: failed to lookup MPI core count\n", argv[0]);
            return EXIT_FAILURE;
        }
        printf("%s: ping %d cores\n", argv[0], cores - 1);

        for (int i = 1; i < cores; i++)
        {
            if (MPI_Recv(&buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status) != MPI_SUCCESS)
            {
                printf("%s: failed to receive message from core%d\n",
                        argv[0], i);
                return EXIT_FAILURE;
            }
            if (buf == PONG)
                printf("%s: pong from core%d\n", argv[0], i);
            else
                printf("%s: invalid message %d from core%d\n", argv[0], buf, i);
        }
    }
    else
    {
        buf = PONG;

        if (MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
        {
            printf("%s: failed to send message to core0\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (MPI_Finalize() != MPI_SUCCESS)
    {
        printf("%s: failed to finalize MPI\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
