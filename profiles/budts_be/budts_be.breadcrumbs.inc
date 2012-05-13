<?php

function budts_be_install_breadcrumbs() {
  $nodes = array(
    array(
      'titles' => _string_from_args('weblog', '[node:created:custom:Y]'),
      'paths' => _string_from_args('weblog/', 'weblog/[node:created:custom:Y]'),
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
  _budts_be_batch_insert('custom_breadcrumb', $nodes);

  $vocabs = array(
    array(
      'name' => 'side wide tags',
      'titles' => 'tag',
      'paths' => 'tag',
      'vid' => 1,
      'visibility_php' => '',
    ),
  );
  _budts_be_batch_insert('custom_breadcrumbs_taxonomy_vocabulary', $vocabs);

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
      'titles' => _string_from_args('weblog', 'archive'),
      'paths' => _string_from_args('weblog', '[current-page:url:relative]'),
      'visibility_php' => '',
      'views_path' => 'weblog/%',
    ),
  );
  _budts_be_batch_insert('custom_breadcrumbs_views', $views);
}
