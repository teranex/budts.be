#!/bin/bash

# stop when any step fails
set -e

# check if a tag was provided or use the default one
if [ "${#1}" -gt 0 ]; then
    TAG=$1
else
    TAG="release-$( date +%Y%m%d )"
fi

DEV_BRANCH="drupal7"
STABLE_BRANCH="master"

echo "Going to use $TAG as tag"

# change to the root directory of our drupal installation
cd $( dirname "$0" ) && cd $( git rev-parse --show-toplevel )

echo "Changed to Drupal root: $PWD"

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
git tag -s $TAG

echo ""
echo "Release created. You can now push everything."
echo "Use \`git push --tags\` to push the newly created tag"
