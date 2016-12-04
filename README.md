# rasprobotd2
Sources for rasprobotd2

## Clone repository to RPi

	$ sudo apt install git-core
	$ git clone https://github.com/sea-kg/rasprobotd2.git
	
## Compile

	
	$ sudo apt install g++ make qtchooser qt5-default libqt5websockets5 libqt5websockets5-dev
	$ cd rasprobotd2
	$ qmake && make
	
## Configure

	$ sudo ln -s `pwd`/etc/rasprobotd2 /etc/rasprobotd2
	$ sudo ln -s `pwd`/etc/init.d/rasprobotd2 /etc/init.d/rasprobotd2
	$ sudo ln -s `pwd`/bin/rasprobotd2 /usr/bin/rasprobotd2
	$ sudo update-rc.d -f rasprobotd2 remove
	$ sudo update-rc.d rasprobotd2 defaults
