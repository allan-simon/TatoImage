/**
 * TatoImage  Web API to wrap basic image manipulation
 *
 * Copyright (C) 2014 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category TatoImage
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @package  Forms
 *
 */

#ifndef TATO_IMAGE_IMAGES_UPLOAD_AVATAR
#define TATO_IMAGE_IMAGES_UPLOAD_AVATAR


#include <cppcms/form.h>

namespace tatoimage {
namespace forms{
namespace images {

/**
 * @struct normalize_avatar @TODO
 * @since  11 January 2014
 *
 */
struct UploadAvatar : public cppcms::form {

    //%%%NEXT_WIDGET_VAR_MARKER%%%

    /**
     * @brief button to submit the form
     */
    cppcms::widgets::submit submit;
    cppcms::widgets::text filename;
    cppcms::widgets::file image;


    /**
     * @brief Constructor
     */
    UploadAvatar() {

        //%%%NEXT_WIDGET_ADD_MARKER%%%

        add(image);
        image.filename(
            booster::regex(".*\\.(jpg|jpeg|png|JPG|PNG)")
        );
        // magic for JPEG
        image.add_valid_magic("\xFF\xD8");
        // magic for PNG
        image.limits(0, 1024*1024);
        image.non_empty();

        add(filename);
        filename.name(
            cppcms::locale::translate("filename")
        );
        filename.non_empty();

        add(submit);
        submit.name(
            cppcms::locale::translate("submit")
        );
        submit.value("submit");
    }


};


} // end of namespace images
} // end of namespace forms
} // end of namespace tatoimage


#endif


