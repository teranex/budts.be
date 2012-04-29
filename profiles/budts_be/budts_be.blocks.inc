<?php

function _build_pages_array() {
  return implode("\n", func_get_args());
}

function budts_be_install_blocks() {
  module_load_include('module', 'budts_be_general');

  // Enable some standard blocks.
  $default_theme = variable_get('theme_default', 'budts_be');
  $admin_theme = 'seven';

  $custom_blocks = array(
  );

  $query = db_insert('block_custom')->fields(array('bid', 'body', 'info', 'format'));
  foreach ($custom_blocks as $record) {
    $query->values($record);
  }
  $query->execute();

  $values = array(
    // for the default theme
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => 'budts_be',
      'status' => 1,
      'weight' => -2,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
    array(
      'module' => 'budts_be_general',
      'delta' => 'age_country_selector',
      'theme' => 'budts_be',
      'status' => 1,
      'weight' => -11,
      'region' => 'footer',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),

    // for the admin theme
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
    array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'help',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
    array(
      'module' => 'user',
      'delta' => 'login',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 10,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
  );
  _budts_be_install_blocks_in_db($values);

  $values = array(
    // array(
    //   'module' => 'budts_be_general',
    //   'delta'  => 'age_country_selector',
    //   'rid'    => 1,
    // ),
  );
  _budts_be_install_blocks_roles_in_db($values);
}

function _budts_be_install_blocks_in_db(array $values) {
  $query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'pages', 'cache', 'title', 'visibility'));
  foreach ($values as $record) {
    $query->values($record);
  }
  $query->execute();
}

function _budts_be_install_blocks_roles_in_db(array $values) {
  $query = db_insert('block_role')->fields(array('module', 'delta', 'rid'));
  foreach ($values as $record){
    $query->values($record);
  }
  $query->execute();
}

