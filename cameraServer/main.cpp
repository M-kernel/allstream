#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "as_camera_server.h"
#include "as.h"


long creat_daemon(void);
void workFunc();
void server_exit();


int main(int argc, char *argv[])
{
#if AS_APP_OS == AS_OS_LINUX
    RUNNING_MOD runType = enBackGround;
    if (argc > 1 &&
        (0 == strncmp(argv[1], "-t", strlen("-t"))))
    {
        runType = enForeGround;
    }

    as_run_service(workFunc, runType, server_exit,CAMERASVR_CONF_FILE, 99);
#else
    workFunc();
#endif
    
    return 0;
}

void startexit()
{
#if AS_APP_OS == AS_OS_LINUX
    send_sigquit_to_deamon();
#endif
}


void server_exit()
{
    ASCameraSvrManager::instance().close();
    ASCameraSvrManager::instance().release();
    return;
}

void workFunc()
{
    int32_t ret = ASCameraSvrManager::instance().init();
    if (AS_ERROR_CODE_OK != ret)
    {
        return ;
    }
    ret = ASCameraSvrManager::instance().open();
    if (AS_ERROR_CODE_OK != ret)
    {
        return ;
    }
    
    as_sleep(10000);
    while (true)
    {
        as_sleep(100);
    }

    return ;
}
