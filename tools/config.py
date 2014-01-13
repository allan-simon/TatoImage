

# where the application code will be generated
# relative to the "tools" directory
APP_ROOT = "../app"

# this represent the logical structure of your code
# the script init will use this to generate a skeleton
# of code
ARCHITECTURE = {
    'controllers' : {
        'Images' : {
            'description': 'Image convertion',
            'methods' : {
                'tatoeba_upload_avatar' : {},
            }
        }
    },

    'models' : {},
    'models_controllers' : {}
}


# placeholders, replace the value by those specific to your
# project
REPLACEMENTS = {
    '@AUTHOR@' : 'Allan SIMON',
    '@EMAIL@': 'allan.simon@supinfo.com',
    '@PROJECT_NAME_CODE@' : 'TatoImage',
    '@PROJECT_NAME_HUMAN@': 'TatoImage',
    '@PROJECT_NS@': 'tatoimage',
    '@MAIN_CLASS@' : 'TatoImage',
    '@MAIN_CLASS_HEADER@' : 'TATO_IMAGE',
    '@DESCRIPTION@' : 'Web API to wrap basic image manipulation',
    '@PROJECT_WEBSITE' : 'https://github.com/allan-simon/tatoimage',
    '@YEARS@' : '2014',
    '    ' : '    ' #your prefered indentation, replace the second one
}

