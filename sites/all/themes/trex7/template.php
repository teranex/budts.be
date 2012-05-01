<?php

function trex7_breadcrumb(&$variables) {
  if (!empty($variables) && count($variables['breadcrumb']) > 1) {
    return '<div class="breadcrumb">' . implode(' » ', $variables['breadcrumb']) . '</div>';
  } else {
    return '<div class="breadcrumb">' . l('"Living and coding on the 3 dimensional brane of the multiverse"', '<front>')  . '</div>';
  }
}
