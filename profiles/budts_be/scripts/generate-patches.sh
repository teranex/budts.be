#!/bin/bash

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( drush dd )

# generate patch for .gitignore
git diff daa7b35 783e6a7 .gitignore > profiles/budts_be/patches/gitignore.patch

# generate patch for .htaccess
git diff 15cadf0 5817a77 .htaccess > profiles/budts_be/patches/htaccess.patch

# generate patch for tagadelic: fix a php notice
git diff cd99231 fc22009 sites/all/modules/contrib/tagadelic/tagadelic.module > profiles/budts_be/patches/tagadelic-1435238-fix-php-notice.patch
