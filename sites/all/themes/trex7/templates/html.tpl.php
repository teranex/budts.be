<!DOCTYPE html>
<html>
  <head>
    <?php print $head ?>
    <?php print $styles ?>
    <title><?php print $head_title ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
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

      <!-- Piwik -->
<script type="text/javascript">
var pkBaseURL = (("https:" == document.location.protocol) ? "https://lightyear.be/piwik/" : "http://lightyear.be/piwik/");
document.write(unescape("%3Cscript src='" + pkBaseURL + "piwik.js' type='text/javascript'%3E%3C/script%3E"));
</script><script type="text/javascript">
try {
  var piwikTracker = Piwik.getTracker(pkBaseURL + "piwik.php", 1);
  piwikTracker.trackPageView();
  piwikTracker.enableLinkTracking();
} catch( err ) {}
</script><noscript><p><img src="http://lightyear.be/piwik/piwik.php?idsite=1" style="border:0" alt="" /></p></noscript>
<!-- End Piwik Tag -->
    </div>
  </body>
</html>
