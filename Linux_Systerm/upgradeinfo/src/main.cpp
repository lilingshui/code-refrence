
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#include "font.hpp"
#include "canvas.hpp"
#include "keyboardManage.hpp"
#include "messageform.hpp"

#define FIFO_PATH       "/tmp/upgradeinfo"
#define PATH_MENU       "/home/et1000/menu"
#define INIT_KILL_MENU    1
#define INIT_RESTORE_MENU 0

keyBoard * keyboard;
char msg_buf[256];


int env_init(int kill_menu)
{
    int ret = 0;
    
    ret = access(PATH_MENU, R_OK);
    if (ret < 0) 
    {
        return -1;
    }
    
    if (kill_menu) 
    {
        system("chmod -x /home/et1000/menu");
        system("killall -9 menu");
    } 
    else 
    {
        system("chmod +x /home/et1000/menu");
    }
    
    return 0;
}


int fifo_init(void)
{
    int ret = 0;
    
    ret = access(FIFO_PATH, R_OK);
    if(ret < 0) 
    {
        if(mkfifo(FIFO_PATH, S_IRUSR | S_IWUSR) < 0) 
        {
            perror("mkfifo");
            return -1;
        }
    }
    
    ret = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (ret < 0) 
    {
        perror("open fifo");
        unlink(FIFO_PATH);
        return -1;
    }
    
    return ret;
}


int fifo_end(int fd)
{
    close(fd);
    unlink(FIFO_PATH);
    return 0;
}


int main( int argc, char * argv[] )
{
    if(argc>1 && argv[1]!=NULL)
    {
        printf("the first param is:%s \n", argv[1]);
        messagebox.setmessage(argv[1]);
        messagebox.enable();
        return 0;
    }
    
    int fd = 0;
    int len = 0;
    
    fd = fifo_init();
    if (fd < 0) 
    {
        printf("fifo init error.\n");
        return -1;
    }
    
    env_init(INIT_KILL_MENU);
    sleep(1);
    
    Canvas::Init( );
    
    keyboard = new keyBoard();
    
    if (!keyboard) 
    {
        perror("keyboard error.");
        fifo_end(fd);
        return -1;
    }
    env_init(INIT_RESTORE_MENU);
    printf("line:%d, kill menu, open keyboard  \n", __LINE__);
    keyboard->SetKeyType( SIX_KEYS );
    
    messagebox.setmessage("U盘升级提示信息");
    messagebox.enable();
    
    while (1) 
    {
        memset(msg_buf, 0, sizeof(msg_buf));
        len = read(fd, msg_buf, sizeof(msg_buf));
        if (len > 0) 
        {
		//keyboard->lighton();
            printf("receive message:%s \n", msg_buf);
            messagebox.setmessage(msg_buf);
            messagebox.enable();
        }
		    
        usleep(100000);
    }
    
    fifo_end(fd);
    delete keyboard;
    
    return 0;
}
