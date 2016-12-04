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


## Compile ffmpeg && x264

Original topic: http://www.jeffreythompson.org/blog/2014/11/13/installing-ffmpeg-for-raspberry-pi/


### INSTALL H264 SUPPORT

	$ cd /usr/src
	$ sudo git clone git://git.videolan.org/x264
	$ cd x264
	$ sudo ./configure --host=arm-unknown-linux-gnueabi --enable-static --disable-opencl
	$ sudo make
	$ sudo make install


### INSTALL OTHER LIBRARIES/FORMATS
	
	Anything else you would like to install should be done now, before compiling FFMPEG. This includes MP3, AAC, etc.
	
### INSTALL FFMPEG

	$ cd /usr/src
	$ sudo git clone https://github.com/FFmpeg/FFmpeg.git ffmpeg
	$ cd ffmpeg
	$ sudo ./configure --arch=armel --target-os=linux --enable-gpl --enable-libx264 --enable-nonfree
	$ sudo make
	$ sudo make install

## How to enable raspberry pi camera module

	Original video: https://www.youtube.com/watch?v=T8T6S5eFpqE
	
If try short in one command:

	$ sudo raspi-config
	
	

