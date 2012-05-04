<?php

function trex7_breadcrumb(&$variables) {
  if (!empty($variables) && count($variables['breadcrumb']) > 1) {
    return '<div class="breadcrumb">' . implode(' » ', $variables['breadcrumb']) . '</div>';
  } else {
    return '<div class="breadcrumb">' . l(variable_get('site_slogan', ''), '<front>')  . '</div>';
  }
}

function trex7_preprocess_node(&$variables) {
  if (isset($variables['feed_nid'])) {
    $variables['feeds_item'] = feeds_item_info_load('node', $variables['nid']);
  }
}
