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
         * @brief @TODO
         * @since 06 January 2014
         */
        void tatoeba_upload_avatar();

        /**
         * @brief @TODO add a description
         * @since 11 January 2014
         */
        void normalize_avatar();

        /**
         * @brief @TODO add a description
         * @since 11 January 2014
         */
        void normalize_avatar_treat();

// %%%NEXT_ACTION_MARKER%%% , do not delete

};

} // End namespace webs
} // End namespace controllers
} // End namespace tatoimage

#endif
