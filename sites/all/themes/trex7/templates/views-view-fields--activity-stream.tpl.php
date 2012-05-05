<div class="activity-stream-item <?php echo $fields['type']->raw; ?>">
<h3><?php echo l($fields['title']->raw, $fields['url']->raw); ?></h3>
<p class="description"><?php echo $fields['body']->content; ?></p>
<p class="date"><?php echo $fields['view_node']->content; ?></p>
</div>
