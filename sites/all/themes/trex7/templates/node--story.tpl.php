<?php if (!empty($pre_object)) print render($pre_object) ?>

<div class='<?php print $classes ?> clearfix' <?php print ($attributes) ?>>
  <?php if (!empty($title_prefix)) print render($title_prefix); ?>

  <?php if (!$page && !empty($title)): ?>
    <h2 <?php if (!empty($title_attributes)) print $title_attributes ?>>
      <?php if (!empty($new)): ?><span class='new'><?php print $new ?></span><?php endif; ?>
      <a href="<?php print $node_url ?>"><?php print $title ?></a>
    </h2>
  <?php endif; ?>

  <?php if (!empty($title_suffix)) print render($title_suffix); ?>


  <?php if (!empty($content)): ?>
    <div class='<?php print $hook ?>-content clearfix <?php if (!empty($is_prose)) print 'prose' ?>'>
      <?php hide($content['taxonomy_vocabulary_1']); ?>
      <?php print render($content) ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($links)): ?>
    <div class='<?php print $hook ?>-links clearfix'>
      <?php print render($links) ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($submitted) && !$page): ?>
  <div class="node-meta">
      <div class='<?php print $hook ?>-submitted clear-block'><?php print $submitted ?>. <?php if (isset($content['taxonomy_vocabulary_1'])): ?>Tagged with <?php echo render($content['taxonomy_vocabulary_1']); ?><?php endif; ?> </div>
  </div>
  <?php endif; ?>
</div>

<?php if (!empty($post_object)) print render($post_object) ?>

<?php if (drupal_is_front_page()): ?>
<div class="read-blog"><a href="/weblog">Read more blog posts</a></div>
<?php endif; ?>
