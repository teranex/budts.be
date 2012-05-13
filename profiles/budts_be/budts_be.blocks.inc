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
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -16,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
    array(
      'module' => 'views',
      'delta' => 'projects_overview-block_1',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -15,
      'region' => 'content',
      'pages' => 'projects',
      'cache' => 4,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      'module' => 'views',
      'delta' => 'activity_stream-block_2',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -14,
      'region' => 'content',
      'pages' => '<front>',
      'cache' => -1,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      // TODO: replace with custom block
      'module' => 'block',
      'delta' => '4',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => 0,
      'region' => 'footer',
      'pages' => '',
      'cache' => -1,
      'visibility' => 0,
      'title' => '',
    ),
    array(
      // TODO: replace with custom block
      'module' => 'block',
      'delta' => '3',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -17,
      'region' => 'sidebar_first',
      'pages' => _build_pages_array('activity-stream', 'activity-stream/*'),
      'cache' => -1,
      'visibility' => 1,
      'title' => 'Sources',
    ),
    array(
      'module' => 'views',
      'delta' => 'node_meta-block',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -16,
      'region' => 'sidebar_first',
      'pages' => 'weblog/*',
      'cache' => -1,
      'visibility' => 1,
      'title' => 'About this post',
    ),
    array(
      'module' => 'tagadelic',
      'delta' => '1',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -15,
      'region' => 'sidebar_first',
      'pages' => _build_pages_array('projects', 'projects/*', 'jeroen/cv', 'fotos', 'fotos/*', 'project/issues', 'project/issues/*', 'weblog/*'),
      'cache' => 8,
      'visibility' => 0,
      'title' => 'Tagcloud',
    ),
    array(
      'module' => 'views',
      'delta' => 'yearly_archive-block',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -14,
      'region' => 'sidebar_first',
      'pages' => _build_pages_array('weblog', 'weblog/*'),
      'cache' => -1,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      // TODO: replace with custom block
      'module' => 'block',
      'delta' => '2',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -13,
      'region' => 'sidebar_first',
      'pages' => 'jeroen/cv',
      'cache' => -1,
      'visibility' => 1,
      'title' => 'C.V.',
    ),
    array(
      'module' => 'menu_block',
      'delta' => '1',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -12,
      'region' => 'sidebar_first',
      'pages' => 'projects/*',
      'cache' => -1,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      'module' => 'views',
      'delta' => 'site_profiles-block_2',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -11,
      'region' => 'sidebar_first',
      'pages' => '<front>',
      'cache' => -1,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      'module' => 'views',
      'delta' => 'site_profiles-block_1',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -17,
      'region' => 'sidebar_second',
      'pages' => _build_pages_array('activity-stream', 'activity-stream/*'),
      'cache' => -1,
      'visibility' => 1,
      'title' => '',
    ),
    array(
      'module' => 'views',
      'delta' => 'activity_stream-block_1',
      'theme' => 'trex7',
      'status' => 1,
      'weight' => -16,
      'region' => 'sidebar_second',
      'pages' => _build_pages_array('projects', 'projects/*', 'jeroen/cv', 'fotos', 'fotos/*', 'project/issues', 'project/issues/*', 'activity-stream', 'activity-stream/*', '<front>'),
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
}

function _budts_be_install_blocks_in_db(array $values) {
  $query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'pages', 'cache', 'title', 'visibility'));
  foreach ($values as $record) {
    $query->values($record);
  }
  $query->execute();
}
