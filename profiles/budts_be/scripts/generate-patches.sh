#!/bin/bash

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd `drush dd`

# generate patch for .gitignore
git diff c8dcf0d .gitignore > profiles/budts_be/patches/gitignore.patch

# generate patch for .htaccess
git diff 15cadf0 .htaccess > profiles/budts_be/patches/htaccess.patch
