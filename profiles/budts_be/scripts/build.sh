#!/bin/bash

# stop when any step fails
set -e

drupal_root=$( drush dd )

if [ "$drupal_root" == "" ]; then
    echo "Could not find Drupal root. Aborting."
    exit 1
fi

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $drupal_root

# todo: remove most of core
rm -v  -r includes/ misc/ modules/ scripts/ themes/
exit 1
rm -v  -r profiles/minimal/ profiles/standard/ profiles/testing/
rm -v  *.txt *.php

# remove all contrib modules, libraries & themes
rm -v  -r sites/all/modules/contrib/
rm -v  -r sites/all/libraries/
rm -v  -r sites/all/themes/tao/

# run drush make
drush -y make profiles/budts_be/budts_be.make .

# geshifilter downloads the libraries module but doesn't place it in the
# contrib subdir so we move it
mv sites/all/modules/libraries sites/all/modules/contrib/

# apply the local patches
for patch in profiles/budts_be/patches/*.patch
do
    echo "Applying $patch."
    patch -p1 < $patch > /dev/null
done
