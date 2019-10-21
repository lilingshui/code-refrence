<1>将编译得出的可执行文件boa，拷到/sbin目录下。
cp boa /sbin

<2>将boa.conf拷贝到/etc/boa下
cp boa.conf /etc/boa

<3>在/var下新建log和www目录：
cd /var
mkdir log     					//创建日志文件所在目录
mkdir www     					//创建HTML文档的主目录
cd log
mkdir boa
cd /var/www
mkdir cgi-bin 					//创建CGI脚本所在录，并将生成的cgi拷贝到这个文件夹

<4>将index.html文件拷到/var/www下
cp index.html /var/www

chmod 777 /var/log/* 			//文件权限设定777表示所有人都可读、可写、可执行
chmod 777 /var/www/*

<5>将mime.types文件复制目标板根文件系统/etc目录下
cp mime.types /etc

<6>在终端上运行
boa &

<7>在浏览器上输入终端的IP地址，如http://192.168.244.10
即可看到服务器的测试界面