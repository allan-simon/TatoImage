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

    dispatcher().assign("/upload-avatar", &Images::upload_avatar, this);
    dispatcher().assign("/upload-avatar_treat", &Images::upload_avatar_treat, this);


    dispatcher().assign("/normalize-avatar", &Images::normalize_avatar, this);
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
void Images::upload_avatar() {

    forms::images::UploadAvatar form;
    contents::images::UploadAvatar c;
    init_content(c);


    render("images_upload_avatar", c);
}

/**
 *
 */
void Images::upload_avatar_treat() {

    forms::images::UploadAvatar form;
    form.load(context());

    if (!form.validate()) {
        go_back_to_previous_page();
        return;
    }

    std::istream& data = form.image.value()->data();
    std::string imageBuffer((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    std::string imageName = form.filename.value();

    cache().store_frame(
        imageName,
        imageBuffer
    );
}


/**
 *
 */
void Images::normalize_avatar() {

    std::string filename = "";
    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
        
        GET_FIELD(filename, "filename");
    }

    response().content_type("image/png");
    if (cache().fetch_page("normalize/" + filename)) {
        return;
    }

    // if we don't have this file data we 404
    // TODO: we should test if we have it on disk
    std::string imageBuffer;
    if (!cache().fetch_frame(filename, imageBuffer)) {
        response().status(404);
        response().out() << "404";
        return;
    }

    // we first load our image from its string representation
    // to an Magick++ Image
    Magick::Blob initialBlob(imageBuffer.data(), imageBuffer.length());
    Magick::Image workingImage(initialBlob);

    //we prepare a transparent PNG image of 50*50 pixels
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

    //we resize the actual image to 50 for largest dimension
    //while keeping ratio
    workingImage.resize(Magick::Geometry(50,50));
    //and we paste it at top left of the "transparent" image
    blankImage.composite(workingImage, 0, 0, Magick::OverCompositeOp);
    blankImage.write(&initialBlob);

    std::string finalImage(
        static_cast<const char*>(initialBlob.data()),
        initialBlob.length()
    );

    response().out() << finalImage;

    cache().store_page("normalize/" + filename);

}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
} // End namespace tatoimage

