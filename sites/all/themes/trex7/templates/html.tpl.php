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
      <?php print $page_top; ?>
      <?php print $page; ?>
      <?php print $page_bottom; ?>
    </div>
  </body>
</html>
