/**
 * TatoImage  Web API to wrap basic image manipulation
 *
 * Copyright (C) 2014 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category TatoImage
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @package  Controllers
 * @link     https://github.com/allan-simon/tatoimage@
 *
 */

#ifndef TATO_IMAGECONTROLLERS_WEBS_IMAGES_H
#define TATO_IMAGECONTROLLERS_WEBS_IMAGES_H

#include <cppcms_skel/controllers/webs/Controller.h>


//needed to avoid to include models directly here,
//which would have the side effects to require to recompile the
// controller every time we modify a model. even though it does
// not affect the controller
namespace tatoimage {

namespace models {
    // %%%NEXT_CLASS_MODEL_CTRL_MARKER%%%
}

namespace controllers {
namespace webs {
/**
 * @class Images Image convertion
 * @since 06 January 2014
 */
class Images : public ::controllers::webs::Controller {
    public:
        /**
         * @brief Constructor
         * @since 06 January 2014
         */
        Images(cppcms::service &serv);

        /**
         * @brief Destructor
         * @since 06 January 2014
         */
        ~Images();

    private:
        // %%%NEXT_VAR_MODEL_CTRL_MARKER%%%

        /**
         * load an image from various location
         * into a buffer, the location etc. will depends on GET parameters
         * NOTE: in case of error, this function will write in the HTTP body
         * also load other parameters given in GET
         * @return boolean,  true if the image is loaded, false otherwise
         */
        bool get_image_and_params(std::string &imageBuffer);

        /**
         * try to load an image from cache or disk if available
         */
        bool load_image_buffer_from_cache(
            std::string &imageBuffer
        );

        /**
         * try to load an image from cache or web if available
         */
        bool load_image_from_web(
            std::string &imageBuffer
        );

        /**
         * @brief TODO
         * @since 06 January 2014
         */
        void upload_avatar();

        /**
         * @since 17 January 2014
         */
        void resize();

        /**
         * @brief TODO
         * @since 15 January 2014
         */
        void upload_avatar_treat();

        /**
         * normalize avatar for tatoeba's usage
         * @since 11 January 2014
         */
        void normalize_avatar();

        /**
         * in which folder to store the images
         */
        std::string storageFolder;

        /**
         * path where original images are stored on disk
         */
        std::string originalFolder;

        // TODO: we should specialize Image by type of transformation
        /**
         * name of the file to work on
         */
        std::string filename;

        /**
         * size of the output image
         */
        std::string sizeStr;

        /**
         *
         */
        std::string online;

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers
} // End namespace tatoimage

#endif
