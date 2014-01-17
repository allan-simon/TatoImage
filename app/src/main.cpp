/**
 * TatoImage  Web API to wrap basic image manipulation
 *
 * Copyright (C) 2014 Allan SIMON <allan.simon@supinfo.com> 
 * See accompanying file COPYING.TXT file for licensing details.
 *
 * @category TatoImage
 * @author   Allan SIMON <allan.simon@supinfo.com> 
 * @package  Main
 *
 */

#include <curl/curl.h>
#include <iostream>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>
#include <cppcms/json.h>

#include <ImageMagick/Magick++.h>

#include "TatoImage.h"

#include "cppcms_skel/generics/Config.h"

using namespace std;
using namespace cppcms;

int main(int argc,char ** argv)
{
    //TODO send notice message to logs instead of cout

    curl_global_init(CURL_GLOBAL_ALL);

    Magick::InitializeMagick(*argv);
    service app(argc, argv);
    /*load some conf defined variables*/
    Config *conf = Config::get_instance();

    conf->sqlite3Path = app.settings().get<string>(
        "TatoImage.sqlite3.path"
    );

    Config::set_assets_url(
        app.settings().get<string>(
            "skel.assetsURL"
        )
    );

    Config::set_assets_folder(
        app.settings().get<string>(
            "skel.assetsFolder"
        )
    );

    /*start the graph database*/

    //singletons::ActionId::get_instance();
    /*instantiate the website application*/
    cout << "[NOTICE] website to be launched" << endl;

    //booster::intrusive_ptr<apps::Tatoeba> tatoApp = new apps::Tatoeba(app);

    app.applications_pool().mount(
        cppcms::applications_factory<tatoimage::apps::TatoImage>()
    );
    /*launch it */
    cout << "[NOTICE] website launched" << endl;
    app.run();
    cout << "[NOTICE] website stopped" << endl;

    /*time to destroy all the singletons*/
    //SearchEngine::kill();
    Config::kill();
    curl_global_cleanup();
}
