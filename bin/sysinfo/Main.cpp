#include <System.h>
#include <FileSystemMessage.h>
#include <Timer.h>
#include <ChannelClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
    SystemInformation info;
    FileSystemMessage msg;
    Timer::Info timer;
    struct timeval tv;
    struct timezone tz;

    msg.type   = ChannelMessage::Request;
    msg.action = ReadFile;
    msg.from = SELF;
    ChannelClient::instance->syncSendReceive(&msg, CORESRV_PID);

    ProcessCtl(SELF, InfoTimer, (Address) &timer);
    gettimeofday(&tv, &tz);

    printf("Memory Total:     %u KB\r\n"
           "Memory Available: %u KB\r\n"
           "Processor Cores:  %u\r\n"
           "Timer:            %l ticks (%u hertz)\r\n"
           "Uptime:           %l.%us\r\n",
            info.memorySize / 1024,
            info.memoryAvail / 1024,
            msg.size,
            (u32) timer.ticks,
            timer.frequency,
            (u32) tv.tv_sec, tv.tv_usec);

    return EXIT_SUCCESS;
}
