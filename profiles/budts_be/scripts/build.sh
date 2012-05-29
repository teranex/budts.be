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

# remove most of core
rm -r includes/ misc/ modules/ scripts/ themes/
rm -r profiles/minimal/ profiles/standard/ profiles/testing/
rm *.txt *.php web.config

# remove all contrib modules, libraries & themes
rm -r sites/all/modules/contrib/
rm -r sites/all/libraries/
rm -r sites/all/themes/tao/

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
