#!/bin/bash

# stop when any step fails
set -e

BACKUP_DIR="$HOME/backup"

# change to the directory of this script so we are in our drupal root (or should be)
cd $( dirname "$0" ) &&

drupal_root=$( drush dd )

if [ "$drupal_root" == "" ]; then
    echo "Could not find Drupal root. Aborting."
    exit 1
fi

# change to the root directory of our drupal installation
cd $drupal_root

# first set the site in maintenance mode
drush vset --always-set maintenance_mode 1

# remove previous backup and rename current backup to be the previous one
cd $BACKUP_DIR
rm -f *.prev
rename 's/(.sql)/$1.prev/' *.sql
cd -

# create a new backup
trim() { echo $1; }
database_name=$( drush status | grep "Database name" | sed -r "s/Database name\\s+:\\s+(.+)\\s+/\\1/" )
database_name=$( trim "$database_name" )
backup_file="$BACKUP_DIR/$database_name-$( date +%Y%m%d%H%M ).sql"
drush sql-dump --result-file=$backup_file

# make the sites/default folder writable
chmod u+w sites/default

# pull the new release. We assume that the correct branch is checked out
# and it is setup to track the correct remote
git pull

# and remove write permissions again
chmod u-w sites/default

# run any database updates
drush --yes updb
