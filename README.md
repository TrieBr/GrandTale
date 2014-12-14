GrandTale
=========

GrandTale is a 2D MMORPG Written in C++. 

Development began in 2010 and slowely made progress over a few years until it the project slowed down around 2012.


Dependencies:
Allegro
RakNet
Mysql++ (3.1.0)


On Windows:
Set Environment variable LIBALLEGRO_DIR to the directory allegro is in.
Compile allegro using cmake into the a folder called build-win32-msvc in the allegro folder.
Make sure Allegro is compiled with the following addons:
ttf
primitives
font
acodec
audio
image

Set LIBRAKNET_DIR to the directory RakNet is in.

On the server, you will need to set the directory for Mysql++ and mysql C connector