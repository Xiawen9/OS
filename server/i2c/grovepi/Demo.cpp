#include <Config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    int greenLed = open("/dev/grove/digital4", O_WRONLY);
    int button   = open("/dev/grove/digital3", O_RDONLY);
    int light    = open("/dev/grove/analog0", O_RDONLY);
    int lcd      = open("/dev/grove/lcd", O_WRONLY);
    char buf[32], text[32];

    if (greenLed < 0 || button < 0 || light < 0 || lcd < 0)
    {
        printf("%s: failed to open GrovePi devices: %s\n",
                argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    while (1)
    {
        // Reset fds
        lseek(button, 0, SEEK_SET);
        lseek(greenLed, 0, SEEK_SET);
        lseek(light, 0, SEEK_SET);
        lseek(lcd, 0, SEEK_SET);

        // Copy button value to the green LED
        read(button, buf, sizeof(buf));
        write(greenLed, buf, 1);

        // Display light status on the LCD
        read(light, buf, sizeof(buf));
        snprintf(text, sizeof(text), "light: %s\nOS %s",
                 buf, VERSION);
        write(lcd, text, sizeof(text));

        // Sleep a bit
        sleep(1);
    }

    return EXIT_SUCCESS;
}
