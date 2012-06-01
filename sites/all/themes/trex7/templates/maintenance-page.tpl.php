<!DOCTYPE html>
<html>
  <head>
    <?php print $head ?>
    <?php print $styles ?>
    <title><?php print $head_title ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
    <meta property="og:image" content="<?php echo theme_get_setting('logo'); ?>" >
  </head>

  <body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>

<!--[if lte IE 7]><div style="background: #bd0101; color: white; text-align: center; font-family: sans-serif;"><div style="font-size: 200%;">
IMPORTANT: Internet Explorer 7 or below not supported.</div>
this website might not entirely work or look as intended in Internet Explorer 7 or below.<br>
Please upgrade to Internet Explorer 8 or higher, or try an alternate browser such as <a href="http://getfirefox.com" style="color: white; font-weight: bold;">Mozilla Firefox</a> 
(recommended!), Opera, Safari or Google Chrome.</div><![endif]-->

    <div id="page-container">
<div id="masthead">

  <div id="navi-menu-outer">
  </div>

  <div class="inside">
    <div id='header'><div class='limiter clear-block'>
        <?php print render($page['header']); ?>
    </div></div>

    <?php if ($site_name): ?><h1><?php print $site_name ?></h1><?php endif; ?>
    <div class="breadcrumb"><a href="#"><?php if ($site_slogan) print $site_slogan; ?></a></div>
  </div>
</div>
<div id="outer-column-container">
  <div id="inner-column-container">
    <div id="source-order-container">
      <div id="middle-column">
        <div class="inside">
          <div class="clearfix" id="inner-topmenu">
          </div>

          <div id='main' class='clear-block'>
            <?php if ($title): ?><h2 class='page-title'><?php print $title ?></h2><?php endif; ?>
            <div id='content' class='clear-block'><?php print $content ?></div>
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
      </div>

      <div class="inside-sidebar extra-sidebar">
      </div>
    </div>
    <div class="clear-columns"><!-- do not delete --></div>
  </div>
</div>

<div id="footer"><div class='inside'>
</div></div>

    </div>
  </body>
</html>
