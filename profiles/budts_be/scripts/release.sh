#!/bin/bash

# stop when any step fails
set -e

DEV_BRANCH="drupal7"
STABLE_BRANCH="master"

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( drush dd )

# first test if the repository is clean
git diff-index --quiet HEAD
if [ $? -ne 0 ];
then
    echo "Working copy is not clean. Aborting."
    exit 1
fi

# then switch to our stable branch
git checkout $STABLE_BRANCH

# merge the development branch
git merge --no-ff -m "Merge development from branch: $DEV_BRANCH" $DEV_BRANCH

# then create a tag for this release
TAG="release-$( date +%Y%m%d )"
git tag -a $TAG

echo ""
echo "Release created. You can now push everything."
echo "Use \`git push --tags\` to push the newly created tag"
