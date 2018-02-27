<?php

/**
 * Implements hook_drush_command().
 */
function drupal_pelican_exporter_drush_command() {

  $items['pelican-node-export'] = array(
    'description' => t('Export nodes to pelican'),
    'aliases' => array('pne'),
  );
  $items['pelican-comment-export'] = array(
    'description' => t('Export comments to pelican'),
    'aliases' => array('pce'),
  );

  return $items;
}

function drush_drupal_pelican_exporter_pelican_comment_export() {
    $nodes = node_load_multiple(FALSE, ['type' => 'story']);
    // $nodes = node_load_multiple([22591, 21004], ['type' => 'story']);
    $i = 1;
    foreach ($nodes as $nid => $node) {
      $cids = comment_get_thread($node, COMMENT_MODE_THREADED, 10000);
      $comments = comment_load_multiple($cids);

      foreach ($comments as $cid => $comment) {
        if ($comment->status) {
          $node_slug = end(explode('/', drupal_get_path_alias('node/'.$node->nid)));

          // date
          $date = $comment->created;
          // author
          $author = $comment->name;
          // email
          $email = $comment->mail;
          // website
          $homepage = $comment->homepage;
          // body (title + body)
          $subject = $comment->subject;
          $body = $comment->comment_body['und'][0]['safe_value'];

          // slug
          $slug_pieces = explode('.', str_replace('/', '', $comment->thread));
          $slug = implode('-', $slug_pieces);
          // replyto
          array_pop($slug_pieces);
          $replyto = implode('-', $slug_pieces);

          $markdown = _format_comment_markdown($date, $author, $email, $homepage, $subject, $body, $slug, $replyto);

          $target = variable_get('file_directory_path')."/exports/comments/".$node_slug;
          mkdir($target, 0755, TRUE);
          file_put_contents($target."/".$slug.".md", $markdown);
        }
      }
    }
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

function _format_comment_markdown($date, $author, $email, $homepage, $subject, $body, $slug, $replyto) {
    $date = date('Y-m-d H:i', $date);
    if ($replyto) {
      $replyto = "\nreplyto: $replyto";
    }
    $markdown = <<<MD
---
date: $date
author: "$author"
email: $email
website: $homepage
slug: $slug $replyto
...

<p><strong>$subject</strong></p>

$body

MD;
    echo $markdown;

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
