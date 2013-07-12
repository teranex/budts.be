#!/bin/bash

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( git rev-parse --show-toplevel )

# generate patch for .gitignore
git diff daa7b35 783e6a7 .gitignore > profiles/budts_be/patches/gitignore.patch

# generate patch for .htaccess
git diff 15cadf0 5817a77 .htaccess > profiles/budts_be/patches/1-htaccess.patch
git diff fce99d7 087eb49 .htaccess > profiles/budts_be/patches/2-htaccess.patch
git diff a9e68e0 6f884d0 .htaccess > profiles/budts_be/patches/3-htaccess.patch
git diff 4a70244 7ce5ec8 .htaccess > profiles/budts_be/patches/4-htaccess.patch
git diff 404073d 0349a31 .htaccess > profiles/budts_be/patches/5-htaccess.patch
git diff abf599b 38a9932 .htaccess > profiles/budts_be/patches/6-htaccess.patch

# generate patch for tagadelic: fix a php notice
git diff cd99231 fc22009 sites/all/modules/contrib/tagadelic/tagadelic.module > profiles/budts_be/patches/tagadelic-1435238-fix-php-notice.patch
git diff 199eedb f82fc9a sites/all/modules/contrib/tagadelic/tagadelic.info   > profiles/budts_be/patches/tagadelic-remove-version-info.patch
