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

#include <cppcms/session_interface.h>
#include <cppcms/http_file.h>

#include <ImageMagick/Magick++.h>
#include "Images.h"


#include "contents/Images.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace tatoimage {
namespace controllers {
namespace webs {

Images::Images(cppcms::service& serv) :
    ::controllers::webs::Controller(serv)
{

    dispatcher().assign("/tatoeba-upload-avatar", &Images::tatoeba_upload_avatar, this);

    dispatcher().assign("/normalize-avatar", &Images::normalize_avatar, this);
    dispatcher().assign("/normalize-avatar_treat", &Images::normalize_avatar_treat, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
Images::~Images() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
void Images::tatoeba_upload_avatar() {

    contents::images::TatoebaUploadAvatar c;
    init_content(c);


    render("images_tatoeba_upload_avatar", c);
}

/**
 *
 */
void Images::normalize_avatar() {

    contents::images::NormalizeAvatar c;
    init_content(c);


    render("images_normalize_avatar", c);
}


/**
 *
 */
void Images::normalize_avatar_treat() {

    forms::images::NormalizeAvatar form;
    form.load(context());

    //if (!form.validate()) {
    //    go_back_to_previous_page();
    //    return;
    //}

    std::istream& data = form.image.value()->data();
    std::string str((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());

    Magick::Blob blog(str.c_str(), str.length());
    Magick::Image plop(blog);
    Magick::Image blankImage(
        Magick::Geometry(50, 50),
        Magick::Color(
            0,
            0,
            0,
            (Magick::Quantum) 65535
        )
    );
    blankImage.magick("PNG");
            
            
    plop.resize(Magick::Geometry(50,50));
    blankImage.composite(plop, 0, 0, Magick::OverCompositeOp);
    blankImage.write("prout.png");
    plop.write("plop45.png");
    //delete buffer;

}


// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
} // End namespace tatoimage

