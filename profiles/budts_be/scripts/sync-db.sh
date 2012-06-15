#!/bin/bash

# `drush sql-sync from to` copies the 'from' database into the 'to' database.
# This script will prevent me from that one evening when I will flip the two arguments
# and, by accident, copy my dev database to the production database.

# synchronise the database from production to development
drush --yes sql-sync @budtsbe.prod @budtsbe.dev
