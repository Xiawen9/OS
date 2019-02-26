
/**
 * Returns an unsigned long containing the timestamp of converted from
 * the given values. I copied this code from the linux source in
 * kernel/time.c
 */
unsigned long mktime(const unsigned int year0, const unsigned int month0,
                    const unsigned int day, const unsigned int hour,
                    const unsigned int min, const unsigned int sec)
{
    unsigned int month = month0, year = year0;
    
    /* 1..12 -> 11,12,1..10 */
    if( 0 >= (int) (month -= 2))
    {
        month += 12; /* Puts Feb last since it has leap day */
        year -= 1;
    }
    
    return ((((unsigned long)
                (year/4 - year/100 + year/400 + 367*month/12 + day) +
                year*365 - 719499
            )*24 + hour /* now have hours */
        )*60 + min /* now have minutes */
    )*60 + sec; /* finally seconds */
}
