<?php if (!empty($pre_object)) print render($pre_object) ?>

<div class='activity-stream tweet <?php print $classes ?> clearfix' <?php print ($attributes) ?>>
  <?php if (!empty($title_prefix)) print render($title_prefix); ?>

  <?php if (!$page && !empty($title)): ?>
    <h2 <?php if (!empty($title_attributes)) print $title_attributes ?>>
      <?php if (!empty($new)): ?><span class='new'><?php print $new ?></span><?php endif; ?>
      <a href="<?php print $node_url ?>"><?php print $title ?></a>
    </h2>
  <?php endif; ?>

  <?php if (!empty($title_suffix)) print render($title_suffix); ?>

  <div class='<?php print $hook ?>-content clearfix <?php if (!empty($is_prose)) print 'prose' ?>'>
    <?php if (!empty($content)): ?>
      <?php hide($content['taxonomy_vocabulary_1']); ?>
      <?php print render($content) ?>
    <?php endif; ?>
    <?php if (isset($feeds_item)): ?>
    <a href="<?php echo $feeds_item->url; ?>"><?php echo $feeds_item->url; ?></a>
    <?php endif; ?>
  </div>

  <?php if (!empty($links)): ?>
    <div class='<?php print $hook ?>-links clearfix'>
      » <?php print render($links) ?>
    </div>
  <?php endif; ?>

  <div class="node-meta">
  <?php if (!empty($submitted)): ?>
    <div class='<?php print $hook ?>-submitted clear-block'><?php print $submitted ?>. <?php if (isset($content['taxonomy_vocabulary_1'])): ?>Tagged with <?php echo render($content['taxonomy_vocabulary_1']); ?><?php endif; ?> </div>
  <?php endif; ?>
  </div>
</div>

<?php if (!empty($post_object)) print render($post_object) ?>
