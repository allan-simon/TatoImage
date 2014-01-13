TatoImage
=========

Image manipulation, avatar caching etc. as a service

The goal is to provide a set of easy to use API call in order to remove complex image manipulation from main application code. A typical example would be user avatar management. In one API call, the image uploaded by the user is normalized, created in different size and thumbnails version, and after different versions are accessible from a URL.

If necessary everything can be done in memory without any mandatory disk write (for the moment a disk write is made for backup data persistence purpose)


##Compile

For this you need

  * cppcms (precompiled package if not provided by your distribution can be found here [http://cppcms.com/wikipp/en/page/apt](http://cppcms.com/wikipp/en/page/apt) )
  * cppcms-skeleton (can be found in my github)
  * magick++ ( `apt-get install libmagick++-dev` on ubuntu)
  * cmake
  * a recent C++ compiler  (gcc4.6+ or clang3.1+ should do the trick)



After this simply do

     cd app
     mkdir build
     cd build
     cmake ..
     make

and to run from build directory

     ./TatoImage -c ../config.js

and then in your browser you can do quick test by going on

     http://127.0.0.1:8080/images/normalize-avatar


##Hacking the code

  * The interesting part (image manipulation) is made  `app/src/controllers/webs/Images.cpp`
