<?php

function trex7_breadcrumb(&$variables) {
  if (!empty($variables) && count($variables['breadcrumb']) > 1) {
    return '<div class="breadcrumb">' . implode(' » ', $variables['breadcrumb']) . '</div>';
  } else {
    return '<div class="breadcrumb">' . l(variable_get('site_slogan', ''), '<front>')  . '</div>';
  }
}

function trex7_links__node(&$variables) {
  if (count($variables['links']) > 0) {
    $variables['heading'] = array(
      'text' => '» ',
      'level' => 'span',
    );
  }
  return theme_links($variables);
}

function trex7_preprocess_node(&$variables) {
  if (isset($variables['feed_nid'])) {
    $variables['feeds_item'] = feeds_item_info_load('node', $variables['nid']);
  }
}

function trex7_preprocess_page(&$variables) {
  if (isset($variables['main_menu'])) {
    $new_menu = array(
      'sl-twitter' => array('href' => 'http://twitter.com/teranex', 'title' => 'Twitter',),
      'sl-facebook' => array('href' => 'http://facebook.com/teranex', 'title' => 'Facebook',),
      'sl-github' => array('href' => 'http://github.com/teranex', 'title' => 'Github',),
      'sl-lastfm' => array('href' => 'http://lastfm.com/user/teranex', 'title' => 'Last.fm',),
      'sl-linkedin' => array('href' => 'http://www.linkedin.com/in/jeroenbudts', 'title' => 'Linkedin',),
    );
    $variables['main_menu'] = $new_menu + $variables['main_menu'];
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

function trex7_feed_icon(&$variables) {
  $text = t('Subscribe to @feed-title', array('@feed-title' => $variables['title']));
  if ($image = theme('image', array('path' => path_to_theme().'/images/rss.png', 'width' => 20, 'height' => 20, 'alt' => $text))) {
    return l($image, $variables['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon'), 'title' => $text)));
  }
}
