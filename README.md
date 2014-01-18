TatoImage
=========

Image manipulation, avatar caching etc. as a service

The goal is to provide a set of easy to use API call in order to remove complex image manipulation from main application code. A typical example would be user avatar management. In one API call, the image uploaded by the user is normalized, created in different size and thumbnails version, and after different versions are accessible from a URL.

If necessary everything can be done in memory without any mandatory disk write (for the moment a disk write is made for backup data persistence purpose)


##Using it

for the moment it provides only two API call

  * /images/resize which accept 3 mandatory parameters with GET, image type is preserverd:
    * `filename` can be simple filename or a URL (if URL you must set up  `online` to 1)
    * `size` final size of the biggest dimension of the image to manipulate, and it will keep ratio
    * `online` if we're working on an image uploaded on the server or an image on other server,  can be `0` (local) or `1` (URL)

    example:

         /images/resize?filename=http://upload.wikimedia.org/wikipedia/commons/e/e0/JPEG_example_JPG_RIP_050.jpg&size=500&online=1

 * /images/normalize-avatar :  it accepts the same parameters as resize, the only difference is that the result is a squarre PNG (the image type is not kept) with the original image resize at the bottom top and the remaining space being transparent

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
