<div id="masthead">

  <div id="navi-menu-outer">
    <?php if ($main_menu): ?>
      <div id="navi-menu" class="navigation">
        <?php print theme('links__system_main_menu', array(
          'links' => $main_menu,
          'attributes' => array(
            'id' => 'main-menu-links',
            'class' => array('links', 'primary-links'),
          ),
        )); ?>
      </div> <!-- /#main-menu -->
    <?php endif; ?>
  </div>

  <div class="inside">
    <div id='header'><div class='limiter clear-block'>
        <?php print render($page['header']); ?>
    </div></div>

    <?php if ($site_name): ?><h1><?php print $site_name ?></h1><?php endif; ?>
    <?php if ($breadcrumb) print $breadcrumb; ?>
  </div>
</div>
<div id="outer-column-container">
  <div id="inner-column-container">
    <div id="source-order-container">
      <div id="middle-column">
        <div class="inside">
          <div class="clearfix" id="inner-topmenu">
          </div>

          <?php if ($show_messages && $messages): ?>
          <div id='console'><div class='limiter clear-block'>
              <?php if ($show_messages && $messages): print $messages; endif; ?>
          </div></div>
          <?php endif; ?>
          <div id='main' class='clear-block'>
            <?php if ($title): ?><h2 class='page-title'><?php print $title ?></h2><?php endif; ?>
            <?php if ($tabs) print render($tabs) ?>
            <div id='content' class='clear-block'><?php print render($page['content']); ?></div>
          </div>

        </div>
      </div>
      <div id="left-column">
        <div class="inside">
        </div>
      </div>
      <div class="clear-columns"><!-- do not delete --></div>
    </div>
    <div id="right-column">
      <div class="inside-sidebar normal-sidebar">
        <?php if ($page['sidebar_first']): ?>
        <div id='right' class='clear-block'><?php print render($page['sidebar_first']); ?></div>
        <?php endif; ?>
      </div>

      <div class="inside-sidebar extra-sidebar">
        <?php if ($page['sidebar_second']): ?>
        <?php echo render($page['sidebar_second']); ?>
        <?php endif; ?>
      </div>
    </div>
    <div class="clear-columns"><!-- do not delete --></div>
  </div>
</div>

<div id="footer"><div class='inside'>
    <?php print $feed_icons ?>
    <?php print render($page['footer']); ?>
</div></div>
