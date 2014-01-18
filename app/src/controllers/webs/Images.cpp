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
#include <curl/curl.h>

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
    storageFolder = "../data/images/";
    originalFolder = storageFolder + "original/";

    dispatcher().assign("/resize", &Images::resize, this);

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

    //TODO should be possible to preallocate memory
    std::string imageBuffer((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    //std::string imageBuffer(
    //    std::istreambuf_iterator<char>(data),
    //    std::istreambuf_iterator<char>()
    //);
    std::string imageName = form.filename.value();

    // we save to disk for persistence
    form.image.value()->save_to(
        originalFolder + imageName
    );

    cache().store_frame(
        imageName,
        imageBuffer
    );
}

/**
 * callback for curl writing data
 */
static size_t write_callback(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userData
) {
    ((std::string*)userData)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/**
 * Simple conversion between format string returned by imagemagick
 * and mime type that can be used by the browser
 */
 static std::string magick_format_to_mime(const std::string &format) {

    if (format == "Portable Network Graphics") {
        return "image/png";
    }

    if (format == "Joint Photographic Experts Group JFIF format") {
        return "image/jpg";
    }

    if (format == "CompuServe graphics interchange format") {
        return "image/gif";
    }

    return "application/octet-stream";
 }

/**
 *
 */
bool Images::get_image_and_params(std::string &imageBuffer) {
    if (request().request_method() != "GET") {
        return false;
    }

    cppcms::http::request::form_type getData = request().get();
    cppcms::http::request::form_type::const_iterator it;

    GET_FIELD(filename, "filename");
    GET_FIELD(online, "online");
    GET_FIELD(sizeStr, "size");

    if (online == "1") {
        return load_image_from_web(imageBuffer);
    }

    return load_image_buffer_from_cache(imageBuffer);
}

/**
 *
 */
void Images::resize() {

    std::string imageBuffer;
    if (!get_image_and_params(imageBuffer)) {
        return;
    }
    //TODO finish to implement this function

    Magick::Blob initialBlob(imageBuffer.data(), imageBuffer.length());
    Magick::Image workingImage(initialBlob);

    response().content_type(
        magick_format_to_mime(workingImage.format())
    );
    response().out() << imageBuffer;

}

/**
 *
 */
bool Images::load_image_from_web(
    std::string & imageBuffer
) {
    std::string urlEncodeFilename = cppcms::util::urlencode(filename);

    if (cache().fetch_frame(urlEncodeFilename, imageBuffer)) {
        return true;
    }

    // we do a curl request to get the file
    // and we write the result in a buffer
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, filename.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &imageBuffer);
    // http status code >= 400 will be considered as error
    curl_easy_setopt(handle, CURLOPT_FAILONERROR, true);

    CURLcode result = curl_easy_perform(handle);
    curl_easy_cleanup(handle);

    //TODO for the moment whatever the error we
    // always return a 404, would be better to have something more precise
    if (result != CURLE_OK) {
        response().status(404);
        response().out() << "404";
        return false;
    }

    cache().store_frame(
        urlEncodeFilename,
        imageBuffer
    );

    return true;
}

/**
 *
 */
bool Images::load_image_buffer_from_cache(
    std::string & imageBuffer
) {
    if (cache().fetch_frame(filename, imageBuffer)) {
        return true;
    }

    // if not in cache we test if we have the file on
    // disk
    std::ifstream file((originalFolder + filename).c_str());
    if (!file.good()) {
        response().status(404);
        response().out() << "404";
        return false;
    }

    // we read the file and put original data in cache
    //TODO should be possible to preallocate memory
    imageBuffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // TODO why this does not compile ?
    //imageBuffer.assign(
    //    (std::istreambuf_iterator<char>(file)),
    //    std::istreambuf_iterator<char>()
    //);
    file.close();

    cache().store_frame(
        filename,
        imageBuffer
    );
    return true;
}

/**
 *
 */
void Images::normalize_avatar() {

    std::string cachedNormalized = "normalize/" + sizeStr + filename;
    if (cache().fetch_page(cachedNormalized)) {
        response().content_type("image/png");
        return;
    }

    std::string imageBuffer;
    if (!get_image_and_params(imageBuffer)) {
        return;
    }
    response().content_type("image/png");

    // we first load our image from its string representation
    // to an Magick++ Image
    Magick::Blob initialBlob(imageBuffer.data(), imageBuffer.length());
    Magick::Image workingImage(initialBlob);

    //we prepare a  squarre transparent PNG image
    size_t size = std::stoul(sizeStr);
    Magick::Image blankImage(
        Magick::Geometry(size, size),
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
    workingImage.resize(Magick::Geometry(size, size));
    //and we paste it at top left of the "transparent" image
    blankImage.composite(workingImage, 0, 0, Magick::OverCompositeOp);
    blankImage.write(&initialBlob);

    std::string finalImage(
        static_cast<const char*>(initialBlob.data()),
        initialBlob.length()
    );

    response().out() << finalImage;

    cache().store_page(cachedNormalized);
}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers
} // End namespace tatoimage

