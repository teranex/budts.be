<?php
// geen comments
// geen edit
?>


<p>This post is titled <strong><?php echo $fields['title']->content; ?></strong> and was
written on <strong><?php echo $fields['created']->content; ?></strong> by <strong><?php echo $fields['name']->content; ?></strong></p>
<?php if ($fields['created']->raw != $fields['changed']->raw): ?>
<p>It was last updated on <strong><?php echo $fields['changed']->content; ?></strong>.</p>
<?php endif; ?>
<?php if ($fields['comment_count']->raw > 0): ?>
<p>It currently has <strong><?php echo $fields['comment_count']->content; ?></strong> comments and the
last comment was posted <strong><?php echo $fields['last_comment_timestamp']->content; ?></strong>.</p>
<?php else: ?>
<p>It currently has no comments</p>
<?php endif; ?>
<?php if ($fields['term_node_tid']->content): ?>
<p>This post was tagged with <strong><?php echo $fields['term_node_tid']->content; ?></strong></p>
<?php endif; ?>
