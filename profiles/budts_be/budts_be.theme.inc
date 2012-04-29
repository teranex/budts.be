<?php

function budts_be_install_theme() {
  // Enable the admin theme.
  db_update('system')
    ->fields(array('status' => 1))
    ->condition('type', 'theme')
    ->condition('name', 'seven')
    ->execute();
  variable_set('admin_theme', 'seven');
  variable_set('node_admin_theme', '1');

  // enable budts_be theme
  db_update('system')
    ->fields(array('status' => 1))
    ->condition('type', 'theme')
    ->condition('name', 'budts_be')
    ->execute();

  // set the site theme
  variable_set('theme_default', 'budts_be');
}

