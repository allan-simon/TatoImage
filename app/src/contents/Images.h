/**
 * TatoImage  Web API to wrap basic image manipulation
 *
 * Copyright (C) 2014 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category TatoImage
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @package  Contents
 *
 */

#ifndef TATO_IMAGE_CONTENTS_IMAGES_H
#define TATO_IMAGE_CONTENTS_IMAGES_H

#include "cppcms_skel/contents/content.h"

#include "contents/forms/upload_avatar.h"
//%%%NEXT_CONTENT_FORM_INCLUDE_MARKER%%%

namespace tatoimage {
namespace contents {
namespace images {

/**
 * @class Images
 * @brief Base content for every action of Images controller
 * @since 06 January 2014
 */
struct Images : public ::contents::BaseContent {
};

/**
 * @struct UploadAvatar
 * @since  06 January 2014
 */
struct UploadAvatar : public Images {

    forms::images::UploadAvatar uploadAvatarForm;
    UploadAvatar() {

    }

};

//%%%NEXT_CONTENT_MARKER%%%

} // end of namespace images
} // end of namespace contents
} // end of namespace tatoimage

#endif
