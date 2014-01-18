TatoImage
=========

Image manipulation, avatar caching etc. as a service

The goal is to provide a set of easy to use API call in order to remove complex image manipulation from main application code. A typical example would be user avatar management. In one API call, the image uploaded by the user is normalized, created in different size and thumbnails version, and after different versions are accessible from a URL.

If necessary everything can be done in memory without any mandatory disk write (for the moment a disk write is made for backup data persistence purpose)


##Using it 

you can upload images directly to the server using its ugly upload page: `/images/upload-avatar`

Note: the filename field is what the API will wait if you want to manipulate that file
Note2: file uploaded that way get saved on disk, so that they can be retrieved if the server is shutdown and restarted


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

###Adding a new API call

  1. add a new method in `app/src/controllers/webs/Images.h`, for example `void wonderful_manipulation();`
  1. in constructor add a line  (the string part is totally up to you)

      dispatcher().assign("/wonderful-manipulation", &Images::wonderful_manipulation, this)

  1. put some boiler plate code in the implementation of your method
 

   ```c++   
        /**
         *
         */
        void Images::wonderful_manipulation() {
    
            std::string imageBuffer;
            if (!get_image_and_params(imageBuffer)) {
                return;
            }
            load_buffer_in_image(imageBuffer);
    
            //TODO put your code here
    
            response().content_type(
                magick_format_to_mime(workingImage.format())
            );
            output_image(workingImage);
        }
    ```
  
  1. put your own code where TODO comment is put, you can have access to your image using workingImage after its simply normal ImageMagick++ library call, no more, no less


###Going deeper

if you want to do more complex things take a look around, there's already utility function yo get the mime type, code to save/load from disk/cache/internet



