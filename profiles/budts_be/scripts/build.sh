#!/bin/bash

# change to the root directory of our drupal installation
cd `drush dd`

# todo: remove most of core

# remove all contrib modules, libraries & themes
rm -r sites/all/modules/contrib/
rm -r sites/all/libraries/
rm -r sites/all/themes/tao/

# run drush make
drush -y make profiles/budts_be/budts_be.make .

# geshifilter downloads the libraries module but doesn't place it in the
# contrib subdir so we move it
mv sites/all/modules/libraries sites/all/modules/contrib/
