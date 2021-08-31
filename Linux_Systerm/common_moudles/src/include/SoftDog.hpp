#ifndef _SOFT_DOG_HPP_
#define _SOFT_DOG_HPP_

/************************************************************
* 2011-8-17 �޶�  by laolvu
*           ����ԭ�з����Ǳ���س��������������س��������Ӽ����������ַ������ܵ�����������ͬʱ����һ���ļ�����������
*           Ԥ�ϵ����⡣��ˣ��ĳ�һ������д������һ�����̶��ķ�����Ϊʵ�ִ�Ŀ�ģ�����ϵͳ����ʱ����Ϊԭ���ļ�������
*           ����س���ι��ʱ��ֻ��Ҫ��ι��ʱ��ϵͳ����ʱ��д�뵽�ļ��м��ɡ���س����ڼ��ʱ���緢���ļ��е�ϵͳ����ʱ����
*           ����ǰ��ϵͳ����ʱ�������������ʱ��(dead_seconds), �жϱ���س�������⣨û�м�ʱι��),��س���ɱ������س���
************************************************************/



#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#define SOFT_WATCH_PATH "/var/volatile/watch"


struct process_t
{
    long up_time;
    long dead_seconds;
    int pid;
    char name[40];
};


/*ι�����������dead_seconds��û��ι������˽��̽���������Ϊ��ֹƵ�������ļ���*/
/*�������Ӷ�ʱ����ʹ�õ���Feed�ļ��������5�����ϣ�ͬʱҪȷ�����С�����ι��ʱ�䣬*/
/*process_nameΪ�߳��������Ȳ��ܳ���39���ַ�*/
inline bool Feed(unsigned short dead_seconds, const char *process_name)
{
	int pid = getpid();
	if(pid<1)
	{
		return false;
	}

	struct sysinfo info;
	if (sysinfo(&info) != 0)
	{
		return false;
	}


	struct process_t process = { info.uptime, dead_seconds, pid, "" };
	memset(process.name, '\0', sizeof(process.name));
	strncpy(process.name, process_name, sizeof(process.name) - 1);

	char filename[sizeof(SOFT_WATCH_PATH) + 10];
	sprintf(filename, "%s/%d", SOFT_WATCH_PATH, pid);
	int fd = open(filename, O_RDWR | O_CREAT);
	if(fd < 0)
	{
		return false;
	}
	write(fd, &process, sizeof(process_t));
	close(fd);

	return true;
}

#endif /* _SOFT_DOG_HPP_*/
