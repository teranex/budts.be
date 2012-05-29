#!/bin/bash

# stop when any step fails
set -e

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( drush dd )

# generate patch for .gitignore
git diff daa7b35 783e6a7 .gitignore > profiles/budts_be/patches/gitignore.patch

# generate patch for .htaccess
git diff 15cadf0 5817a77 .htaccess > profiles/budts_be/patches/htaccess.patch
