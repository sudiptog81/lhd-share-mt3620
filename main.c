// This minimal Azure Sphere app repeatedly toggles an LED. Use this app to test that
// installation of the device and SDK succeeded, and that you can build, deploy, and debug an app.

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <applibs/gpio.h>
#include <applibs/log.h>

#include <hw/avnet_mt3620_sk.h>

typedef enum
{
    ExitCode_Success = 0,
    ExitCode_Main_Led = 1
} ExitCode;

int main(void)
{
    int fd_red = GPIO_OpenAsOutput(AVNET_MT3620_SK_USER_LED_RED, GPIO_OutputMode_PushPull, GPIO_Value_High);
    if (fd_red < 0)
    {
        Log_Debug(
            "Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
            strerror(errno), errno);
        return ExitCode_Main_Led;
    }

    int fd_green = GPIO_OpenAsOutput(AVNET_MT3620_SK_USER_LED_GREEN, GPIO_OutputMode_PushPull, GPIO_Value_High);
    if (fd_green < 0)
    {
        Log_Debug(
            "Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
            strerror(errno), errno);
        return ExitCode_Main_Led;
    }

    int fd_blue = GPIO_OpenAsOutput(AVNET_MT3620_SK_USER_LED_BLUE, GPIO_OutputMode_PushPull, GPIO_Value_High);
    if (fd_blue < 0)
    {
        Log_Debug(
            "Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
            strerror(errno), errno);
        return ExitCode_Main_Led;
    }

    const struct timespec sleepTime = {.tv_sec = 1, .tv_nsec = 0};
    while (true)
    {
        GPIO_SetValue(fd_red, GPIO_Value_Low);
        nanosleep(&sleepTime, NULL);
        GPIO_SetValue(fd_red, GPIO_Value_High);
        nanosleep(&sleepTime, NULL);

        GPIO_SetValue(fd_green, GPIO_Value_Low);
        nanosleep(&sleepTime, NULL);
        GPIO_SetValue(fd_green, GPIO_Value_High);
        nanosleep(&sleepTime, NULL);

        GPIO_SetValue(fd_blue, GPIO_Value_Low);
        nanosleep(&sleepTime, NULL);
        GPIO_SetValue(fd_blue, GPIO_Value_High);
        nanosleep(&sleepTime, NULL);
    }
}
