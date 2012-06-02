#!/bin/bash

# stop when any step fails
set -e

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( drush dd )

# bring the site back online
drush --yes vset maintenance_mode 0

# clear the cashes to remove any cashed maintenance pages
drush --yes cc all
