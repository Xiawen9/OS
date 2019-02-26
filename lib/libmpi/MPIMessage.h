#ifndef __LIBMPI_MPIMESSAGE_H
#define __LIBMPI_MPIMESSAGE_H

typedef struct MPIMessage
{
    union
    {
        int integer;
    };
}
MPIMessage;

#endif /* __LIBMPI_MPIMESSAGE_H */
