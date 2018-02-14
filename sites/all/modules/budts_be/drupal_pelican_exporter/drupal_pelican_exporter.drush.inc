<?php

/**
 * Implements hook_drush_command().
 */
function drupal_pelican_exporter_drush_command() {

  $items['pelican-node-export'] = array(
    'description' => t('Export nodes to pelican'),
    'aliases' => array('pne'),
  );

  return $items;
}

function drush_drupal_pelican_exporter_pelican_node_export() {
    // $nodes = node_load_multiple([22615], ['type' => 'story']);
    $nodes = node_load_multiple(FALSE, ['type' => 'story']);
    $i = 1;
    foreach ($nodes as $nid => $node) {
        echo "Exporting node $i [nid: $node->nid]: $node->title\n";

        // title
        $title = $node->title;
        // body
        $body = $node->body['und'][0]['value'];
        // date
        $date = $node->created;
        // modified
        $modified = $node->changed;
        // slug
        $slug = end(explode('/', drupal_get_path_alias('node/'.$node->nid)));
        // tags
        $tags = _exporter_load_tags($node);

        $markdown = _format_markdown($title, $body, $date, $modified, $slug, $tags);

        // drupal_mkdir(drupal_dirname("public://")."exports/nodes/", TRUE);
        $target = variable_get('file_directory_path')."/exports/nodes/".date('Y', $date);
        mkdir($target, 0755, TRUE);
        file_put_contents($target."/".date('m', $date)."-$slug.md", $markdown);
        // file_save_data($markdown, "public://exports/nodes/$slug.md");

        $i++;
    }
}

function _exporter_load_tags($node) {
    $tids = [];
    foreach ($node->taxonomy_vocabulary_1['und'] as $tagref) {
        $tids[] = (int) $tagref['tid'];
    }
    $tag_objects = taxonomy_term_load_multiple($tids);
    $tags = [];
    foreach ($tag_objects as $tag_obj) {
        $tags[] = $tag_obj->name;
    }
    return $tags;
}

function _format_markdown($title, $body, $date, $modified, $slug, $tags = []) {
    $date = date('Y-m-d H:i', $date);
    $modified = date('Y-m-d H:i', $modified);
    $tags = _format_markdown_tags($tags);
    $markdown = <<<MD
---
title: "$title"
date: $date
modified: $modified
slug: $slug
$tags
...

$body
MD;
    return $markdown;
}

function _format_markdown_tags($tags) {
    if (empty($tags)) {
        return '';
    }
    $output = [];
    $output[] = 'tags:';
    foreach ($tags as $tag) {
        $output[] = "    - $tag";
    }
    return implode("\n", $output);
}
