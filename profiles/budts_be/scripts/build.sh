#!/bin/bash

# stop when any step fails
set -e

# change to the directory of this script so we are in our drupal root (or should be)
cd $( dirname "$0" ) &&

drupal_root=$( git rev-parse --show-toplevel )

if [[ $? != 0 ]]; then
    echo "Could not find Drupal root. Aborting."
    exit 1
fi

# change to the root directory of our drupal installation
 cd $drupal_root

# remove most of core
rm -r includes/ misc/ modules/ scripts/ themes/
rm -r profiles/minimal/ profiles/standard/ profiles/testing/
rm *.txt *.php web.config
rm .htaccess .gitignore

# remove all contrib modules, libraries & themes
rm -r sites/all/modules/contrib/
rm -r sites/all/libraries/
rm -r sites/all/themes/tao/

# make sites/default writable to avoid nagging from Drush make
chmod u+w sites/default/

# run drush make
drush -y make profiles/budts_be/budts_be.make .

# geshifilter downloads the libraries module but doesn't place it in the
# contrib subdir so we move it
mv sites/all/modules/libraries sites/all/modules/contrib/

# remove install and update. Not needed because we use Drush for these operations.
rm install.php update.php

# apply the local patches
for patch in profiles/budts_be/patches/*.patch
do
    echo "Applying $patch."
    patch -p1 < $patch > /dev/null
done
