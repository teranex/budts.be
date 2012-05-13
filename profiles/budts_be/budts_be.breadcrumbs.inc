<?php

function _build_titles_array() {
  return implode("\n", func_get_args());
}

function _build_paths_array() {
  return implode("\n", func_get_args());
}

function budts_be_install_breadcrumbs() {
  $nodes = array(
    array(
      'titles' => _build_titles_array('weblog', '[node:created:custom:Y]'),
      'paths' => _build_paths_array('weblog/', 'weblog/[node:created:custom:Y]'),
      'visibility_php' => '',
      'node_type' => 'story',
      'name' => 'story',
    ),
    array(
      'titles' => 'Activity Stream',
      'paths' => 'activity-stream',
      'visibility_php' => '',
      'node_type' => 'delicious_bookmark',
      'name' => 'delicious',
    ),
    array(
      'titles' => 'Activity Stream',
      'paths' => 'activity-stream',
      'visibility_php' => '',
      'node_type' => 'tweet',
      'name' => 'twitter',
    ),
  );

  $query = db_insert('custom_breadcrumb')->fields(array('titles', 'paths', 'visibility_php', 'node_type', 'name'));
  foreach ($nodes as $record) {
    $query->values($record);
  }
  $query->execute();

  $vocabs = array(
    array(
      'name' => 'side wide tags',
      'titles' => 'tag',
      'paths' => 'tag',
      'vid' => 1,
      'visibility_php' => '',
    ),
  );

  $query = db_insert('custom_breadcrumbs_taxonomy_vocabulary')->fields(array('name', 'titles', 'paths', 'vid', 'visibility_php'));
  foreach ($vocabs as $record) {
    $query->values($record);
  }
  $query->execute();

  $views = array(
    array(
      'name' => 'weblog-view',
      'titles' => 'weblog',
      'paths' => 'weblog/',
      'visibility_php' => '',
      'views_path' => 'weblog',
    ),
    array(
      'name' => 'Archive view',
      'titles' => _build_titles_array('weblog', 'archive'),
      'paths' => _build_titles_array('weblog', '[current-page:url:relative]'),
      'visibility_php' => '',
      'views_path' => 'weblog/%',
    ),
  );

  $query = db_insert('custom_breadcrumbs_views')->fields(array('name', 'titles', 'paths', 'visibility_php', 'views_path'));
  foreach ($views as $record) {
    $query->values($record);
  }
  $query->execute();
}
