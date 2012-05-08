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

function trex7_field__taxonomy_vocabulary_1(&$variables) {
  $output = '';
  foreach ($variables['items'] as $link) {
    $output .= render($link).' ';
  }
  return $output;
}

function trex7_file_formatter_table($variables) {
  $header = array(t('Attachment'), t('Size'), t('Uploaded'));
  $rows = array();
  foreach ($variables['items'] as $delta => $item) {
    $rows[] = array(
      theme('file_link', array('file' => (object) $item)),
      format_size($item['filesize']),
      format_date($item['timestamp'], 'short'),
    );
  }

  return empty($rows) ? '' : theme('table', array('header' => $header, 'rows' => $rows));
}

