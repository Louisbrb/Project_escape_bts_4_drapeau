#ifndef DEFINE_H
#define DEFINE_H

#define SCRIPT_FILE_PATH    "script.asc"
#define LOG_FILE_PATH       "log.txt"

#ifdef MX28_1024
#define MOTION_FILE_PATH    "/Darwin/Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "/darwin/Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "/darwin/Data/config.ini"

#define U2D_DEV_NAME0       "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

#endif // DEFINE_H
