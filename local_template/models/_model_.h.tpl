/**
 * TatoImage  Web API to wrap basic image manipulation
 *
 * Copyright (C) 2014 Allan SIMON <allan.simon@supinfo.com>
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category TatoImage
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @package  Models
 *
 */

#ifndef TATO_IMAGE_%%MODEL_INCLUDE%%
#define TATO_IMAGE_%%MODEL_INCLUDE%%

#include <cppcms_skel/models/SqliteModel.h>

namespace tatoimage {
namespace models {


/**
 * @class %%MODEL_NAME%% %%MODEL_DESCRIPTION%%
 *
 * @since %%MODEL_TODAY%%
 *
 */
class %%MODEL_NAME%% : public cppcmsskel::models::SqliteModel {
    public:
        /**
         * @brief Constructor
         * @since %%MODEL_TODAY%%
         */
        %%MODEL_NAME%%();

};

} // end namespace models
} // end namespace tatoimage

#endif
